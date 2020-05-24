#include <iostream>

template <typename T>
void foo(const T& container)
{
    for (T::const_iterator it = container.begin();;) {}
}

int main()
{
    int a = 10;
    auto&& b = a;
}