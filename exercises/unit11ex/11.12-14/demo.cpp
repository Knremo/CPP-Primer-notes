#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>

using namespace std;

//11.12
void f1()
{
    string s;
    int i;
    vector<pair<string, int>> v;
    while (cin >> s >> i)
    {
        pair<string, int> p(s,i);
        v.push_back(p);
    }

    for (auto e:v)
    {
        cout << e.first << " " << e.second << endl;
    }
}

//11.14
map<string, vector<pair<string, string>>> homeinfo;

void addinfo(const string &h, 
             const pair<string, string> &kid = pair<string, string>(), 
             map<string, vector<pair<string, string>>> &info = homeinfo)
{
    if (kid != pair<string, string>())
        info[h].push_back(kid);

    for (auto e:info)
    {
        cout << e.first << " " << e.second.size() << " ";
        for (auto c:e.second)
            cout << c.first << "&" << c.second << "@";
        cout << endl;
    }
}

int main()
{
    // f1();

    addinfo("bob", pair<string, string>("lili","1992-2-3"));
    addinfo("bob", pair<string, string>("lily","1994-2-3"));
    addinfo("bob");
    addinfo("James", pair<string, string>("ray","1992-3-3"));
    return 0;
}