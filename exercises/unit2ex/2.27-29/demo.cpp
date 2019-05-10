#include <iostream>

int main()
{
int i2 = 1;
const int *p1 = &i2;
const int & r2 = i2;
}

// 2.27
int f1()
{
    //int i = -1, &r = 0;  //xxxx
    //const int &const r2; //xxxx
}

// 2.28
void f2()
{
    //int *const cp; //xxxx
    //int *const p2; //xxxx
    //const int ic, &r = ic;  //xxxx
    //const int *const p3; //xxxx
    const int *p;
}

// 2.29
void f3()
{
    int i;
    const int ic = 1;

    i = ic;

    int *p1, *const p2 = &i;
    const int *const p3 = &ic;
    //p1 = p3; //xxxx

    //p1 = &ic; //xxxx

    //p3 = & ic; //xxxx
    
    //p2 = p1; //xxxx

    //ic = *p3; //xxxx
}