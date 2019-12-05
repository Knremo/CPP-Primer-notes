#include <map>
#include <iostream>

using namespace std;

//11.26
int main()
{
    map<string, int> m;
    map<string, int>::key_type s1 = "k1";
    string s2 = "k2";
    int i = 3;

    m[s1] = 1;
    m[s2] = 2;

    decltype(m[s1]) s = i; //int&

    cout << m[s1] << endl;
    cout << s << endl;
}