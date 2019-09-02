#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "Book.h"


std::vector<Book> readbookdata(const std::string &s)
{
    std::ifstream in(s);
    std::vector<Book> vbk;
    if (in)
    {
        while (!in.eof())
        {
            std::string no;
            double price;
            unsigned count;

            in >> no >> price >> count;
            Book bk(no, price, count);
            vbk.push_back(bk);
        }
    }
    else
    {
        std::cerr << "Open data file error." << std::endl;
        return vbk;
    }

    in.close();

    return vbk;
}

//8.7
bool write2txt(std::vector<Book> &v, const std::string &s)
{
    std::ofstream out(s);
    if(out)
    {
        for (auto i : v)
            i.c2str(out);
    }
    else
    {
        std::cout << "Write to file failed." << std::endl;
        out.close();
        return false;
    }
    out.close();
    return true;
}

//8.8
bool write2txtapp(std::vector<Book> &v, const std::string &s)
{
    std::ofstream out(s, std::ofstream::app);
    if(out)
    {
        for (auto i : v)
            i.c2str(out);
    }
    else
    {
        std::cout << "Write to file failed." << std::endl;
        out.close();
        return false;
    }
    out.close();
    return true;
}

int main(int argc, char *argv[])
{
    if (argc == 1 || argc > 3)
    {
        std::cerr << "paths are wrong." << std::endl;
        return 1;
    }

    std::vector<Book> vbook = readbookdata(argv[1]);
    for (auto i : vbook)
        i.print();

    if (write2txt(vbook, argv[2]))
    {
        write2txtapp(vbook, argv[2]);
        return 0;
    }
    return 1;
}