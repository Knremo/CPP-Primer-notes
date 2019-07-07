#include <iostream>

using namespace std;

//5.18
void f1()
{
    do
    {
        int v1, v2;
        cout << "Please enter two numbers to sum:";
        if (cin >> v1 >> v2)
            cout << "Sum is: " << v1 + v2 << endl;
    } while (cin);

    // do {
    //     ;
    // } while (int ival = 1); //x

    // do {
    //     int ival = 1;
    // } while (ival); //x , ival is undefined.
}

//5.19
void f2()
{
    do
    {
        string s1, s2;
        cout << "Please enter 2 strings:";
        cin >> s1 >> s2;
        cout << (s1.size() < s2.size() ? s1 : s2) << endl;
    } while (cin);
}

int main()
{
    f2();

    return 0;
}