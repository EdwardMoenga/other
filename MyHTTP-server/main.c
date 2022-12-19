#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MYHTTP_IMPLEMENTATION
#include "./myhttp.h"

// Test server, use the chunked file for encoding test
#define HOST "anglesharp.azurewebsites.net"
// Default port
#define PORT "8080"

ssize_t myhttp_write(MyHTTP_Socket socket, const void *buf, size_t count)
{
    return write((int) (int64_t) socket, buf, count);
}

ssize_t myhttp_read(MyHTTP_Socket socket, void *buf, size_t count)
{
    return read((int) (int64_t) socket, buf, count);
}

int main()
{
    struct addrinfo hints = {0};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    struct addrinfo *addrs;
    if (getaddrinfo(HOST, PORT, &hints, &addrs) < 0) {
        fprintf(stderr, "Could not get address of `"HOST"`: %s\n",
                strerror(errno));
        exit(1);
    }

    int sd = 0;
    for (struct addrinfo *addr = addrs; addr != NULL; addr = addr->ai_next) {
        sd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

        if (sd == -1) break;
        if (connect(sd, addr->ai_addr, addr->ai_addrlen) == 0) break;

        close(sd);
        sd = -1;
    }
    freeaddrinfo(addrs);

    if (sd == -1) {
        fprintf(stderr, "Could not connect to "HOST":"PORT": %s\n",
                strerror(errno));
        exit(1);
    }

    static MyHTTP myhttp = {
        .write = myhttp_write,
        .read = myhttp_read,
    };
    myhttp.socket = (void*) (int64_t) sd,

    myhttp_req_begin(&myhttp, IMHTTP_GET, "/Chunked");
    {
        myhttp_req_header(&myhttp, "Host", HOST);
        myhttp_req_header(&myhttp, "Foo", "Bar");
        myhttp_req_header(&myhttp, "Hello", "World");
        myhttp_req_headers_end(&myhttp);
        myhttp_req_body_chunk(&myhttp, "Hello, World\n");
        myhttp_req_body_chunk(&myhttp, "Test1, test2, test3\n");
    }
    myhttp_req_end(&myhttp);

    myhttp_res_begin(&myhttp);
    {
        // Status Code
        {
            uint64_t code = myhttp_res_status_code(&myhttp);
            printf("Status Code: %lu\n", code);
        }

        // Headers
        {
            String_View name, value;
            while (myhttp_res_next_header(&myhttp, &name, &value)) {
                printf("------------------------------\n");
                printf("Header Name: "SV_Fmt"\n", SV_Arg(name));
                printf("Header Value: "SV_Fmt"\n", SV_Arg(value));
            }
            printf("------------------------------\n");
        }

        // Body
        {
            String_View chunk;
            while (myhttp_res_next_body_chunk(&myhttp, &chunk)) {
                printf(SV_Fmt, SV_Arg(chunk));
            }
        }
    }
    myhttp_res_end(&myhttp);

    close(sd);

    return 0;
}
