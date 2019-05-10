#include <iostream>

void f1();

int main()
{
    f1();
    return 0;
}

// 2.36
void f1()
{
    int a = 3, b = 4;
    decltype(a) c = a; // int c = a;
    decltype((b)) d = a; // int &d = a;
    ++c;
    ++d;

    //c==4,d=4,a=4,b=4
    std::cout << a << " " << b << " " << c << " " << d <<std::endl;
}

// 2.37
void f2()
{
    int a = 3, b = 4;
    decltype(a) c = a; //int c = a;
    decltype((a = b)) d = a; // int &d = a;
}

// 2.38
