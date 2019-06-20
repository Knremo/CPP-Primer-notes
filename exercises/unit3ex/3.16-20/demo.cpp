#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

//3.16
void f1()
{

}

//3.17
void strl2u(string &s)
{
    for(auto &c : s)
    {
        c = toupper(c);
    }
}

void f2()
{
    vector<string> word;
    string w;

    while (cin >> w)
    {
        word.push_back(w);
    }

    for (auto &e : word)
    {
        strl2u(e);
        cout << e << endl;
    }
}

//3.18
void f3()
{
    vector<int> ivec;
    ivec.push_back(42);

    cout << ivec[0];
}

//3.19
void f4()
{
    vector<int> v1(10, 42);
}

//3.20
void f5()
{
    vector<int> ivec;
    int i;
    while (cin >> i)
    {
        ivec.push_back(i);
    }

    for(size_t index = 0; index < ivec.size() - 1; ++index)
    {
        cout << ivec[index] + ivec[index + 1] << " ";
    }
    cout << endl;

    size_t e = ivec.size()-1;
    for(size_t index = 0; index < (ivec.size()+1)/2; ++index)
    {
        cout << ivec[index] + ivec[index + e] << " ";
        e -= 2;
    }
}
 
int main()
{
    f5();

    return 0;
}