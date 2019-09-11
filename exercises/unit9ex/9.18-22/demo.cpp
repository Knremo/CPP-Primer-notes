#include <iostream>
#include <string>
#include <deque>
#include <list>
#include <vector>

using namespace std;

//9.18
int str2deq()
{
    deque<string> ds;
    string temp;
    while (cin >> temp)
    {
        ds.push_back(temp);
    }

    for(deque<string>::const_iterator i = ds.begin(); i != ds.end(); ++i)
        cout << *i << endl;

    return ds.size();
}

//9.19
int str2list()
{
    list<string> ls;
    string temp;
    while (cin >> temp)
    {
        ls.push_back(temp);
    }

    for(list<string>::const_iterator i = ls.begin(); i != ls.end(); ++i)
        cout << *i << endl;

    return ls.size();
}

//9.20
void list2deq(const list<int> &li)
{
    deque<int> d1, d2;
    for (auto &e : li)
    {
        if (e%2 == 0)
        {
            d1.push_back(e);
        }
        else
        {
            d2.push_back(e);
        }
    }
    for (auto &e : d1)
        cout << e << endl;
    cout << "---------------" << endl;
    for (auto &e : d2)
        cout << e << endl;
}

int main()
{
    //str2list();
    list<int> li = {1,2,3,4,5,6,7,8,9,10};
    list2deq(li);

    //9.21
    vector<int> iv = {1,2,3};
    vector<int>::iterator iiv = iv.begin();
    iv.insert(iiv, 10);

    cout << iv[0] << "  " << iv[1] << endl;
    cout << *iiv << endl; //insert之后迭代器失效

    return 0;
}