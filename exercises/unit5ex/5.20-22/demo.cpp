#include <iostream>
#include <string>
#include <cctype>

using namespace std;

//5.20
void f1()
{
    string s1, s2;
    while (cin >> s1 && cin.get() != '\n')
    {
        if (s1 != s2)
        {
            s2 = s1;
            continue;
        }
        break;
    }
    if (s1 != s2)
        cout << "No words match." << endl;
    else
        cout << s1 << endl;
}

//5.21
void f2()
{
    string s1, s2;
    unsigned flag = 0;
    while (cin >> s1)
    {
        if (s1 != s2)
        {
            s2 = s1;
            continue;
        }
        else
        {
            if (isupper(s1[0]))
            {
                flag = 1;
                break;
            }
        }
    }
    if (flag == 0)
        cout << "No words match." << endl;
    else
        cout << s1 << endl;
}

int main()
{
    f2();

    return 0;
}