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
