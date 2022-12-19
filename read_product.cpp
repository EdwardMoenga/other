#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

struct Product
{
    std::string name;
    int quantity = 0;
    double price = 0.0;
};

// Read a product's data from std::cin
// Return a product with the data read
Product read_product();

// Write a product p to file
void write_product(std::ofstream &file, const Product &p);

int main()
{
    std::ofstream utFil("C:/TEMP/C++/list.txt");

    if (utFil)
    { // succeeded to connect the stream utFil to the text file
        // Write file's header
        utFil << std::setw(20) << "Product"
              << std::setw(14) << "Quantity"
              << std::setw(10) << "Price"
              << "\n";

        Product item = read_product(); // read first product

        // If it wasn't possible to read from std::cin then cin is in bad state
        // Loop until user ends input with ctrl-Z
        while (std::cin)
        {
            // write product to the text file
            write_product(utFil, item);

            item = read_product(); // read next product
        }
    }
    else
    {
        std::cout << "File could not be created!!\n";
    }
}

// Read a product's data from std::cin
// Return a product with the data read
Product read_product()
{
    Product p;

    // Ask a product's name
    std::cout << "Product? ";
    std::cin >> std::ws; // skip any white spaces before the name
    std::getline(std::cin, p.name);

    // Ask quantity and price
    std::cout << "Quantity and price? ";
    std::cin >> p.quantity >> p.price;

    return p;
}

// Write a product p to file
void write_product(std::ofstream &file, const Product &p)
{
    // write product, quantity, and price to the text file
    file << std::setw(20) << p.name
         << std::setw(10) << p.quantity
         << std::setw(14) << std::fixed << std::setprecision(2) << p.price << '\n';
}