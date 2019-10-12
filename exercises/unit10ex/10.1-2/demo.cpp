#include <algorithm>
#include <vector>
#include <iostream>
#include <list>

using namespace std;

int main()
{
    vector<int> iv = {1,2,3,4,2,5,2,6};
    cout << count(iv.begin(), iv.end(), 2);  

    list<string> sl = {"abs", "sqrt", "abs"};  
    cout << count(sl.begin(), sl.end(), "abs"); 
}