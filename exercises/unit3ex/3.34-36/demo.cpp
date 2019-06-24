#include <iostream>
#include <string>
#include <iterator>
#include <vector>

using namespace std;

//3.34
void f1()
{
    int ia[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *p1 = &ia[2], *p2 = &ia[6];

    p1 += p2 - p1;
    cout << *p1 << endl;
    //功能就是返回p2的元素，失效的话应该不会失效除了p2自己的下标有问题
}

//3.35
void f2()
{
    int ia[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int *i = begin(ia); i < end(ia); ++i)
        *i = 0;
    for (auto i : ia)
        cout << i << " ";
}

//3.36
int f3()
{
    int ia[] = {1,2,3,4,5};
    short ib[] = {1,2,3,4,5};
    cout << sizeof(ia[0]) << " " << sizeof(ib[0]) << " " << (end(ia) - begin(ia)) << endl;
    //无论元素类型是int还是short,(end(ia) - begin(ia))返回的都是元素的个数

    if ((end(ia) - begin(ia)) != (end(ib) - begin(ib))) 
        return 2;
    
    for (int i = 0; i < end(ia) - begin(ia); ++i)
    {
        if (ia[i] != ib[i])
            return 1;
    }

    return 0;
}

int f4()
{
    vector<int> iva = {1,2,3,4,5};
    vector<int> ivb = {1,2,3,4,5};

    if (iva == ivb)
        cout << "hh";

    if (iva.size() != ivb.size())
        return 2;
    
    auto abeg = iva.begin(); 
    for (auto bbeg = ivb.begin(); bbeg < ivb.end(); ++bbeg)
    {
        if (*bbeg != *abeg)
            return 1;
        ++abeg;
    }

    return 0;
}

int main()
{
    
    int r = f4();
    cout << r << endl;

    return 0;
}