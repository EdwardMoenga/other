#ifndef MyHTTP_H_
#define MyHTTP_H_

#include <assert.h>
// myhttp depends on separate translation unit which makes it no longer header-only
#include "./sv.h"

typedef void* MyHTTP_Socket;
typedef ssize_t (*MyHTTP_Write)(MyHTTP_Socket socket, const void *buf, size_t count);
typedef ssize_t (*MyHTTP_Read)(MyHTTP_Socket socket, void *buf, size_t count);

// 2 methods supported
typedef enum {
    MyHTTP_GET,
    MyHTTP_POST,
} MyHTTP_Method;

#define MyHTTP_ROLLIN_BUFFER_CAPACITY (8 * 1024)
#define MyHTTP_USER_BUFFER_CAPACITY MyHTTP_ROLLIN_BUFFER_CAPACITY

static_assert(MyHTTP_ROLLIN_BUFFER_CAPACITY <= MyHTTP_USER_BUFFER_CAPACITY,
              "The user buffer should be at least as big as the rolling buffer "
              "if you want to put the whole rollin content into the user buffer.");

typedef struct {
    MyHTTP_Socket socket;
    MyHTTP_Write write;
    MyHTTP_Read read;

    char rollin_buffer[MyHTTP_ROLLIN_BUFFER_CAPACITY];
    size_t rollin_buffer_size;

    char user_buffer[MyHTTP_USER_BUFFER_CAPACITY];

    int content_length;
    bool chunked;
    size_t chunk_length;
    bool chunked_done;
} MyHTTP;

void MyHTTP_req_begin(MyHTTP *MyHTTP, MyHTTP_Method method, const char *resource);
void MyHTTP_req_header(MyHTTP *MyHTTP, const char *header_name, const char *header_value);
void MyHTTP_req_headers_end(MyHTTP *MyHTTP);
void MyHTTP_req_body_chunk(MyHTTP *MyHTTP, const char *chunk_cstr);
void MyHTTP_req_body_chunk_sized(MyHTTP *MyHTTP, const char *chunk, size_t chunk_size);
void MyHTTP_req_end(MyHTTP *MyHTTP);

void MyHTTP_res_begin(MyHTTP *MyHTTP);
uint64_t MyHTTP_res_status_code(MyHTTP *MyHTTP);
bool MyHTTP_res_next_header(MyHTTP *MyHTTP, String_View *name, String_View *value);
bool MyHTTP_res_next_body_chunk(MyHTTP *MyHTTP, String_View *chunk);
void MyHTTP_res_end(MyHTTP *MyHTTP);

#endif

#ifdef MYHTTP_IMPLEMENTATION

static void MyHTTP_drop_rollin_buffer(MyHTTP *MyHTTP, size_t n)
{
    assert(n <= MyHTTP->rollin_buffer_size);
    memmove(MyHTTP->rollin_buffer, MyHTTP->rollin_buffer + n, n);
    MyHTTP->rollin_buffer_size -= n;
}

static String_View MyHTTP_shift_rollin_buffer(MyHTTP *MyHTTP, const char *end)
{
    // Boundary check
    assert(MyHTTP->rollin_buffer <= end);
    size_t n = end - MyHTTP->rollin_buffer;
    assert(n <= MyHTTP->rollin_buffer_size);

    // Copy chunk to user buffer
    assert(n <= MyHTTP_USER_BUFFER_CAPACITY);
    memcpy(MyHTTP->user_buffer, MyHTTP->rollin_buffer, n);

    // Shifting the rollin buffer
    MyHTTP->rollin_buffer_size -= n;
    memmove(MyHTTP->rollin_buffer, end, MyHTTP->rollin_buffer_size);

    return (String_View) {
        .data = MyHTTP->user_buffer,
        .count = n,
    };
}

// document that rollin_buffer does not perform any reads until everything inside of rollin_buffer is processed
static void MyHTTP_top_rollin_buffer(MyHTTP *MyHTTP)
{
    if (MyHTTP->rollin_buffer_size == 0) {
        ssize_t n = MyHTTP->read(
                        MyHTTP->socket,
                        MyHTTP->rollin_buffer + MyHTTP->rollin_buffer_size,
                        MyHTTP_ROLLIN_BUFFER_CAPACITY - MyHTTP->rollin_buffer_size);
        // MyHTTP_top_rollin_buffer() does not handle read errors
        assert(n > 0);
        MyHTTP->rollin_buffer_size += n;
    }
}

static String_View MyHTTP_rollin_buffer_as_sv(MyHTTP *MyHTTP)
{
    return (String_View) {
        .data = MyHTTP->rollin_buffer,
        .count = MyHTTP->rollin_buffer_size,
    };
}

static const char *MyHTTP_method_as_cstr(MyHTTP_Method method)
{
    switch (method) {
    case MyHTTP_GET:
        return "GET";
    case MyHTTP_POST:
        return "POST";
    default:
        assert(0 && "MyHTTP_method_as_cstr: unreachable");
    }
}

static void MyHTTP_write_cstr(MyHTTP *MyHTTP, const char *cstr)
{
    size_t cstr_size = strlen(cstr);
    // MyHTTP_write_cstr does not handle MyHTTP_Write errors
    MyHTTP->write(MyHTTP->socket, cstr, cstr_size);
}

void MyHTTP_req_begin(MyHTTP *MyHTTP, MyHTTP_Method method, const char *resource)
{
    MyHTTP_write_cstr(MyHTTP, MyHTTP_method_as_cstr(method));
    MyHTTP_write_cstr(MyHTTP, " ");
    // it is easy to make the resource malformed in MyHTTP_req_begin
    MyHTTP_write_cstr(MyHTTP, resource);
    MyHTTP_write_cstr(MyHTTP, " HTTP/1.1\r\n");
}

void MyHTTP_req_header(MyHTTP *MyHTTP, const char *header_name, const char *header_value)
{
    MyHTTP_write_cstr(MyHTTP, header_name);
    MyHTTP_write_cstr(MyHTTP, ": ");
    MyHTTP_write_cstr(MyHTTP, header_value);
    MyHTTP_write_cstr(MyHTTP, "\r\n");
}

void MyHTTP_req_headers_end(MyHTTP *MyHTTP)
{
    MyHTTP_write_cstr(MyHTTP, "\r\n");
}

void MyHTTP_req_body_chunk(MyHTTP *MyHTTP, const char *chunk_cstr)
{
    MyHTTP_write_cstr(MyHTTP, chunk_cstr);
}

void MyHTTP_req_body_chunk_sized(MyHTTP *MyHTTP, const char *chunk, size_t chunk_size)
{
    MyHTTP->write(MyHTTP->socket, chunk, chunk_size);
}

void MyHTTP_req_end(MyHTTP *MyHTTP)
{
    (void) MyHTTP;
}

void MyHTTP_res_begin(MyHTTP *MyHTTP)
{
    MyHTTP->content_length = -1;
    MyHTTP->chunked = false;
    MyHTTP->chunk_length = 0;
    MyHTTP->chunked_done = false;
}

uint64_t MyHTTP_res_status_code(MyHTTP *MyHTTP)
{
    MyHTTP_top_rollin_buffer(MyHTTP);
    String_View rollin = MyHTTP_rollin_buffer_as_sv(MyHTTP);
    String_View status_line = sv_chop_by_delim(&rollin, '\n');
    assert(
        sv_ends_with(status_line, SV("\r")) &&
        "The rolling buffer is so small that it could not fit the whole status line. "
        "maybe the status line was not fully read after MyHTTP_top_rollin_buffer()");
    status_line = MyHTTP_shift_rollin_buffer(MyHTTP, rollin.data);
    // the HTTP version is skipped in MyHTTP_res_status_code()
    sv_chop_by_delim(&status_line, ' ');
    String_View code_sv = sv_chop_by_delim(&status_line, ' ');
    return sv_to_u64(code_sv);
}

// Document that MyHTTP_res_next_header() invalidate name and value on the consequent MyHTTP_* calls
bool MyHTTP_res_next_header(MyHTTP *MyHTTP, String_View *name, String_View *value)
{
    MyHTTP_top_rollin_buffer(MyHTTP);
    String_View rollin = MyHTTP_rollin_buffer_as_sv(MyHTTP);
    String_View header_line = sv_chop_by_delim(&rollin, '\n');
    assert(
        sv_ends_with(header_line, SV("\r")) &&
        "The rolling buffer is so small that it could not fit the whole header line. "
        "maybe the status line was not fully read after MyHTTP_top_rollin_buffer()");
    // Transfer the ownership of header_line from rollin_buffer to user_buffer
    header_line = MyHTTP_shift_rollin_buffer(MyHTTP, rollin.data);

    if (!sv_eq(header_line, SV("\r\n"))) {
        // don't set name/value if the user set them to NULL in MyHTTP_res_next_header
        *name = sv_chop_by_delim(&header_line, ':');
        *value = sv_trim(header_line);

        // are header case-sensitive?
        if (sv_eq(*name, SV("Content-Length"))) {
            // content_length overflow
            MyHTTP->content_length = sv_to_u64(*value);
        } else if (sv_eq(*name, SV("Transfer-Encoding"))) {
            String_View encoding_list = *value;
            while (encoding_list.count > 0) {
                String_View encoding = sv_trim(sv_chop_by_delim(&encoding_list, ','));
                if (sv_eq(encoding, SV("chunked"))) {
                    MyHTTP->chunked = true;
                }
            }
        }
        return true;
    }

    return false;
}

// document that the chunk is always invalidated after each MyHTTP_res_next_body_chunk() call
bool MyHTTP_res_next_body_chunk(MyHTTP *MyHTTP, String_View *chunk)
{
    if (MyHTTP->chunked) {
        if (!MyHTTP->chunked_done) {
            MyHTTP_top_rollin_buffer(MyHTTP);

            if (MyHTTP->chunk_length == 0) {
                String_View rollin = MyHTTP_rollin_buffer_as_sv(MyHTTP);
                String_View chunk_length_sv = sv_chop_by_delim(&rollin, '\n');
                assert(sv_ends_with(chunk_length_sv, SV("\r")) &&
                       "The rolling buffer is so small that it could not fit the whole chunk length. "
                       "maybe the chunk length was not fully read after the MyHTTP_top_rollin_buffer()");
                MyHTTP->chunk_length = sv_hex_to_u64(sv_trim(chunk_length_sv));
                MyHTTP_shift_rollin_buffer(MyHTTP, rollin.data);
            }

            if (MyHTTP->chunk_length == 0) {
                MyHTTP->chunked_done = true;
                return false;
            }

            {
                size_t n = MyHTTP->chunk_length;
                if (n > MyHTTP->rollin_buffer_size) {
                    n = MyHTTP->rollin_buffer_size;
                }

                String_View data = MyHTTP_shift_rollin_buffer(MyHTTP, MyHTTP->rollin_buffer + n);
                MyHTTP->chunk_length -= n;

                if (MyHTTP->chunk_length == 0) {
                    String_View rollin = MyHTTP_rollin_buffer_as_sv(MyHTTP);
                    assert(sv_starts_with(rollin, SV("\r\n")));
                    MyHTTP_drop_rollin_buffer(MyHTTP, 2);
                }

                if (chunk) {
                    *chunk = data;
                }
            }

            return true;
        }
    } else {
        // MyHTTP can't handle the responses that do not set Content-Length
        assert(MyHTTP->content_length >= 0);

        if (MyHTTP->content_length > 0) {
            MyHTTP_top_rollin_buffer(MyHTTP);
            String_View rollin = MyHTTP_rollin_buffer_as_sv(MyHTTP);
            // MyHTTP does not handle the situation when the server responded with more data than it claimed with Content-Length
            assert(rollin.count <= (size_t) MyHTTP->content_length);

            String_View result = MyHTTP_shift_rollin_buffer(
                                     MyHTTP,
                                     MyHTTP->rollin_buffer + MyHTTP->rollin_buffer_size);

            if (chunk) {
                *chunk = result;
            }

            MyHTTP->content_length -= result.count;

            return true;
        }
    }

    return false;
}

void MyHTTP_res_end(MyHTTP *MyHTTP)
{
    (void) MyHTTP;
}

#endif // MYHTTP_IMPLEMENTATION
