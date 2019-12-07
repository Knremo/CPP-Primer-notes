#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//11.28
void f2()
{
    map<string, vector<int>> vm = {{"a", {1}},{"b", {2}}};

    map<string, vector<int>>::iterator i1 = vm.find("a");
    auto i2 = vm.find("a");

    if (i1 == i2)
        cout << "ok" << endl;
}

//11.29
// c.end()
// c.end()
// pair<c.end(), c.end()>

//11.30

//11.31
int delEntry(multimap<string, vector<string>>& m, const string& s)
{
    auto count = m.count(s);
    if (count)
    {    
        auto beg = m.lower_bound(s), end = m.upper_bound(s);
        auto d = m.erase(beg, end);
    }
    return count;
}

//11.32
void sortWorks(multimap<string, vector<string>>& m)
{
    for (auto e:m)
    {
        cout << e.first << endl;
        stable_sort(e.second.begin(), e.second.end());
        for (auto c:e.second)
            cout << c << "-";
        cout << endl;
    }
}

int main()
{
    //f2();

    multimap<string, vector<string>> works = {{"laoshe", {"luotuoxiangzi"}}, 
                                              {"luxun", {"zhaohuaxishi", "aqzhengzhuan", "runtu"}},
                                              {"bajin", {"jian"}},
                                              {"bajin", {"suixianglu"}}};
    // delEntry(works, "bajin");
    // delEntry(works, "xx");
    // for (auto e:works)
    // {
    //     cout << e.first << " ";
    //     for (auto c:e.second)
    //         cout << c << "-";
    //     cout << endl;
    // }

    sortWorks(works);

    return 0;
}