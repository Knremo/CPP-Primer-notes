# 1. 自动类型推断
## auto
不使用自动类型推断时，如果容器类型未知的话，还要加上 typename
```c++
template <typename T>
void foo(const T& container)
{
    for (typename T::const_iterator it = v.begin(), ...) // 编译器无法判断 const_iterator 是一个类型还是一个成员变量
}
```
如果不使用自动类型推断，为了支持遍历 C 数组，只能使用两个不同的重载
```c++
template <typename T, std::size_t N>
void foo(const T (&a)[N])
{
    typedef const T* ptr_t;
    for (ptr_t it = a, end = a + N; it != end; ++it) {  }
}
template <typename T>
void foo(const T& c)
{
    for (typename T::const_iterator it = c.begin(), end = c.end(); it != end; ++it) {  }
}
```
而使用自动类型推断,以及 C++11 的begin end
```c++
template <typename T>
void foo(const T& c)
{
    using std::begin; // 使用依赖查找
    using std::end;
    for (auto it = begin(c), ite = end(c); it != ite; ++it) {  }
}
```

* `auto a = expr;` 用 expr 去匹配一个假想的 `template <typename T> f(T)`, 结果为值类型
* `const auto& a = expr;` `template <typename T> f(const T&)`, 结果为常左值引用类型
* `auto&& a = expr;` `template <typename T> f(T&&)`, 结果是一个跟 expr 值类别相同的引用类型

# 2. decltype
基本用法：
* decltype(变量名)，可以获得变量的精确类型
* decltype(表达式)，包括 ((变量名)) 可以获得表达式的引用类型; 若表达式是纯右值，结果仍然是值类型

## decltype(auto)
```c++
decltype(expr) a = expr; // 根据表达式类型决定返回值类型

// C++ 14
decltype(auto) a = expr;
```

## 函数返回值类型推断
