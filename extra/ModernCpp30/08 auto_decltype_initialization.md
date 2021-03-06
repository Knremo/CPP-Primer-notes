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

# 3. 函数返回值类型推断
从 C++14, 函数的返回值可以用 auto 或 decltype(auto) 来声明

后置返回值类型声明
```c++
auto foo(args) -> 返回值类型声明
{
    // ...
}
```

# 4. 类模板的模板参数推导
使用 pair
```c++
pair<int, int> pr{1, 42};
auto pr = make_pair(1, 42); // 函数模板推导

// C++ 17 之前的类模板没有模板参数推导
// 之后
pair pr{1, 42};
// 同样
array<int, 3> a{1, 2, 3}; // ==
array a{1, 2, 3};
```
这种自动推导机制，可以是编译器根据构造函数来自动生成
```c++
template <typename T>
struct MyObj {
    MyObj(T value);
    …
};

MyObj obj1{string("hello")};
// 得到 MyObj<string>
MyObj obj2{"hello"};
// 得到 MyObj<const char*>
```
也可以是手工提供一个推导向导
```c++

template <typename T>
struct MyObj {
  MyObj(T value);
  …
};

MyObj(const char*) -> MyObj<string>;

MyObj obj{"hello"};
// 得到 MyObj<string>
```

# 5. 结构化绑定
```c++
// C++11/14
multimap<string, int>::iterator lower, upper;
std::tie(lower, upper) = mmp.equal_range("four");
// C++17
auto [lower, upper] = mmp.equal_range("four");
// 可以用 auto 来获得 pair 或 tuple 返回值里的各个子项
```

# 6. 列表初始化
```c++
vector<int> v{1,2,3,4,5};
```

# 7. 统一初始化
uniform initialization

几乎可以在所有初始化对象的地方使用大括号，当一个构造函数不是 explicit，可以使用大括号不写类名进行构造
```c++
Obj getObj()
{
    return {1.0}; // 如果 Obj 类可以使用浮点数进行构造
}
```
跟 `Obj(1.0)` 的主要区别是，后者可以用来调用 Obj(int), 而大括号不接受窄转换

如果一个类既有使用初始化列表的构造函数，又有不使用初始化列表的构造函数，编译器会千方百计调用初始化列表的构造函数，导致意外

# 8. 类数据成员的默认初始化
```c++
class Complex {
public:
    Complex() {}
    Complex(float re): re_(re) {}
    Complex(float re, float im): re_(re), im_(im) {}
private:
    float re_(0);
    float im_(0);
};
```

打印变量推导类型
```c++
template <typename T>
constexpr std::string_view type_name()
{
    return __PRETTY_FUNCTION__;
}

#define TYPE_DISPLAY(var) static type_displayer<decltype(var)> type_display_test

template <typename T>
class type_displayer
{
    public:
    type_displayer()
    {
        std::cout << type_name<T>() << std::endl;
    }
};

int main()
{
    int a = 10;
    auto&& b = a;
    TYPE_DISPLAY(b);

    return 0;
}
```
```c++
boost::typeindex::type_id_with_var<decltype(var)>().pretty_name()
```