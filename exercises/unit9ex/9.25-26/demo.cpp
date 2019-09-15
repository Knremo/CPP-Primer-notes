#include <vector>
#include <iostream>
#include <list>

using namespace std;

//9.25
void f1()
{
    vector<int> iv = {1, 2, 3, 4, 5};
    //iv.erase(iv.begin()+2, iv.begin()+2); //相等不会删除任何元素
    //iv.erase(iv.begin()+2, iv.end()); // 1, 2
    //iv.erase(iv.end(), iv.end()); //不会删除任何元素

    for (auto e : iv)
        cout << e << endl;
}

//9.26
void f2()
{
    int ia[] = {0, 11, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    vector<int> iv;
    iv.assign(begin(ia), end(ia));
    list<int> il;
    il.assign(begin(ia), end(ia));

    for (auto e = iv.begin(); e != iv.end();)
    {
        if (*e % 2 == 0)
        {
            e = iv.erase(e);
            continue;
        }
        cout << *e << endl;
        e++;
    }

    for (auto e = il.begin(); e != il.end();)
    {
        if (*e % 2)
        {
            e = il.erase(e);
            continue;
        }
        cout << *e << endl;
        ++e;
    }
}

int main()
{
    f2();

    return 0;
}