# 1. 面向对象和多态
动态多态

# 2. C++ 模板
## 定义模板
```c++
template <typename T>
T my_gcd(T a)
{
    // ...
}
```

## 实例化模板
不管是类模板还是函数模板，编译器在看到其定义时只能做最基本的语法检查，真正的类型检查要在实例化（instantiation）的时候才能做

在整个的编译过程中，可能产生多个这样的（相同）实例，但最后链接时，会只剩下一个实例

### 显式实例化和外部实例化
显式实例化
```c++
tempalte cln::cl_I my_gcd(cln::cl_I, cln::cl_I);
```

如果在显式实例化的形式之前加上 `extern` 的话，编译器就会认为这个模板已经在其他某个地方实例化，从而不再产生其定义

当我们在使用 `vector<int>` 这样的表达式时，我们就在隐式地实例化 `vector<int>`

我们同样也可以选择用 `template class vector<int>` 来显式实例化

或使用 `extern template class vector<int>` 来告诉编译器不需要实例化

### 特化模板
需要使用的模板参数类型，不能完全满足模板的要求，可以：
* 添加代码，让那个类型支持需要的操作
* 对于函数模板，可以直接针对那个类型进行重载
* 对于类模板和函数模板，可以针对那个类型进行特化

1. 添加 operator% 的实现：
```c++
cln::cl_I
operator%(const cln::cl_I& lhs, const cln::cl_I& rhs)
{
  return mod(lhs, rhs);
}
```

2. 针对 cl_I 进行重载：
```c++
template <typename E>
E my_gcd(E a, E b)
{
  while (b != E(0)) {
    E r = my_mod(a, b);
    a = b;
    b = r;
  }
  return a;
}
// 一般情况的 my_mod
template <typename E>
E my_mod(const E& lhs, const E& rhs)
{
  return lhs % rhs;
}
// 针对 cl_I 类的重载
cln::cl_I
my_mod(const cln::cl_I& lhs, const cln::cl_I& rhs)
{
  return mod(lhs, rhs);
}
```

3. 针对 cl_I 进行特化：
specialization
```c++
template <>
cln::cl_I my_mod<cln::cl_I>(const cln::cl_I& lhs, const cln::cl_I& rhs)
{
  return mod(lhs, rhs);
}
```
一般而言，特化是一种更通用的技巧，最主要的原因是特化可以用在类模板和函数模板上，而重载只能用于函数

对函数使用重载，对类模板进行特化

使用特化技巧大致实现 static_assert 的功能：
```c++
template <bool>
struct complie_time_error;
template <>
struct compile_time_error<true> {};

#define STATIC_ASSERT(Expr, Msg) \
  { \
    compile_time_error<bool(Expr)> ERROR_##_Msg; \
    (void)ERROR_##_Msg;\
  }

// 在宏里 ## 表示连接两个子串
```
上面首先声明了一个 struct 模板，然后仅对 true 的情况进行了特化，产生了一个 struct 的定义。这样。如果遇到 `compile_time_error<false>` 的情况——也就是下面静态断言里的 Expr 不为真的情况——编译就会失败报错，因为 `compile_time_error<false>` 从来就没有被定义过

# 3. 动态多态和静态多态的对比
动态”多态解决的是运行时的行为变化，选择了一个形状之后，再选择在某个地方绘制这个形状——这个是无法在编译时确定的

“静态”多态或者“泛型”，解决的是很不同的问题，让适用于不同类型的“同构”算法可以用同一套代码来实现，实际上强调的是对代码的复用

## sort 算法
C++ 里的标准 sort 算法（以两参数的重载为例）只要求：
* 参数满足随机访问迭代器的要求
* 迭代器指向的对象之间可以使用 < 来比较大小，满足严格弱序关系
* 迭代器指向的对象可以被移动

## 其他
```c++
reverse：反转
count：计数
find：查找
max：最大值
min：最小值
minmax：最小值和最大值
next_permutation：下一个排列
gcd：最大公约数
lcm：最小公倍数
etc.
```

# 4. 补充
```c++
template <class T>  //(a)
void f(T)；

template <> // 显式特化，这一次是（a）的特化
void f<>(int *);

template <class T> // (b)第二个基本模板，重载(a)
void f(T*);

int* p;
f(p);
```
针对 `int*` 的全特化在(a)的后面，就是属于(a)的基础模板的全特化，在(b)后面就是(b)的全特化

所以对函数用重载就行了

`#include <typeinfo>`