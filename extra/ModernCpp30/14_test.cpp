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

template <typename C, typename T>
auto append(C& container, T* ptr, size_t size) 
    -> decltype(std::declval<C&>().reserve(1U), void())
{ }


class MyContainer {
public:
    void reserve(size_t n) {  }
};

typedef std::integral_constant<bool, true> true_type;
typedef std::integral_constant<bool, false> false_type;

template <typename T, typename = std::void_t<>>
struct has_reserve2 : false_type {};

template <typename T>
struct has_reserve2<T, std::void_t<decltype(std::declval<T&>().reserve(1U))>> : true_type {};

int main()
{
    auto r = has_reserve<MyContainer>::value;
    if (r) std::cout << 1;

    MyContainer mc;
    int Myarray[3] = {1,2,3};
    append(mc, Myarray, 2);

    auto r2 = has_reserve2<MyContainer>::value;
    if (r) std::cout << 2;
}