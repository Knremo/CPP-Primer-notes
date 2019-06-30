#include <iostream>

using namespace std;

//4.34
void f1()
{
    float fval = 1.56;
    int ival = 1;
    double dval;
    char cval = 'c';

    if (fval)
        cout << "1" << endl;

    dval = fval + ival;
    cout << dval << endl;

    cout << dval + ival * cval << endl;
}

//4.35
void f2()
{
    char cval;
    int ival;
    unsigned int ui;
    float fval;
    double dval;

    cval = 'a' + 3;
    fval = ui - ival * 1.0;
    dval = ui * fval;
    cval = ival + fval + dval;
}

int main()
{
    f1();

    return 0;
}