#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

// 10.34
void f1()
{
    vector<string> sv = {"one", "two", "three"};
    auto iter = sv.crbegin();
    while (iter != sv.crend())
    {
        cout << *iter++ << endl;
    }
}

//10.35
void f2()
{
    vector<string> sv = {"one", "two", "three"};
    auto iter = sv.cend();
    iter--;
    while (iter != sv.cbegin())
        cout << *iter-- << endl;
    cout << *iter << endl;
}

//10.36
void f3()
{
    list<int> li = {1, 0, 2, 0, 3, 0, 4, 5};
    auto f = find(li.crbegin(), li.crend(), 0);

    for_each(f.base(), li.cend(), [](const int s) { cout << s << endl; });
}

// 10.37
void f4()
{
    vector<int> iv = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    list<int> li;
    auto first_iter = iv.crbegin() + 3;
    reverse_iterator<vector<int>::const_iterator> last_iter = iv.crend() - 2;
    
    li.assign(first_iter, last_iter);
    for_each(li.cbegin(), li.cend(), [](const int s) { cout << s << endl; });
}

int main()
{
    f4();

    return 0;
}