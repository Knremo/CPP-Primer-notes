#include <iostream>
#include <vector>
#include <string>

using namespace std;

void f2();
void f1();

int main()
{
   f2();

    return 0;
}

//3.14
void f1()
{
    vector<int> i;
    int n;

    while (cin >> n)
    {
        i.push_back(n);
    }

    for(auto num:i)
    {
        cout << num << " ";
    }
}

//3.15
void f2()
{
    vector<string> s;
    string str;

    while(cin >> str)
    {
        s.push_back(str);
    }

    for (auto ss : s)
    {
        cout << ss << " ";
    }
}