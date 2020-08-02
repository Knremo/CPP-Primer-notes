# 1. 编译期编程
斐波那契数列：
```c++
template<int N>
struct fib                   // 递归计算斐波那契数列
{
    static const int value =
        fib<N - 1>::value + fib<N - 2>::value;
};

template<>
struct fib<0>                // 模板特化计算fib<0>
{
    static const int value = 1;
};

template<>
struct fib<1>               // 模板特化计算fib<1>
{
    static const int value = 1;
};

// 调用后输出2，3，5，8
cout << fib<2>::value << endl;
cout << fib<3>::value << endl;
cout << fib<4>::value << endl;
cout << fib<5>::value << endl;
```

# 2. 属性 (attribute)
给变量、函数、类等“贴”上一个编译阶段的“标签”，方便编译器识别处理

C++11 里只定义了两个属性：“noreturn”和“carries_dependency”
```c++
[[noreturn]]              // 属性标签
int func(bool flag)       // 函数绝不会返回任何值
{
    throw std::runtime_error("XXX");
}
```

C++14 增加了一个比较实用的属性“deprecated”、
```c++
[[deprecated("deadline:2020-12-31")]]      // C++14 or later
int old_func();
```

GCC 的属性都在“gnu::”里:
* deprecated：与 C++14 相同，但可以用在 C++11 里。
* unused：用于变量、类型、函数等，表示虽然暂时不用，但最好保留着，因为将来可能会用。
* constructor：函数会在 main() 函数之前执行，效果有点像是全局对象的构造函数。
* destructor：函数会在 main() 函数结束之后执行，有点像是全局对象的析构函数。
* always_inline：要求编译器强制内联函数，作用比 inline 关键字更强。
* hot：标记“热点”函数，要求编译器更积极地优化。

```c++
[[gnu::unused]]      // 声明下面的变量暂不使用，不是错误
int nouse;  
```

# 3. 静态断言 (static_assert)
assert 虽然是一个宏，但在预处理阶段不生效，而是在运行阶段才起作用，所以又叫“动态断言”

“static_assert” 是一个专门的关键字，而不是宏。它只在编译时生效

使用 `assert` 要包含头文件 `<cassert>`，如果再编译时定义了 `NDEBUG`，就会令 assert 宏为空，完全禁用断言

