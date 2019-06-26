#include <iostream>

using namespace std;

//4.4
void f1()
{
    cout << 12/3*4+5*15+24%4/2 << endl; //91
}

//4.5
void f2()
{
    cout << -30*3+21/5 << endl; //-86
    cout << -30+3*21/5 << endl; //-18
    cout <<  30/3*21%5 << endl; //0
    cout << -30/3*21%4 << endl; //-2
}

//4.6
void f3(int i)
{
    if (i % 2 == 0)
        cout << "even" << endl;
    else
        cout << "odd" << endl;
}

//4.7
void f4()
{
    short si = 65536;
}

int main()
{
    f4();

    return 0;
}