# 19.1 控制内存分配
## 19.1.1 重载new和delete
当编译器发现一条 new 表达式：
1. 首先在类及其基类的作用域中查找
2. 全局作用域中查找
3. 使用标准库定义的版本

标准库定义的：
```cpp
void *operator new(size_t);
void *operator new[](size_t);
void *operator delete(void*) noexcept;
void *operator delete[](void*) noexcept;

void *operator new(size_t, nothrow_t&) noexcept;
void *operator new[](size_t, nothrow_t&) noexcept;
void *operator delete(void*, nothrow_t&) noexcept;
void *operator delete[](void*, nothrow_t&) noexcept;
```
是隐式静态的，无须显式声明 static，因为 operator new 用在对象构造之前而 operator delete 用在对象销毁之后

**malloc and free**
cstdlib

malloc 接受一个表示待分配字节数的 size_t，返回指针或0

free 接受一个 void*，释放内存

```c++
void *operator new(size_t size) {
    if (void *mem = malloc(size))
        return mem;
    else
        throw bad_alloc();
}
void operator delete(void *mem) noexcept { free(mem); }
```

## 19.1.2 定位 new 表达式
```
new (place_address) type
new (place_address) type (initializers)
new (place_address) type [size]
new (place_address) type [size] { braced initializer list }
```
palce_address 指针

**显式的析构函数调用**
`sp->~string();`

# 19.2 RTTI
typeid

dynamic_cast

我们想使用基类对象的执政或引用执行某个派生类操作并且该操作不是虚函数

## 19.2.1 dynamic_cast
```cpp
dynamic_cast<type*>(e)
dynamic_cast<type&>(e)
dynamic_cast<type&&>(e)
```
转换目标是指针并且失败了返回 0，目标是引用类型并且失败了抛出 bad_cast 异常

**指针类型的 dynamic_cast**
```cpp
if (Derived *dp = dynamic_cast<Derived*>(bp))
{
    // dp
} else {
    // bp
}
```
Derived 是 Base 的公用派生类，bp 指向 Derived 对象

**引用类型的 dynamic_cast**
```cpp
void f(const Base &b)
{
    try {
        const Derived &d = dynamic_cast<const Derived&>(b);
    } catch (bad_cast) {
        //
    }
}
```
## 19.2.2 typeid
typeid(e), 返回一个常量 type_info 对象的引用

忽略顶层 const

数组的结果是数组类型而不是指针类型

**使用 typeid 运算符**
```cpp
Derived *dp = new Derived;
Base *bp = dp;
// 运行时比较
if (typeid(*dp) == typeid(*dp)) {
    //
}
if (typeid(*bp) == typeid(Derived)) {
    //
}
```
只有当类型含有虚函数时，编译器才会对表达式求值

## 19.2.3 使用 RTTI
相等比较
```cpp
class Base {
    friend bool operator==(const Base&, const Base&);
public:
    // Base
protected:
    virtual bool equal(const Base&) const;
};
class Derived: public Base {
public:
    //
protected:
    bool equal(const Base&) const;
    //
};
bool operator==(const Base &lhs, const Base &rhs)
{
    return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
}
bool Derived::equal(const Base &rhs) const
{
    auto r = dynamic_cast<const Derived&>(rhs); // 不会抛出异常
    // ...
}
bool Base::equal(const Base &rhs) const
{
    // 比较 Base 对象的操作
}
```

## 19.2.4 type_info 类
```cpp
t1 == t2 
t1 != t2
t.name()
t1.before(t2) // 表示 t1 是否位于 t2 之前，依赖于编译器
```
创建 type_info 对象的唯一途径是使用 typeid 运算符

# 19.3 枚举类型
限定作用域枚举类型：

`enum class/enum struct open_modes {input, output, append};`

不限定作用域枚举类型：

`enum color {red, yellow, green};`

**枚举成员**
```cpp
enum color {red, yellow, green};
enum stoplight {red, yellow, green}; // xxxx, 重复定义枚举成员
enum class peppers {red, yellow, green}; // ok
color eyes = green; //ok
peppers p = green; // xxxx
peppers p2 = peppers::red; // ok
```

不限定作用域的枚举类型的对象或枚举成员自动的转换成整形

`int j = color::red;`

**指定enum的大小**
```c++
enum intValues : unsigned long long {
    charTyp = 255, shortTyp = 65535, intTyp = 65535,
    longTyp = 3423423423423423ULL
};
```
**enum 的前置声明必须指定其成员大小**

# 19.4 类成员指针
指向类的非静态成员的指针

## 19.4.1 数据成员指针
```c++
const string Screen::*pdata; // pdata 指向一个常量（非常量）Screen对象的string成员
pdata = &Screen::contents;
//
auto pdata = &Screen::contents;
```
使用
```c++
Screen myScreen, *pScreen = &myScreen;
auto s = myScreen.*pdata;
s = pScreen->*pdata;
```
**返回数据成员指针的函数**
```cpp
class Screen {
public:
    static const std::string Screen::*data()
    { return &Screen::contents; }
};

const string Screen::*pdata = Screen::data();

auto s = myScreen.*pdata;
```