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
compose(sum_list, square_list)(v) -> 第二个 compose
[sum_list, square_list](auto&& v) {return sum_list(compose(square_list)(forward<decltype(v)>(v)));}; ->
```
