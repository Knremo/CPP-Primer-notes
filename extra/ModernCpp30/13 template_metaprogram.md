# 1. 编译期计算
C++ 模板是图灵完全的

## 阶乘函数
```c++
template <int n>
struct factorial {
    static const int value = n * factorial<n - 1>::value;
};

template <>
struct factorial<0> {
    static const int value = 1;
};
int main()
{
    cout << factorial<5>::value; // 120
}
```
这个计算是在编译期完成的

分析：
```c++
factorial<5>::value ->
5 * factorial<4>::value ->
5 * 4 * factorial<3>::value ->
5 * 4 * 3 * factorial<2>::value ->
5 * 4 * 3 * 2 * factorial<1>::value ->
5 * 4 * 3 * 2 * 1 * factorial<0>::value -> 120
```

使用 `static_assert` 确保参数永远不会是负数
```c++
template <int n>
struct factorial {
    static_assert(n >= 0, "Arg must be non-negative");
    static const int value = n * factorial<n - 1>::value;
};
```

## 条件语句
```c++
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

Foo<7>::type::value; // 2
```
分析：
```c++
Foo<7>::type::value ->
If<(7==2||7==3||7==5), integral_constant<int, 1>, integral_constant<int, 2>>::type::value ->
If<false, integral_constant<int, 1>, integral_constant<int, 2>>::type::value ->
integral_constant<int, 2>>::value -> 2
```

## while loop
```c++
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

cout << While<Sum<10>::type>::type::value << endl;
```
分析：
```c++
While<Sum<10>::type>::type::value ->
While<SumLoop<0, 10>>::type::value ->
WhileLoop<SumLoop<0, 10>::cond_value, SumLoop<0, 10>>::type::value ->
WhileLoop<true, SumLoop<0, 10>>::type::value ->
WhileLoop<SumLoop<0, 10>::cond_value, typename SumLoop<0, 10>::next_type>::type::value ->
WhileLoop<true, SumLoop<10, 9>>::type::value ->
WhileLoop<SumLoop<10, 9>::cond_value, typename SumLoop<10, 9>::next_type>::type::value ->
WhileLoop<true, SumLoop<19, 8>>::type::value ->
... ->
WhileLoop<true, SumLoop<54, 1>>::type::value ->
WhileLoop<SumLoop<54, 1>::cond_value, typename SumLoop<54, 1>::next_type>::type::value ->
WhileLoop<true, SumLoop<55, 0>>::type::value ->
WhileLoop<SumLoop<55, 0>::cond_value, typename SumLoop<55, 0>::next_type>::type::value ->
WhileLoop<false, SumLoop<55, -1>>::type::value ->
SumLoop<55, -1>::res_type::value -> 
integral_constant<int, 55>::value -> 55
```

# 2. 编译期类型推导
