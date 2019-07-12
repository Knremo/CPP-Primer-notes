#include <iostream>

using namespace std;

//6.21
int f1(int i1, int *p1)
{
    return (i1 > *p1 ? i1 : *p1);
}

//6.22
void f2(int* p1, int* p2)
{
    decltype(p1) temp = p1;
    p1 = p2;
    p2 = temp;
    cout << *p1 << " " << *p2 << endl;
}

//6.23
void f3(int i, int (&j)[])
{
    ;
}

//6.24
void print(const int ia[10])
{
    for (size_t i = 0; i != 10; ++i)
        cout << ia[i] <<endl;
}

int main()
{
    int int1 = 34, int2 = 45;
    int* p2 = &int2, *p1 = &int1;
    cout<< f1(int1, p2) << endl;

    f2(p1, p2);
}