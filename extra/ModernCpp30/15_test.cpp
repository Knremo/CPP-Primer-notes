#include <array>
#include <iostream>

template <typename T>
struct has_output_function {
    template <class U>
    static auto output(U* ptr) -> decltype(
        std::declval<std::ostream&>() << *ptr,
        std::true_type());
    template <class U>
    static std::false_type output(...);
    static constexpr bool value = decltype(output<T>(nullptr))::value;
};
template <typename T>
inline constexpr bool has_output_function_v =
    has_output_function<T>::value;

int sqr(int n)
{
    return n * n;
}

int main()
{
    int a[sqr(3)];

    const int n = sqr(3);
    int b[n];

    int* ptr;
    ptr = nullptr;
    // std::array<int, sqr(3)> c; // error
    decltype(ptr) t;
    std::cout << *t << std::endl; 

    constexpr int c = 42;
    const int& d = c;

    std::cout << 1 << std::endl;
}
