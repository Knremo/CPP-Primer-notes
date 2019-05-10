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

    r1 = v2;
    //p1 = p2; //xxxx 
    p2 = p1;
    //p1 = p3; //xxxx
    p2 = p3;
}
