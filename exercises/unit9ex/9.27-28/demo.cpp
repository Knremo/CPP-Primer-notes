#include <forward_list>
#include <string>
#include <iostream>

using namespace std;

//9.28
void f1()
{
    forward_list<int> il = {1,2,3,4,5,6,7,8};
    auto it = il.before_begin();
    auto itc = il.begin();

    while (itc != il.end())
    {
        if (*itc % 2)
        {
            itc = il.erase_after(it);
        }
        else
        {
            it = itc;
            itc++;
        }
    }

    for (auto e:il)
    {
        cout << e << endl;
    }
}

//9.28
void ins2list(forward_list<string> &sil, const string &s1, const string &s2)
{
    unsigned flag = 0;
    auto it = sil.begin();
    auto bit = sil.before_begin();

    while (it != sil.end())
    {
        if (*it == s1)
        {
            sil.insert_after(it, s2);
            ++flag;
        }
        ++it;
        ++bit;
    }

    if (!flag)
    {
        sil.insert_after(bit, s2);
    }

    for (auto e:sil)
     cout << e << endl;
}

int main()
{
    forward_list<string> sil = {"a", "b","a", "b", "x"};

    ins2list(sil, "a", "hh");

    return 0;
}