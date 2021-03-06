# 1. 自定义字面量
字面量 literal

C++11 引入了自定义字面量，可以使用 operator“” 后缀 将字面量转换为实际的类型，C++14 则在标准库加入了不少标准字面量
```c++
#include <chrono>
#include <complex>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

int main()
{
    cout << "i * i = " << 1i * 1i << endl; // 生成虚数
    cout << "Waiting for 500ms" << endl; 
    this_thread::sleep_for(500ms); // 生成时间
    cout << "Hello world"s.substr(0, 5) << endl; // basic_string
}
```
`using namespace std;` 同时引入 std 名空间和里面的内联名空间 (inline namespace):
* std::literals::complex_literals
* std::literals::chrono_literals
* std::literals::string_literals

自己的类支持字面量，唯一的限制是非标准的字面量后缀必须以下划线 _ 打头
```c++
struct length {
    double value;
    enum unit {
        metre,
        kilometre,
        millimetre,
        centimetre,
        inch,
        foot,
        yard,
        mile,
    };
    static constexpr double factors[] = {1.0, 1000.0, 1e-3, 1e-2, 0.0254, 0.3048, 0.9144, 1609.344};
    explicit length(double v, unit u = metre)
    {
        value = v * factors[u];
    }
};

length operator+(length lhs, length rhs)
{
    return length(lhs.value + rhs.value);
}

length operator"" _m(long double v)
{
    return length(v, length::metre);
}
length operator"" _cm(long double v)
{
    return length(v, length::centimetre);
}
```
可以这样使用： `1.0_m + 10.0_cm`

# 2. 二进制字面量
从 C++14 开始，对于二进制也有了直接的字面量：

`unsigned mask = 0b111000000;`

I/O streams 只有 dec, hex, oct 三个操纵器(manipulator),输出二进制数间接使用 bitset，
```c++
#include <bitset>
cout << bitset<9>(mask) << endl;
```

# 3. 数字分隔符
C++14 允许在数字型字面量中添加 '
```c++
unsigned mask = 0b111'000'000;
long r_earth_equatorial = 6'378'137;
double pi = 3.14159'26535'89793;
const unsigned magic = 0x44'42'47'4E;
```

# 4. 静态断言
C++11 直接从语言层面提供了静态断言机制，不仅能输出更好的信息，而且适用性也更好，可以直接放在类的定义中:
```c++
static_assert(编译期条件表达式，可选输出信息);
// e.g.
static_assert((allgnment & (alignment -1)) == 0, "Alignment must be power of two");
```
如果第一个参数常量表达式的值为真(true或者非零值)，那么static_assert不做任何事情，否则会产生一条编译错误，错误位置就是该static_assert语句所在行，错误提示就是第二个参数提示字符串

# 5. default 和 delete 成员函数
关于构造函数等的复杂规则...

```c++
class my_array {
public:
    my_array() = default; // 默认构造函数
};

class shape_wrapper {
    ...
    shape_wrapper(const shape_wrapper&) = delete;
    shape_wrapper& operator=(const shape_wrapper&) = delete;
    ...
};
```

# 6. override 和 final 说明符
override 显式声明了成员函数是一个虚函数且覆盖了基类中的该函数

final 声明了成员函数是一个虚函数，且该虚函数不可在派生类中被覆盖; 标志某个类或结构不可被派生

```c++
class A {
public:
    virtual void foo();
    virtual void bar();
    void foobar();
};

class B : public A {
public:
    void foo() override;
    void bar() override final;
};

class C final : public B {
public:
    void foo() override; // ok
    // void bar() override; // xxx
};

class D : public C {}; // xxxx
```

