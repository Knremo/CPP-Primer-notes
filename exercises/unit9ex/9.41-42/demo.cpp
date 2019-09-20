#include <iostream>
#include <vector>
#include <string>

using namespace std;

//9.41
void f1()
{
    vector<char> vc = {'a', 'b', 'c'};
    string s;
    s.assign(vc.begin(), vc.end());

    cout << s << endl;
}

int main()
{
    f1();

    return 0;
}