#include <iostream>

using namespace std;
//6.49

//6.50
void f(){cout << 1 << endl;}
void f(int){cout << 2 << endl;}
void f(int, int){cout << 3 << endl;}
void f(double, double = 3.14){cout << 4 << endl;}

int f1()
{
    //f(2.56, 42); //xxx
    f(42);
    f(42, 0);
    f(2.56, 3.14);
}

//6.51

int main()
{
    f1();

    return 0;
}