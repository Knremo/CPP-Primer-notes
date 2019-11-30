#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <set>

using namespace std;

//11.9
void f1()
{
    map<string, list<int>> words;
}

//11.10
void f2()
{
    map<vector<int>::iterator, int> m1;
    map<list<int>::iterator, int> m2;
}

//11.11
struct Sale_data
{
    string bookNo;

    string isbn() const
    {
        return bookNo;
    }
};

bool compareIsbn(const Sale_data &lhs, const Sale_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

void f3()
{
    set<Sale_data, bool (*)(const Sale_data&, const Sale_data&)> s(compareIsbn);
}

int main()
{
    return 0;
}