#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "Book.h"

//8.4
std::vector<std::string> readline2vec(const std::string &infile)
{
    std::ifstream in(infile);
    std::vector<std::string> svec;
    while (!in.eof())
    {
        std::string stemp;
        std::getline(in, stemp);
        svec.push_back(stemp);
    }
    in.close();

    return svec;
}
//8.5
std::vector<std::string> readword2vec(const std::string &infile)
{
    std::ifstream in(infile);
    std::vector<std::string> svec;
    while (!in.eof())
    {
        std::string stemp;
        std::getline(in, stemp, ' ');
        svec.push_back(stemp);
    }
    in.close();

    return svec;
}

//8.6
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

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cerr << "No data file." << std::endl;
        return 1;
    }
    std::vector<std::string> sv = readword2vec("a.txt");
    std::cout << sv.size() << std::endl;

    for (auto i : sv)
        std::cout << i << std::endl;

    std::vector<Book> vbook = readbookdata(argv[1]);
    for (auto i : vbook)
        i.print();

    return 0;
}