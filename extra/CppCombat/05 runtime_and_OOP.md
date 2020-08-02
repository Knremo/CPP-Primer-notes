# 实现原则
“面向对象编程”的关键点是“抽象”和“封装”，而“继承”“多态”并不是核心，只能算是附加品

建议在设计类的时候**尽量少用继承和虚函数**

可以避免去记忆、实施那一大堆难懂的相关规则，比如 public/protected/private 继承方式的区别、多重继承、纯虚接口类、虚析构函数，还可以绕过动态转型、对象切片、函数重载等很多危险的陷阱，减少冗余代码，提高代码的健壮性

非要用继承不可，那么一定要**控制继承的层次**

在设计类接口的时候，我们也要让类尽量简单，**只负责单一的功能**

# 编码准则
C++11 新增了一个特殊的标识符“final”（不是关键字），把它用于类定义，就可以显式地禁用继承，防止其他人有意或者无意地产生派生类：
```c++
class DemoClass final    // 禁止任何人继承我
{ ... };
```

一个类总是会有六大基本函数：**三个构造、两个赋值、一个析构**

对于比较重要的构造函数和析构函数，应该用 `= default` 的形式，明确地告诉编译器

因为 C++ 有隐式构造和隐式转型的规则，如果类里有单参数的构造函数，或者是转型操作符函数，为了防止意外的类型转换，保证安全，就要使用 `explicit` 将这些函数标记为“显式”
```c++
class DemoClass final 
{
public:
    explicit DemoClass(const string_type& str)  // 显式单参构造函数
    { ... }

    explicit operator bool()                  // 显式转型为bool
    { ... }
};
```

# 常用技巧
1. 委托构造 (delegating constructor)
```cpp
class DemoDelegating final
{
private:
    int a;                              // 成员变量
public:
    DemoDelegating(int x) : a(x)        // 基本的构造函数
    {}  

    DemoDelegating() :                 // 无参数的构造函数
        DemoDelegating(0)               // 给出默认值，委托给第一个构造函数
    {}  

    DemoDelegating(const string& s) : // 字符串参数构造函数
        DemoDelegating(stoi(s))        // 转换成整数，再委托给第一个构造函数
    {}  
};
```

2. 成员变量初始化 (In-class member initializer)
在类里声明变量的同时给它赋值，实现初始化
```cpp
class DemoInit final                  // 有很多成员变量的类
{
private:
    int                 a = 0;        // 整数成员，赋值初始化
    string              s = "hello";  // 字符串成员，赋值初始化
    vector<int>         v{1, 2, 3};   // 容器成员，使用花括号的初始化列表
public:
    DemoInit() = default;             // 默认构造函数
   ~DemoInit() = default;             // 默认析构函数
public:
    DemoInit(int x) : a(x) {}         // 可以单独初始化成员，其他用默认值
};
```

3. 类型别名 (Type Alias)
```cpp
using uint_t = unsigned int;        // using别名
typedef unsigned int uint_t；      // 等价的typedef
```

简化名字，同时还能增强可读性:
```cpp
class DemoClass final
{
public:
    using this_type         = DemoClass;          // 给自己也起个别名
    using kafka_conf_type   = KafkaConfig;        // 外部类起别名

public:
    using string_type   = std::string;            // 字符串类型别名
    using uint32_type   = uint32_t;              // 整数类型别名

    using set_type      = std::set<int>;          // 集合类型别名
    using vector_type   = std::vector<std::string>;// 容器类型别名

private:
    string_type     m_name  = "tom";              // 使用类型别名声明变量
    uint32_type     m_age   = 23;                  // 使用类型别名声明变量
    set_type        m_books;                      // 使用类型别名声明变量

private:
    kafka_conf_type m_conf;                       // 使用类型别名声明变量
};
```
