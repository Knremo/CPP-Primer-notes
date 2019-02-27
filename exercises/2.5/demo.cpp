#include <typeinfo>
#include <iostream>

int main()
{
    unsigned s = 10;
    std::cout << typeid(L"a").name() << std::endl;
    std::cout << sizeof(long) << std::endl;
}