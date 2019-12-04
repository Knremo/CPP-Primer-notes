#include <map>
#include <string>
#include <set>
#include <iostream>
#include <vector>

using namespace std;

//11.20
void f1()
{
    map<string, size_t> word_count;
    set<string> exclude = {"The", "But"};
    string word;
    while (cin >> word)
        if (exclude.find(word) == exclude.end())
        {
            auto ret = word_count.insert({word, 1});
            if (!ret.second)
                ++ret.first->second;
        }
}

//11.21
// 这个可以

//11.22
void f3()
{
    map<string, vector<int>> m;
    m.insert({"word", {1,2,3}});

    pair<string, vector<int>> p = {"test", {1,2,3}};
    auto ret = m.insert(p);
    pair<pair<string, vector<int>>, bool> r2;

    cout << m.begin()->first << endl;
}

//11.23
multimap<string, vector<string>> homeinfo;
void addinfo(const string &h, 
             const vector<string> &kid = vector<string>(), multimap<string, vector<string>> &info = homeinfo)
{
    info.insert({h, kid});

    for (auto e:info)
    {
        cout << e.first << " ";
        for (auto c:e.second)
            cout << c << "-";
        cout << endl;
    }
}

int main()
{
    //f3();

    vector<string> bobkids = {"bob1","bob2", "bob3"};
    vector<string> anakids = {"ana1", "ana2"};
    addinfo("bob", bobkids);
    addinfo("bob", anakids);
    addinfo("jack");

    return 0;
}