#include <iostream>
#include <initializer_list>

using namespace std;

//6.27
void f1(initializer_list<int> lst)
{
    int sum = 0;

    for (const auto &e : lst)
    {
        sum += e;
    }

    cout << sum << endl;
}

//6.28

//6.29

int main()
{
    f1({1, 2, 3});

    return 0;
}