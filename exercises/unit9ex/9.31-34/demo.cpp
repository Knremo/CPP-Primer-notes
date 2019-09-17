#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <forward_list>

using namespace std;

//9.31
void f1()
{
    list<int> vi = {0,1,2,3,4,5,6,7,8,9};
    auto iter = vi.begin();
    while (iter != vi.end())
    {
        if (*iter % 2)
        {
            iter = vi.insert(iter, *iter);
            iter++;
            iter++;
        }
        else
        {
            iter = vi.erase(iter);
        }
    }

    for (auto e:vi)
        cout << e <<endl;
}

void f2()
{
    forward_list<int> vi = {0,1,2,3,4,5,6,7,8,9};
    auto iter = vi.begin();
    auto iter_prev = vi.before_begin();
    while (iter != vi.end())
    {
        if (*iter % 2)
        {
            iter = vi.insert_after(iter, *iter);
            iter++;
        }
        else
        {
            iter = vi.erase_after(iter);
        }
    }

    for (auto e:vi)
        cout << e <<endl;
}

int main()
{
    f1();

    return 0;
}