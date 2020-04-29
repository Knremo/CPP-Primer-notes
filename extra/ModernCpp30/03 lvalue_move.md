# 1. 值分左右
左值 lvalue 是有标识符、可以取地址的表达式：
* 变量、函数或数据成员的名字
* 返回左值引用的表达式，如 ++x、x=1、cout<<' '
* 字符串字面量如 "hello world"

左值可以绑定到左值引用的参数，T&，一个常量只能绑定到常左值引用，const T&

纯右值 prvalue 是没有标识符、不可以取地址的表达式，一般也称之为“临时对象”：
* 返回非引用类型的表达式，如 x++、x+1、make_shared<int>(42)
* 出字符串字面量之外的字面量，如 42、true

```c++
smart_ptr<shape> ptr1{new circle()};
smart_ptr<shape> ptr2 = std::move(ptr1);
```
`new circle()` 是一个纯右值，但对于指针一般值传递，并不关心它是左值还是右值

`std::move(ptr1)` 把这种表达式叫做 xvalue (expiring lvalue),将亡值

* lvalue：不可移动，有标识符
* xvalue：可移动，有标识符
* prvalue：可移动，无标识符

# 2. 值类别和值类型
值类别 value category: 指的是左值、右值相关的概念

值类型 value type: 与引用类型 (reference type) 相对而言, 所有的原生类型、枚举、结构、联合、类都代表值类型，只有引用& 和指针* 才是引用类型

# 3. 声明周期和表达式类型
**一个临时对象会在包含这个临时对象的完整表达式估值完成后、按生成顺序的逆序被销毁，除非有生命周期延长发生**

C++ 对临时对象有特殊的生命周期延长规则：如果一个 prvalue 被绑定到一个引用上，它的生命周期则会延长到跟这个引用变量一样长
```c++
result process_shape(const shape& shape1, const shape& shape2)
{
    return result();
}

process_shape(circle(), triangle());
// 上一句执行结束就依次销毁 result(), triangle(), circle()

result&& r = process_shape(circle(), triangle());
// rusult() 的析构被延迟到main的最后
```
注意：这条规则只对 prvalue 有效，xvalue无效
```c++
#include <utility>

result&& r = std::move(process_shape(circle(), triangle()));
// result() 还是会在这一句结束被销毁，之后对 r 的解引用未定义
```

# 4. 移动的意义
移动语义使得在 C++ 里返回大对象（如容器）的函数和运算符成为现实