#include <iostream>

using namespace std;

//4.8
void f1()
{
    // == , && , ||
}

//4.9
void f2()
{
    const char *cp = "Hello World";
    if (cp && *cp)
        cout << 1 << endl;
}

//4.10
void f3()
{
    int i;
    while (cin >> i)
    {
        if (i == 42)
            break;
    }
}

//4.11
void f4()
{
    int a = 12, b = 11, c = 10, d = 9;
    if (a > b && b > c && c > d)
        cout << 1 << endl;
}

//4.12
void f5()
{
    int i = 1, j = 2, k = 3;
    if (i != j < k) // j < k 得到0或1
        cout << 1 << endl;
}

int main()
{
    f5();

    return 0;
}