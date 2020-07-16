#include <array>

int sqr(int n)
{
    return n * n;
}

int main()
{
    int a[sqr(3)];

    const int n = sqr(3);
    int b[n];

    // std::array<int, sqr(3)> c; // error
}
