#include <iostream>
#include <vector>
using namespace std;

//3.30
void f1()
{
    constexpr size_t array_size = 10;
    int ia[array_size];
    for (size_t ix = 1; ix <= array_size; ++ix) // ix = 0; ix < array_size
    {
        ia[ix] = ix;
    }
}

//3.31
void f2()
{
    int ia[10];
    for (unsigned i = 0; i < 10; ++i)
    {
        ia[i] = i;
    }
}

//3.32
void f3()
{
    vector<int> ivec;
    for (unsigned i = 0; i < 10; ++i)
        ivec.push_back(i);
}

int main()
{
    return 0;
}