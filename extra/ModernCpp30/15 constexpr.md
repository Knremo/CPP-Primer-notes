# 1. constexpr
* constexpr 变量
* constexpr 函数

一个 constexpr 变量是一个编译时完全确定的常数

一个 constexpr 函数至少对于某一组实参可以在编译期间产生一个编译期常数

* constexpr 变量必须立即初始化
* 初始化只能使用字面量或常量表达式，后者不允许调用任何非 constexpr 函数

下面的代码可以工作：
```c++
#include <array>
constexpr int sqr(int n) { return n * n; }

int main()
{
    constexpr int n = sqr(3);
    std::array<int, n> a;
    int b[n];
}
```

# 2. constexpr 和编译期计算
阶乘函数：
```c++
constexpr int factorial(int n)
{
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

constexpr int n = factorial(10); // ok
```
在这个 constexpr 函数里，是不能写 static_assert(n >= 0) 的。一个 constexpr 函数仍然可以作为普通函数使用.显然，传入一个普通 int 是不能使用静态断言的

替换方法是在 factorial 的实现开头加入：
```c++
if (n < 0) {
    throw std::invalid_argument("Arg must be non-negative");
}
```

# 3. constexpr 和 const