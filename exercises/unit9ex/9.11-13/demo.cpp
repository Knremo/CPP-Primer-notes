#include <vector>
#include <list>
#include <iostream>

using namespace std;

//9.11
void f1()
{
    vector<int> iv1;

    vector<int> iv2(iv1);
    
    vector<int> iv3{1,2,3,4,5};

    vector<int> iv4(iv3.begin(), iv3.end());

    vector<int> iv5(10,10);
}

//9/12

//9.13
int main()
{
    list<int> lst = {1,2,3,4,5};
    vector<double> vd(lst.begin(), lst.end());

    vector<int> iv = {1,2,3,4,5};
    vector<double> vd2(iv.begin(), iv.end());
    
    cout << vd2[1];

    return 0;
}