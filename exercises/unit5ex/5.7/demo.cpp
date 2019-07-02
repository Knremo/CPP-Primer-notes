#include <iostream>

using namespace std;

int get_value()
{
    return 0;
}

int main()
{
    int ival1, ival2;

    if (ival1 != ival2)
        ival1 = ival2;
    else ival1 = ival2 = 0;

    if (int ival3 = get_value())
        cout << "ival = " << ival3 << endl;

    if (int ival4 = 1)
        cout << "ival4" << endl;
}