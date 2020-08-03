# 1. auto
auto 的“自动推导”能力只能用在“**初始化**”的场合

在类成员变量初始化的时候，目前的 C++ 标准不允许使用 auto 推导类型

**两条简单的规则**：
* auto 总是推导出“**值类型**”，绝不会是“引用”；
* auto 可以附加上 const、volatile、*、& 这样的类型修饰符，得到新的类型。

```cpp
auto        x = 10L;    // auto推导为long，x是long

auto&       x1 = x;      // auto推导为long，x1是long&
auto*       x2 = &x;    // auto推导为long，x2是long*
const auto& x3 = x;        // auto推导为long，x3是const long&
auto        x4 = &x3;    // auto推导为const long*，x4是const long*
```

# 2. decltype
```cpp
int x = 0;          // 整型变量

decltype(x)     x1;      // 推导为int，x1是int
decltype(x)&    x2 = x;    // 推导为int，x2是int&，引用必须赋值
decltype(x)*    x3;      // 推导为int，x3是int*
decltype(&x)    x4;      // 推导为int*，x4是int*
decltype(&x)*   x5;      // 推导为int*，x5是int**
decltype(x2)    x6 = x2;  // 推导为int&，x6是int&，引用必须赋值
```

**decltype 不仅能够推导出值类型，还能够推导出引用类型，也就是表达式的“原始类型”**

C++14 就又增加了一个 `decltype(auto)` 的形式，既可以精确推导类型，又能像 auto 一样方便使用:
```cpp
int x = 0;            // 整型变量

decltype(auto)     x1 = (x);  // 推导为int&，因为(expr)是引用类型
decltype(auto)     x2 = &x;   // 推导为int*
decltype(auto)     x3 = x1;   // 推导为int&
```

# 3. 使用 auto/decltype
* 在 C++14 里，auto 还新增了一个应用场合，就是能够推导函数返回值

* 用 decltype 很容易得到指针类型：
```cpp
// UNIX信号函数的原型，看着就让人晕，你能手写出函数指针吗？
void (*signal(int signo, void (*func)(int)))(int)

// 使用decltype可以轻松得到函数指针类型
using sig_func_ptr_t = decltype(&signal) ;
```

* decltype 搭配别名任意定义类型，再应用到成员变量、成员函数上:
```cpp
class DemoClass final
{
public:
    using set_type      = std::set<int>;  // 集合类型别名
private:
    set_type      m_set;                   // 使用别名定义成员变量

    // 使用decltype计算表达式的类型，定义别名
    using iter_type = decltype(m_set.begin());

    iter_type     m_pos;                   // 类型别名定义成员变量
};
```

* C++17 为 auto 增加了 “结构化绑定”，相当于简化了的 tie() 用法