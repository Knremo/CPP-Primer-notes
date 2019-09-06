#include <vector>
#include <iostream>
#include <list>

using namespace std;

//9.3

//9.4
bool findint(vector<int>::iterator ib, vector<int>::iterator ie, int target)
{
    while (ib != ie)
    {
        if (*ib == target)
            return true;
        ++ib;
    }
    return false;
}

//9.5
vector<int>::iterator findint2(vector<int>::iterator ib, vector<int>::iterator ie, int target)
{
    while (ib != ie)
    {
        if (*ib == target)
            return ib;
        ++ib;
    }
    return ie;
}

int main()
{
    vector<int> iv = {2,3,4,5,2,32,454,54,2,4,33,43,43,5,56,11,8,789,7,67,55,1};
    if (iv.end() != findint2(iv.begin(), iv.end(), 32))
        cout << "True." << endl;
    

    //9.6
    list<int> lst1;
    list<int>::iterator iter1 = lst1.begin(), iter2 = lst1.end();

    //while (iter1 < iter2)
    //{}

    return 0;
}