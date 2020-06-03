#include <iostream>


template <typename T>
constexpr std::string_view type_name()
{
    return __PRETTY_FUNCTION__;
}

#define TYPE_DISPLAY(var) static type_displayer<decltype(var)> type_display_test

template <typename T>
class type_displayer
{
    public:
    type_displayer()
    {
        std::cout << type_name<T>() << std::endl;
    }
};

int main()
{
    int a = 10;
    auto&& b = a;
    TYPE_DISPLAY(b);

    return 0;
}