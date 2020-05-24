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