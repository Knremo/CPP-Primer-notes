#include <string>
#include <iostream>

class Book
{
private:
    std::string bookNo;
    double price;
    unsigned count;
    double total;
public:
    
    Book(const std::string &n, double p, unsigned c)
        :bookNo(n), price(p), count(c), total(p * c) {}
    Book(): Book("", 0.0, 0) {}
    
    void print()
    {
        std::cout << bookNo << " " << price << " " << count << " " << total << std::endl;
    }
};
