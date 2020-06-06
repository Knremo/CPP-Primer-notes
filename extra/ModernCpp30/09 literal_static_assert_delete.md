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