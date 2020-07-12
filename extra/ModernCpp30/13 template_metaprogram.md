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
C++ 标准库在 `<type_traits>` 头文件里定义了很多工具类模板，用来提取某个类型（type）在某方面的特点（trait）

integral_constant 就是其中之一

针对布尔值
```c++
typedef std::integral_constant<bool, true> true_type;
typedef std::integral_constant<bool, false> false_type;
```

一个工具函数
```c++
template <typename T>
class SomeContainer {
public:
    ...
    static void destory(T* ptr)
    {
        _destory(ptr, is_trivially_destructible<T>());
    }
private:
    static void _destory(T* ptr, true_type) {}
    static void _destory(T* ptr, fasle_type)
    {
        ptr->~T();
    }
};
```
很多容器类里会有一个 `destroy` 函数，通过指针来析构某个对象

为了确保最大程度的优化，常用的一个技巧就是用 `is_trivially_destructible` 模板来判断类是否是可平凡析构的——也就是说，不调用析构函数，不会造成任何资源泄漏问题

模板返回的结果还是一个类，要么是 `true_type`，要么是 `false_type`

如果要得到布尔值的话，使用 `is_trivially_destructible<T>::value` 

## trait class
* is_array
* is_enum
* is_function
* is_pointer
* is_reference
* is_const
* has_virtual_destructor
* ...

## remove_const
```c++
template <class T>
struct remove_const {
    typedef T type;
};
template <class T>
struct remove_const<const T> {
    typedef T type;
};

remove_const<const string&>::type == string&
```
如果对 `const char*` 应用 `remove_const` 的话，结果还是 `const char*`。原因是，`const char*` 是指向 `const char` 的指针，而不是指向 `char` 的 `const` 指针。如果我们对 `char * const` 应用 `remove_const` 的话，还是可以得到 `char*` 的。

## 简易写法
```c++
template <class T>
inline constexpr bool is_trivially_destructible_v =is_trivially_destructible<T>::value;


template <class T>
using remove_const_t = typename remove_const<T>::type;
```

## fmap
```c++
template <
    template <typename, typename>
    class OutContainer = vector,
    typename F, class R
    >
auto fmap(F&& f, R&& inputs)
{
    typedef decay_t<decltype(f(*inputs.begin()))> result_type;
    OutContainer<result_type, allocator<result_type>> result;
    for (auto&& item:inputs) {
        result.push_back(f(item));
    }
    return result;
}

vector<int> v{1,2,3,4,5};
int add_1(int x)
{
    return x + 1;
}
auto result = fmap(add_1, v);
// {2,3,4,5,6}
```
* 用 decltype 来获得用 f 来调用 inputs 元素的类型（参考第 8 讲）；
* 用 decay_t 来把获得的类型变成一个普通的值类型；
* 缺省使用 vector 作为返回值的容器，但可以通过模板参数改为其他容器；
* 使用基于范围的 for 循环来遍历 inputs，对其类型不作其他要求（参考第 7 讲）；
* 存放结果的容器需要支持 push_back 成员函数（参考第 4 讲）。