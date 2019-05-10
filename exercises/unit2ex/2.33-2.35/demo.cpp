#include <iostream>

int main()
{
    return 0;
}

//2.33 2.34
void f1(void)
{
    int i = 0, &r = i;
    auto a = r;

    const int ci = i, &cr = ci;
    auto b = ci;
    auto c = cr;
    auto d = &i;
    auto e = &ci;
    auto &g = ci;

    //a - int a
    //b - int b
    //c - int c
    //d - int *d
    //e - const int *e
    a = 42;
    b = 42;
    c = 42;
    //d = 42; //xxxx
    //e = 42; //xxxx
    //g = 42; //xxxx
}

// 2.35
void f2()
{
    const int i = 42;
    auto j = i; // int j
    const auto &k = i; // const int &k
    auto *p = &i; // const int *p
    const auto j2 = i; // cosnt int
    const auto &k2 = i; // const int &k2
}