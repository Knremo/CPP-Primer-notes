#include <iostream>
#include <vector>
#include <list>

using namespace std;

//9.15
bool f1(vector<int> iv1, vector<int> iv2)
{
    if (iv1 == iv2)
        return true;
    
    return false;
}

//9.16
bool f2(vector<int> iv, list<int> il)
{
    if (iv.size() == il.size())
    {
        list<int>::iterator liter = il.begin();
        for (auto e : iv)
            if (e != *liter)
                return false;
        return true;
    }
    else
    {
        return false;
    }
}

//9.17
