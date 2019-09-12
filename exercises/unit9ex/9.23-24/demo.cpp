#include <vector>
#include <iostream>

using namespace std;

//9.24
int main()
{
    vector<int> iv;

    //cout << iv.at(0) << endl; /out_of_range
    cout << iv[0] << endl;
    cout << iv.front() << endl;
    cout << *iv.begin() << endl;

    return 0;

}