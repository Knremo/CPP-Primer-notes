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
注意：这条规则只对 prvalue 有效，xvalue 无效
```c++
#include <utility>

result&& r = std::move(process_shape(circle(), triangle()));
// result() 还是会在这一句结束被销毁，之后对 r 的解引用未定义
```

# 4. 移动的意义
string的拼接

移动语义使得在 C++ 里返回大对象（如容器）的函数和运算符成为现实

# 5. 如何实现移动

* 分开的拷贝构造函数和移动构造函数
* swap 成员函数
* 全局 swap 函数
* 通用的 operator=
* 上面各个函数如果不抛异常，标为 noexcept

```c++
// 拷贝构造函数，只能用于相同模板参数的对象
smart_ptr(const smart_ptr& other)
{
    ptr_ = other.ptr_;
    if (ptr_) {
        other.shared_count_->add_count();
        shared_count_ = other.shared_count_;
    }
}
// 拷贝构造函数，同上，但是可以用于不同模板参数的对象 
// 例如 smart_ptr<circle> ptr1; smart_ptr<shape> ptr2{ptr1};
// 不能把 smart_ptr<circle> 转换为 smart_ptr<triangle>,因为 ptr_ = other.ptr_; 这一句，可以将
// circle* 转为 shape*，但不能转为 triangle*
// 定义这个功能与上面的相同，但不定义上面的非模板拷贝构造函数，编译器会合成拷贝构造函数，出错
template <typename U>
smart_ptr(const smart_ptr<U>& other) noexcept
{
    ptr_ = other.ptr_;
    if (ptr_) {
        other.shared_count_->add_count(); // 增加计数器
        shared_count_ = other.shared_count_;
    }
}
// 移动构造函数
template <typename U>
smart_ptr(smart_ptr<U>&& other) noexcept
{
    ptr_ = other.ptr_;
    if (ptr_) {
        shared_count_ = other.shared_count_;
        other.ptr_ = nullptr;
    }
}

// 赋值构造函数
// 拷贝传参时调用拷贝构造函数，计数器已经加1，直接和临时对象交换
smart_ptr& operator=(smart_ptr rhs) noexcept
{
    rhs.swap(*this);
    return *this;
}

void swap(smart_ptr& rhs) noexcept
{
    using std::swap;
    swap(ptr_, rhs.ptr_);
    swap(shared_count_, rhs.shared_count_);
}

template <typename T>
void swap(smart_ptr<T>& lhs, smart_ptr<T>& rhs) noexcept
{
    lhs.swap(rhs);
}
```

# 6. 不要返回本地变量的引用
在函数结束时本地对象即被销毁，返回一个指向本地对象的引用属于未定义行为

C++11开始，返回值优化（NRVO）仍可以发生，但在没有返回值优化的情况下，编译器视图把本地对象移动出去，而不是拷贝出去

用 `std::move` 反而会妨碍了返回值优化

# 7. 引用坍缩和完美转发

* 对于 `template <typename T> foo(T&&)` 这样的代码，如果传递过去的参数是左值，T 的推导结果是左值引用；如果传递过去的参数是右值，T 的推导结果是参数的类型
* 如果 T 是左值引用，那 T&& 的结果仍然是左值引用
* 如果 T 是一个实际类型，那 T&& 的结果是一个右值引用

```c++
template <typename T>
void bar(T&& s)
{
    foo(std::forward<T>(s));
}
```