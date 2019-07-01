#include <iostream>
#include <string>

using namespace std;

//4.36
void f1()
{
    int i = 3;
    double d = 4.4;
    i *= static_cast<int>(d);
    cout << i << endl;
}

//4.37
void f2()
{
    int i; double d; const string *ps; char *pc; void *pv;

    pv = const_cast<string*>(ps);
    i = static_cast<int>(*pc);
    pv = static_cast<void*>(&d);
    pc = static_cast<char*>(pv);
    
}

//4.38
void f3()
{
    int i, j;
    double slope = static_cast<double>(j/i);
}

int main()
{
    f1();

    return 0;
}