#include <iostream>

using namespace std;

template <bool cond, typename Then, typename Else>
struct If;

template <typename Then, typename Else>
struct If<true, Then, Else> {
    typedef Then type;
};

template <typename Then, typename Else>
struct If<false, Then, Else> {
    typedef Else type;
};

template <int n>
struct Foo {
    typedef typename If<(n==2||n==3||n==5), 
                        integral_constant<int, 1>,
                        integral_constant<int, 2>>::type type;
};

// while
template <bool condition, typename Body>
struct WhileLoop;

template <typename Body>
struct WhileLoop<true, Body> {
    typedef typename WhileLoop<Body::cond_value, typename Body::next_type>::type type;
};

template <typename Body>
struct WhileLoop<false, Body> {
    typedef typename Body::res_type type;
};

template <typename Body>
struct While {
    typedef typename WhileLoop<Body::cond_value, Body>::type type;
};

template <int result, int n>
struct SumLoop {
    static const bool cond_value = n != 0;
    static const int res_value = result;
    typedef integral_constant<int, res_value> res_type;
    typedef SumLoop<result + n, n - 1> next_type;
};

template <int n>
struct Sum {
    typedef SumLoop<0, n> type;
};


int main()
{
    cout << Foo<7>::type::value << endl;
    cout << While<Sum<10>::type>::type::value << endl;
    return 0;
}