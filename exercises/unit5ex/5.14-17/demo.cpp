#include <iostream>
#include <string>

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

int main()
{
    f1();

    return 0;
}