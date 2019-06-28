#include <iostream>

using namespace std;

//4.13
void f1()
{
    int i;
    double d;
    d = i = 3.5;
    cout << i << " " << d << endl;

    i = d = 3.5;
    cout << i << " " << d << endl;
}

//4.14
void f2()
{
    int i;
    //if (42 = i) ++i; //wrong
    if (i = 0)
        cout << 1 << endl;
    if (i = 1)
        cout << 2 << endl;
}

//4.15
void f3()
{
    double dval;
    int ival;
    int *pi;
    //dval = ival = pi = 0; //wrong
    dval = ival = 0;
    pi = 0;
}

//4.16
void f4()
{
    //if ((p = getPtr()) != 0)

    //if (i == 1024)
}

int main()
{
    f2();

    return 0;
}