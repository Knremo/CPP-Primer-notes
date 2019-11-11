#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

//10.27
void f1()
{
    vector<int> iv1;
    vector<int> iv2 = {1,1,2,2,3,4,5};

    unique_copy(iv2.begin(), iv2.end(), back_inserter(iv1));

    for_each(iv1.begin(), iv1.end(), [](const int i){cout << i << " ";});
}

//10.28
void f2()
{
    vector<int> iv = {1,2,3,4,5,6,7,8,9};

    vector<int> iv_ins, iv_back;
    list<int> lst;

    copy(iv.cbegin(), iv.cend(), inserter(iv_ins, iv_ins.begin()));
    copy(iv.cbegin(), iv.cend(), back_inserter(iv_back));
    copy(iv.cbegin(), iv.cend(), front_inserter(lst));

    vector<vector<int>> r = {iv_ins, iv_back};
    for (auto e:r)
    {
        for_each(e.begin(), e.end(), [](const int i){cout << i << " ";});
        cout << endl;
    }
    for_each(lst.begin(), lst.end(), [](const int i){cout << i << " ";});
}

int main()
{
    f2();

    return 0;
}