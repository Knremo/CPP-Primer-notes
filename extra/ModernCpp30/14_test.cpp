#include <iostream>

template <typename T>
struct has_reserve {
    struct good { char dummy; };
    struct bad { char dummy[2]; };
    template <class U, void (U::*)(size_t)>
    struct SFINAE {};
    template <class U>
    static good reserve(SFINAE<U, &U::reserve>*);
    template <class U>
    static bad reserve(...);
    static const bool value = sizeof(reserve<T>(nullptr)) == sizeof(good);
};

class MyContainer {
public:
    int reserve(size_t n) { return 1; }
};

int main()
{
    auto r = has_reserve<MyContainer>::value;
    if (r) std::cout << 1;
}