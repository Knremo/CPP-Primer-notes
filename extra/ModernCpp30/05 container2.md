# 1. 函数对象及其特化

## less
```c++
template <class T>
struct less: binary_function<T, T, bool> {
    bool operator() (const T& x, const T& y) const
    {
        return x < y;
    }
};
```
less 是一个函数对象，二元函数，执行对任意类型值的比较，返回布尔类型

C++ 默认会使用 less，相反顺序可以使用 greater

## hash
把一个某类型的值转换成一个无符号整数哈希值，类型为 `size_t`

没有可用的默认实现，对于常用的类型，系统提供了需要的特化
```c++
template <class T> struct hash;

template <>
struct hash<int>: public unary_function<int, size_t> {
    size_t operator()(int v) const noexcept
    {
        return static_cast<size_t>(v);
    }
};
```