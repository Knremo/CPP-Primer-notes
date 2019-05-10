#include <iostream>

int main()
{
    return 0;
}

// 2.30
void f1()
{
    const int v2 = 0; //low
    int v1 = v2; 

    int *p1 = &v1, &r1 = v1;
    const int i = 1;
    const int *p2 = &v2, *const p3 = &i, &r2 = v2;
    // low - high - low

    r1 = v2; //常量给非常量赋值
    //p1 = p2; //xxxx ，指向常量的指针赋给指向非常量的指针
    p2 = p1; //指向非常量的指针赋给指向常量的指针
    //p1 = p3; //xxxx, 指向常量的常量指针赋给指向非常量的指针
    p2 = p3; //指向常量的常量指针赋给指向常量的指针
}

// 2.32
void f2()
{
    int null = 0;
    //int *p = null; //xxxx
}