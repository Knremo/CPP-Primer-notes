#include <iostream>

using namespace std;

// 3.2
void f1()
{
    string s;
    while (getline(cin, s))
        cout << s << endl;
}

// 3.4
void f2()
{
    string s1, s2;
    while (cin >> s1 >> s2)

    {
        s1 >= s2 ? cout << s1 : cout << s2;
        cout << endl;
        s1.size() >= s2.size() ? cout << s1
                               : cout << s2;
    }
}

// 3.5
void f3()
{
    string s1, s2, temp;
    while (cin >> temp)
    {
        s1 = s1 + temp;
        s2 = s2 + temp + " ";
    }
    cout << s1 << endl << s2;
}

int main()
{
    f3();

    return 0;
}