#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <forward_list>

using namespace std;

//9.31
void f1()
{
    list<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto iter = vi.begin();
    while (iter != vi.end())
    {
        if (*iter % 2)
        {
            iter++;
            iter = vi.insert(iter, 12);
            iter++;
        }
        else
        {
            iter = vi.erase(iter);
        }
    }

    for (auto e : vi)
        cout << e << endl;
}

void f2()
{
    forward_list<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto iter = vi.begin();
    auto iter_prev = vi.before_begin();
    while (iter != vi.end())
    {
        if (*iter % 2)
        {
            iter = vi.insert_after(iter, 12);
            iter++;
            iter_prev++;
        }
        else
        {
            iter = vi.erase_after(iter_prev);
            iter_prev++;
        }
    }

    for (auto e : vi)
        cout << e << endl;
}

//9.32
void f3()
{
    vector<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto iter = vi.begin();
    while (iter != vi.end())
    {
        if (*iter % 2)
        {
            iter = vi.insert(iter, *iter++);
            iter++;
        }
        else
        {
            iter = vi.erase(iter);
        }
    }

    for (auto e : vi)
        cout << e << endl;
}

//9.33
void f4()
{
    vector<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto begin = vi.begin();

    while (begin != vi.end())
    {
        if (*begin % 2)
        {
            begin++;
            begin = vi.insert(begin, 42); //去掉之后失败
            begin++;
        }
        else
        {
            begin++;
        }
    }

    for (auto e : vi)
        cout << e << endl;
}

//9.34
void f5()
{
    vector<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto begin = vi.begin();

    while (begin != vi.end())
    {
        if (*begin % 2)
            begin = vi.insert(begin, *begin++);  
        ++begin;
    }

    for (auto e : vi)
        cout << e << endl;
}

int main()
{
    f5();

    return 0;
}