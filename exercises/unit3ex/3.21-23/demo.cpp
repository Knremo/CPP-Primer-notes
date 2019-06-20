#include <iostream>
#include <vector>
#include <string>

using namespace std;

//3.21
void f1()
{
    vector<string> v7{10, "hi"};

    for (auto a = v7.begin(); a != v7.end(); ++a)
    {
        cout << *a << " ";
    }
}

//3.22

//3.23
void f2()
{
    vector<int> ivec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    for (auto index = ivec.begin(); index != ivec.end(); ++index)
    {
        *index = (*index) * 2;
        cout << *index << " ";
    }
}

int main()
{
    f2();

    return 0;
}