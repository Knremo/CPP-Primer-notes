#include <iostream>
#include <vector>

using namespace std;

//4.31
void f1()
{
    vector<int> ivec(10);
    vector<int>::size_type cnt = ivec.size();

    for (vector<int>::size_type ix = 0;
         ix != ivec.size(); ix++, cnt--)
        ivec[ix] = cnt;

    for (auto i : ivec)
        cout << i << " ";
}

//4.32
void f2()
{
    constexpr int size = 5;
    int ia[size] = {1, 2, 3, 4, 5};
    for (int *ptr = ia, ix = 0;
         ix != size && ptr != ia + size;
         ++ix, ++ptr)
    {
        cout << *ptr << " " << ia[ix];
    }
}

//4.33
void f3()
{
    int x = 1, y = 1;
    1 ? ++x, ++y : --x, --y; // == (1 ? (++x, ++y) : --x), --y;
    cout << x << " " << y;
}

int main()
{
    f3();

    return 0;
}