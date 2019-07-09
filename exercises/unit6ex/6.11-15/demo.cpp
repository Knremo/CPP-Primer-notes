#include <iostream>

using namespace std;

//6.11
void reset(int &i)
{
    i = 0;
}

//6.12
void f2(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

//6.13

//6.14

//6.15


int main()
{
    int ire = 9;
    reset(ire);
    cout << ire << endl;

    int a = 3, b =4;
    f2(a,b);
    cout << a << " " << b <<endl;
}