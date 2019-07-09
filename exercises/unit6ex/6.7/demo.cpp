#include <iostream>

using namespace std;

int f1()
{
    static unsigned cnt = 0;
    return cnt++;
}

int main()
{
    for (int i = 0; i< 10;++i)
        cout << f1() << endl;
    return 0;
}