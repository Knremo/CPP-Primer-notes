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
    
}
int main()
{
    f3();

    return 0;
}