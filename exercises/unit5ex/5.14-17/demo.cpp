#include <iostream>
#include <string>
#include <vector>

using namespace std;

//5.14
void f1()
{
    string s;
    string temp, last;
    unsigned count = 0, last_cnt = 0;
    while (cin >> s)
    {
        if (s == temp)
            count++;
        else if (s != temp)
        {
            if (count > last_cnt)
            {
                last_cnt = count;
                last = temp;
            }
            temp = s;
            count = 1;
        }
    }
    cout << last << " " << last_cnt << endl;
}

//5.15
void f2()
{
    for (int ix = 0;; ++ix)
        if (ix != 10)
            ;

    int ix = 0;
    for (; ix != 10; ++ix)
        ;

    for (int ix = 0; ix != 10; ++ix)
        ;
}

//5.16

//5.17
void f3()
{
    vector<int> v1 = {0, 1, 1, 2, 5};
    vector<int> v2 = {0, 2, 1};

    auto v1beg = v1.begin(), v1end = v1.end();
    auto v2beg = v2.begin(), v2end = v2.end();

    while (v1beg != v1end && v2beg != v2end)
    {
        if (*v1beg != *v2beg)
            break;
        v1beg++, v2beg++;
    }

    if (v1beg != v1end && v2beg != v2end) cout << 0 << endl;
    else
    {
        cout << 1 << endl;
    }
    
}

int main()
{
    f3();

    return 0;
}