#include <memory>
#include <string>
#include <iostream>

using namespace std;

//12.23
char* f1(const string &s1, const string &s2)
{
    size_t size = s1.size() + s2.size();
    string temp = s1 + s2;

    char *p = new char[size+1];
    for (size_t i = 0; i < size; ++i)
        p[i] = temp[i];
    p[size] = '\0';
    
    return p;
}

//12.24
//超出好像也没啥
char *f2()
{
    char *x = new char[10]();
    size_t c = 0;
    char t;
    while (cin >> t)
    {
        x[c] = t;
        ++c;
    }
    x[c] = '\0';

    return x;
}

//12.25
void f3()
{
    int *pa = new int[10];
    delete [] pa;
}

int main()
{
    // auto p = f1("happy", "day");
    // cout << p << endl;
    // delete [] p;

    auto p = f2();
    cout << p << endl;
    delete [] p;

    return 0;
}