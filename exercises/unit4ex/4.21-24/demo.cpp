#include <iostream>
#include <vector>

using namespace std;

//4.21
void f1()
{
    vector<int> ivec = {1, 2, 3};

    for (auto &e : ivec)
    {
        e = (e % 2 == 0) ? e : e * 2;
        cout << e << " ";
    }
}

//4.22
void f2()
{
    unsigned grade = 76;
    cout << ((grade > 90) ? "high pass"
                          : (grade > 75) ? "pass"
                                         : (grade > 60) ? "low pass" : "fail");
}

void f3()
{
    unsigned grade = 76;

    if (grade > 90)
        cout << "high pass";
    else if (grade > 75)
        cout << "pass";
    else if (grade > 60)
        cout << "low pass";
    else
        cout << "fail";
}

//4.23
void f4()
{
    string s = "word";
    string pl = s + (s[s.size() - 1] == 's' ? "" : "s");
    cout << pl << endl;
}

//4.24


int main()
{
    f4();

    return 0;
}