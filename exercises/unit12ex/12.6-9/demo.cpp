#include <vector>
#include <memory>
#include <iostream>

using namespace std;

//12.6
vector<int> *rePointer()
{
    auto p = new vector<int>();
    return p;
}
vector<int> *mycin(vector<int> *p)
{
    int i;
    while (cin >> i)
    {
        p->push_back(i);
    }
    return p;
}
void mycout(vector<int> *p)
{
    for (auto e : *p)
    {
        cout << e << endl;
    }
    delete p;
}

//12.7
shared_ptr<vector<int>> rePointer2()
{
    auto p = make_shared<vector<int>>();
    return p;
}
shared_ptr<vector<int>> mycin2(shared_ptr<vector<int>> p)
{
    int i;
    while (cin >> i)
    {
        p->push_back(i);
    }
    return p;
}
void mycout2(shared_ptr<vector<int>> p)
{
    for (auto e : *p)
    {
        cout << e << endl;
    }
}

//12.8

//12.9
void f4()
{
    int *q = new int(42), *r = new int(100);
    r = q;
    auto q2 = make_shared<int>(42), r2 = make_shared<int>(100);
    r2 = q2;
    delete r,q;
}

int main()
{
    //mycout2(mycin2(rePointer2()));

    f4();
    return 0;
}