#include <iostream>
#include <bitset>

using namespace std;

//4.25
void f1()
{
    char x = 'q';
    cout << bitset<8>(x) << endl;
    cout << bitset<32>(~x << 6) << endl;
}

//4.26

//4.27
void f2()
{
    unsigned long ul1 = 3, ul2 = 7;

    cout << bitset<sizeof(unsigned long)*8>(ul1) << endl <<
            bitset<sizeof(unsigned long)*8>(ul2) << endl;

    cout << bitset<sizeof(unsigned long)*8>(ul1 & ul2) << endl;       
    cout << bitset<sizeof(unsigned long)*8>(ul1 | ul2) << endl;
    cout << bitset<sizeof(unsigned long)*8>(ul1 && ul2) << endl; //1
    cout << bitset<sizeof(unsigned long)*8>(ul1 || ul2) << endl; //1
}

int main()
{
    f2();

    return 0;
}