#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iterator>
#include <set>
using namespace std;

//11.7
map<string, vector<string>> homeinfo;
void addinfo(const string &h, const vector<string> &kid = vector<string>(), map<string, vector<string>> &info = homeinfo)
{
    if (info.find(h) == info.end())
        info[h] = kid;
    else
        if (!kid.empty())
            copy(kid.begin(), kid.end(), back_inserter(info[h]));

    for (auto e:info)
    {
        cout << e.first << " ";
        for (auto c:e.second)
            cout << c << "-";
        cout << endl;
    }
}

//11.8
set<string> words;
void f2(const string &s)
{
    words.insert(s);
    for (auto e:words)
        cout << e << " ";
    cout << endl;
}

int main()
{
    // vector<string> bobkids = {"bob1","bob2", "bob3"};
    // vector<string> anakids = {"ana1", "ana2"};
    // addinfo("bob", bobkids);
    // addinfo("ana", anakids);
    // addinfo("jack");

    f2("happy");
    f2("day");
    f2("and");
    f2("day");
    f2("happy");

    return 0;
}
