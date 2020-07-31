# 1. armadillo
科学计算中的标准，即是一些 Fortran 库定下的，如：
* BLAS
* LAPACK
* ARPACK

它们的实现倒不一定用 Fortran，尤其是 BLAS：
* OpenBLAS 是用汇编和 C 语言写的
* Intel MKL 有针对 Intel 的特定 CPU 指令集进行优化的汇编代码
* Mir GLAS 是用 D 语言写的

不管实现的方法是哪一种，暴露出来的函数名字是一样

使用 Armadillo 库来实现矢量旋转的代码：
```c++
#include <armadillo>
#include <cmath>
#include <iostream>

using namespace std;

int main()
{
    arma::vec pos{1.0, 0.0};

    auto& pi = arma::datum::pi;
    double angle = pi / 2;
    arma::mat rot = {
        {cos(angle), -sin(angle)},
        {sin(angle), cos(angle)}
    };

    cout << "Current position:\n" << pos;
    cout << "Rotating " << angle * 180 / pi << "deg\n";

    arma::vec new_pos = rot * pos;
    cout << "New position:\n" << new_pos;
}
```
**表达式模板**
```c++
arma::vec new_pos = rot * pos;
```
结果是一个表达式，而并没有实际进行计算

如果用 auto 的话，行为上似乎一切都正常，但我每次输出这个结果时，都会重新进行一次矩阵的乘法

而用 arma::vec 接收的话，构造时就直接进行了计算，存储了表达式的结果

# 2. Boost.Multiprecision
* 使用基本的 cpp_int 对象不需要预先编译库，只需要 Boost 的头文件和一个好的编译器。
* 常用运算符 +、-、*、/、% 一个不缺，全部都有。
* 可以自然地通过整数和字符串来进行构造。提供了用户自定义字面量来高效地进行初始化。
* 在使用 IO 流时，输入输出既可以使用十进制，也可以通过 hex 来切换到十六进制。
```c++
#include <iomanip>
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;

int main()
{
  using namespace boost::multiprecision::literals;
  using boost::multiprecision::cpp_int;

  cpp_int a = 0x123456789abcdef0_cppi;
  cpp_int b = 16;
  cpp_int c{"0400"};
  cpp_int result = a * b / c;
  cout << hex << result << endl;
  cout << dec << result << endl;
}
```

表达式模板

GMP
