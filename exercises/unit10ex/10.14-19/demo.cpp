#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//10.14
auto f = [](int a, int b) { return a + b; };

//10.15
void f2(int a)
{
    auto r = [a](int b) { return a + b; };
    cout << r(5);
}

//10.16

//10.17
struct Sales_data
{
    Sales_data(const string &isbn) : bookNo(isbn) {}

    string isbn() const { return bookNo; }
    string bookNo;
};
vector<Sales_data> sv = {Sales_data("997"), Sales_data("9966"), Sales_data("998")};

bool compareIsbn(const Sales_data &s1, const Sales_data &s2)
{
    return s1.isbn().size() < s2.isbn().size();
}

void f3(vector<Sales_data> &sv)
{
    stable_sort(sv.begin(), sv.end(), 
                [](const Sales_data &s1, const Sales_data &s2){return s1.isbn().size() < s2.isbn().size();});

    for (auto e : sv)
        cout << e.isbn() << endl;
}


//10.18


int main()
{
    cout << f(1, 2);

    f2(1);
    f3(sv);
}