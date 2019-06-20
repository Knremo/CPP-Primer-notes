#include <iostream>
#include <vector>
#include <string>

using namespace std;

//3.24
void f1()
{
    vector<int> ivec{2, 3, 4, 5, 6, 7, 8};

    for (auto beg = ivec.begin(); beg < ivec.end() - 1; ++beg)
    {
        cout << *beg + *(beg + 1) << " ";
    }
    cout << endl;
    auto end = ivec.end();
    for (auto beg = ivec.begin(); beg <= ivec.begin() + (ivec.end() - ivec.begin()) / 2; ++beg)
    {
        cout << *beg + *(end - 1) << " ";
        --end;
    }
}

//3.25
void f2()
{
    vector<int> score = {42, 65, 95, 100, 39, 67, 95, 76, 88, 76, 83, 92, 76, 93};
    vector<unsigned> list(11,0);

    for (auto s : score)
    {
        ++*(list.begin() + s/10);
    }

    for (auto n : list)
    {
        cout << n << " ";
    }
}

//3.26
void f3()
{
    vector<int> score{42, 65, 95, 100, 39, 67, 95, 76, 88, 76, 83, 92, 76, 93};
    auto beg = score.begin(), end = score.end();
    auto mid = beg + (end - beg) / 2;
//    auto mid = (beg + end) / 2; //没有定义迭代器相加的规则
    cout << *mid;
}

int main()
{
    f3();

    return 0;
}