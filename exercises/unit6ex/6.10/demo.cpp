#include <iostream>

using namespace std;


void f1(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int i1 = 3, i2 = 4;
    int *p1 = &i1, *p2 = &i2;
    f1(p1, p2);
    cout << i1 << " " << i2 << endl;
    return 0;
}