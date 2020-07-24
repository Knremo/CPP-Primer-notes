# 1. 可变模板
C++11 引入的一项新功能，使我们可以在模板参数里表达**不定个数和类型的参数**。从实际的角度，它有两个明显的用途：
* 用于在通用工具模板中转发参数到另外一个函数
* 用于在递归的模板中表达通用的情况（另外会有至少一个模板特化来表达边界情况）

## 转发用法
make_unique
```c++
template <typename T, typename... Args>
inline unique_ptr<T> make_unique(Args&&...)
{
    return unique_ptr<T>(new T(forward<Args>(args)...));
}
```
* `typename... Args` 声明了一系列的类型, `class...` 或 `typename...` 表示后面的标识符代表了一系列的类型
* `Args&&... args` 声明了一系列的形参 `args`，其类型是 `Args&&`
* `forward<Args>(args)...` 会在编译时实际逐项展开 `Args` 和 `args` ，参数有多少项，展开后就是多少项

`make_unique<vector<int>>(100, 1)` 模板实例化相当于：
```c++
template <>
inline unique_ptr<vector<int>> make_unique(int&& arg1, int&& arg2)
{
    return unique_ptr<vector<int>>(
        new vector<int>(forward<int>(arg1), forward<int>(arg2))
    );
}
```
## 递归用法
用可变模板来实现编译期递归
```c++
template <typename T>
constexpr auto sum(T x)
{
    return x;
}

template <typename T1, typename T2, typename... Targ>
constexpr auto sum(T1 x, T2 y, Targ... args)
{
    return sum(x+y, args...);
}

auto result = sum(1,2,3,4,5);
```
只有一个参数，会走到上面的重载，下面的重载每次会递归调用，每次少一个参数

复合函数：
```c++
template <typename F>
auto compose(F f)
{
    return [f](auto&&... x) {
        return f(forward<decltype(x)>(x)...);
    };
}
template <typename F, typename... Args>
auto compose(F f, Args... other)
{
    return [f, other...](auto&&... x) {
        return f(compose(other...)(forward<decltype(x)>(x)...));
    };
}
```
先平方在求和
```c++
auto square_list = [](auto&& container) {
    return fmap([](int x) { return x*x; }, 
                container);
};
auto sum_list = [](auto&& container) {
    return accumulate(container.begin(), container.end(), 0);
};

auto squared_sum = compose(sum_list, square_list);

vector v{1, 2, 3, 4, 5};
cout << squared_sum(v) << endl;
```
分析：
```c++
squared_sum(v) -> compose(sum_list, square_list)(v) -> 第二个 compose, 返回的是一个 lambda 对象
[sum_list, square_list](auto&& v) {return sum_list(  compose(square_list)(forward<vector<int>>(v))  );}; -> 内层的 compose 匹配第一个
[sum_list, square_list](auto&& v) {return sum_list(  [square_list](auto&& v) {return square_list(forward<vector<int>>(v);};  );}; -> 计算最内层的 square_list
[sum_list, square_list](auto&& v) {return sum_list(  { 被平方的 vector }  );}; ->
[sum_list, square_list](auto&& v) { return { 先平方再求和的 vector } }; ->
{ 先平方再求和的 vector }
```

# 2. tuple
```c++
#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

using num_tuple = tuple<int, string, string>;

ostream& operator<<(ostream& os, const num_tuple& value)
{
    os << get<0>(value) << ','
       << get<1>(value) << ','
       << get<2>(value);
}

int main()
{
    vector<num_tuple> vn{
        {1, "one", "un"},
        {2, "two", "deux"},
        {3, "three", "trois"},
        {4, "four", "quatre"}
    };
    get<2>(vn[0]) = "une";
    // 按照法文排序
    sort(vn.begin(), vn.end(),
         [](auto&& x, auto&& y) {
             return get<2>(x) < get<2>(y);
         });
    for (auto&& value : vn) {
        cout << value << endl;
    }
    constexpr auto size = tuple_size_v<num_tuple>;
    cout << "Tuple size is " << size << endl;
}
```

参数项数会变时，使用 `make_index_sequence` 处理：
```c++
template <class T, T... Ints>
struct integer_sequence {};

template <size_t... Ints>
using index_sequence = integer_sequence<size_t, Ints...>;

template <size_t N, size_t... Ints>
struct index_sequence_helper {
    typedef typename index_sequence_helper<N-1,N-1,Ints...>::type type;
};

template <size_t... Ints>
struct index_sequence_helper<0, Ints...> {
    typedef index_sequence<Ints...> type;
};

template <size_t N>
using make_index_sequence = typename index_sequence_helper<N>::type;
```
分析：
```c++
make_index_sequence<4> -> index_sequence_helper<4>::type ->
index_sequence_helper<3,3>::type ->
index_sequence_helper<2,2,3>::type ->
index_sequence_helper<1,1,2,3>::type ->
index_sequence_helper<0,0,1,2,3>::type ->
index_sequence<0,1,2,3> -> 
integer_sequence<size_t,0,1,2,3>
```
一个简化版的 apply:
```c++
template <class F, class Tuple, size_t... I>
constexpr decltype(auto) apply_impl(F&& f, Tuple&& t, index_sequence<I...>)
{
    return f(get<I>(forward<Tuple>(t))...);
}
template <class F, class Tuple>
constexpr decltype(auto) apply(F&& f, Tuple&& t)
{
    return apply_impl(forward<F>(f),
                      forward<Tuple>(t),
                      make_index_sequence<tuple_size_v<remove_reference_t<Tuple>>>{});
}
```
分析：
```c++
apply(f, tuple<int, string, string>()) ->
apply_impl(forward<F>(f), forward<tuple<int,string,string>>(t), index_sequence<0,1,2>{}) -> 推导出 I 为 size_t 类型的模板参数包 0,1,2
f(get<I>(forward<tuple<int,string,string>>(t))...) -> 应用模板参数包 I 后再扩展 ->
f(get<0>(forward<tuple<int,string,string>>(t)));
f(get<1>(forward<tuple<int,string,string>>(t)));
f(get<2>(forward<tuple<int,string,string>>(t)));

// 错误用法
f(get<I...>(forward<tuple<int,string,string>>(t))) 扩展会得到
f(get<0，1，2>(forward<tuple<int,string,string>>(t))) // xxxx
```

# 3. 数值预算
