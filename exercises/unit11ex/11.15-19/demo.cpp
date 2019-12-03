#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

//11.15
void f1()
{
    map<int, vector<int>>::mapped_type v1;
    auto v11 = v1; //vector<int>
    map<int, vector<int>>::key_type v2;
    auto v22 = v2; //int
    map<int, vector<int>>::value_type v3;
    auto v33 = v3; //pair<int, vector<int>>
}

//11.16
void f2()
{
    map<string, int> m = {{"a", 1}, {"b", 2}};
    auto mit = m.begin();
    mit->second = 4;
    cout << m.find("a")->second;
}

//11.17
void f3()
{
    multiset<string> c = {"d", "e", "f"};
    vector<string> v = {"a", "b", "c"};

    //copy(v.begin(), v.end(), inserter(c, c.end())); //v->c ok
    //copy(v.begin(), v.end(), back_inserter(c)); //v->c wrong c 没有push_back的方法
    //copy(c.begin(), c.end(), inserter(v, v.end())); //c->v ok
    copy(c.begin(), c.end(), back_inserter(v)); //c->v ok

    for_each(c.begin(), c.end(), [](const string &s){cout << s << endl;});
    cout <<endl;
    for_each(v.begin(), v.end(), [](const string &s){cout << s << endl;});
}

//11.18
void f4()
{
    map<string, vector<int>> m;
    map<string, vector<int>>::iterator map_it = m.begin();

    auto map_itt = m.begin();

    if (map_it == map_itt)
        cout << "ok" << endl;

}

// 11.19
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
void f5()
{
    multiset<Sale_data, bool (*)(const Sale_data&, const Sale_data&)> bookstore(compareIsbn);
    multiset<Sale_data, bool (*)(const Sale_data&, const Sale_data&)>::iterator set_it = bookstore.begin();

    auto set_itt = bookstore.begin();

    if (set_it == set_itt)
        cout << "okk";
}

int main()
{
    f5();

    return 0;
}