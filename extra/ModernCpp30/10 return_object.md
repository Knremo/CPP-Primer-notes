# 1. 调用者负责管理内存，接口负责生成
C 的惯用做法
```c++
MyObj obj;
ec = initialize(&obj);
```

# 2. 借口负责对象的堆上生成和内存管理
接口提供生成和销毁对象的函数，对象在堆上维护，然后由调用者通过调用 delete 来释放
```c++
matrix* add(const matrix* lhs, const matrix* rhs, error_code_t* ec);
void deinitialize(matrix** mat);

error_code_t ec;
matrix* temp = nullptr;
temp = add(a, b, &ec);
if(!temp) goto end;
end:
    if (temp)
        deinitialize(&temp);
```

# 3. 接口直接返回对象
```c++
#include <armadillo>
#include <iostream>

using arma::imat22;
using std::cout;

int main()
{
    imat22 a{{1, 1}, {2, 2}};
    imat22 b{{1, 0}, {0, 1}};
    imat22 c{{2, 2}, {1, 1}};
    imat22 r = a * b + c;
    cout << r;
}
```
这段代码使用了Armadillo，一个利用现代C++特性的开源线性代数库

# 4. 如何返回一个对象
一个用来返回的对象，通常应当是可移动构造 / 赋值的，一般也同时是可拷贝构造 / 赋值的。如果这样一个对象同时又可以默认构造，我们就称其为一个半正则（semiregular）的对象

半正则意味着matrix类提供下面的成员函数：
```c++
class matrix {
public:
    matrix(size_t rows, size_t cols);
    // 半正则要求的构造
    matrix();
    matrix(const matrix&);
    matrix(matrix&&);
    // 半正则要求的赋值
    matrix& operator=(const matrix&);
    matrix& operator=(matrix&&);
};
```
## 没有返回值优化
返回非引用类型的表达式结果是个纯右值（prvalue）

在执行`auto r = …`的时候，编译器会认为我们实际是在构造`matrix r(…)`，而“…”部分是一个纯右值。
因此编译器会首先试图匹配 `matrix(matrix&&)`，在没有时则试图匹配 `matrix(const matrix&)`；也就是说，有移动支持时使用移动，没有移动支持时则拷贝。

## 返回值优化
```c++
#include <iostream>

using namespace std;

// Can copy and move
class A {
public:
  A() { cout << "Create A\n"; }
  ~A() { cout << "Destroy A\n"; }
  A(const A&) { cout << "Copy A\n"; }
  A(A&&) { cout << "Move A\n"; }
};

A getA_unnamed()
{
  return A();
}

int main()
{
  auto a = getA_unnamed();
}
```
结果是
```
Create A
Destroy A
```
既没有移动构造也没有拷贝构造

## 删除拷贝和移动构造函数
C++14 之前出错

但从 C++17 开始，对于 `getA_unnamed()` 这种情况，即使对象不可拷贝，不可移动，仍是可以被返回的。对象必须被直接构造在目标位置，不经过拷贝或移动的步骤