# 1. 回顾

```c++
class shape_wrapper {
public:
    explicit shape_wrapper(shape* ptr=nullptr): ptr_(ptr) {}
    ~shape_wrapper()
    {
        delete ptr_; // delete 一个空指针什么也不会做
    }
    shape* get() const { return ptr_; }
private:
    shape* ptr_;
};
```
这个类可以完成智能指针最基本功能：对超出作用域的对象进行释放

但是缺少：
* 这个类只适用于 `shape` 类
* 该类的行为不够像指针
* 拷贝该类对象会引发程序行为异常

# 2. 模板和易用性
包装任意类型的指针，类模板
```c++
template <typename T>
class smart_ptr {
public:
    explicit smart_ptr(T* ptr=nullptr): ptr_(ptr) {}
    ~smart_ptr()
    {
        delete ptr_;
    }
    T* get() const { return ptr_; }
private:
    T* ptr_;
};
```
但这个 smart_ptr 的行为还是和指针有点差异：
* 不能用 * 运算符解引用
* 不能用 -> 运算符指向对象成员
* 不能像指针一样用在布尔表达式里

```c++
template <typename T>
class smart_ptr {
public:
    ...

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    operator bool() const { return ptr_; }
};
```

# 3. 拷贝构造和赋值
禁止拷贝：
```c++
template <typename T>
class smart_ptr {
public:
    ...
    smart_ptr(const smart_ptr&) = delete;
    smart_ptr& operator=(const smart_ptr&) = delete;
    ...
};
```

在拷贝时转移指针所有权：
```c++
template <typename T>
class smart_ptr {
public:
    ...
    smart_ptr(smart_ptr& other)
    {
        ptr_ = other.release();
    }
    smart_ptr& operator=(smart_ptr& rhs)
    {
        smart_ptr(rhs).swap(*this); // 生成临时对象，会先拷贝构造，rhs.release()
        // 保证了强异常安全性
        return *this;
    }
    ...
    T* release()
    {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }
    void swap(smart_ptr& rhs)
    {
        using std::swap;
        swap(ptr_, rhs.ptr_);
    }
    ...
};
```
C++98 的 `auto_ptr` 的定义，已被删除

一不小心把它传递给另外一个 `smart_ptr`, 你就不再拥有这个对象

# 4. 移动语义
```c++
template <typename T>
class smart_ptr {
public:
    ...
    smart_ptr(smart_ptr&& other)
    {
        ptr_ = other.release();
    }
    smart_ptr& operator=(smart_ptr rhs)
    {
        rhs.swap(*this); 
        return *this;
    }
    ...
};
```
* `smart_ptr&&` 移动构造函数
* `smart_ptr` ，在构造参数时直接生成新的智能指针，不再需要构造临时对象

提供了移动构造函数而没有手动提供拷贝构造函数，拷贝构造函数自动被禁用，有以下结果：
```c++
smart_ptr<shape> ptr1{create_shape(shape_type::circle)};
smart_ptr<shape> ptr2{ptr1};   // 编译错误
smart_ptr<shape> ptr3;
ptr3 = ptr1;                   // 编译错误
ptr3 = std::move(ptr1);        // ok
smart_ptr<shape> ptr4{std::move(ptr3)}; // ok
```
C++11 的 `unique_ptr` 的基本行为

# 5. 子类指针向基类指针的转换
`smart_ptr<circle>` 无法自动转换成 `smart_ptr<shape>`，增加一个构造函数：
```c++
template <typename U>
smart_ptr(smart_ptr<U>&& other)
{
    ptr_ = other.release();
}
```
该构造函数不能自动触发删除拷贝构造函数，需要标记 =delete，或同时定义标准的拷贝/移动构造函数和所需的模板构造函数

可以将 `smart_ptr<circle>` 移动给 `smart_ptr<shape>`，自然
```c++
smart_ptr<circle> ptr1{ new circle() };
smart_ptr<shape> ptr2{std::move(ptr1)}; // 可以将 smart_ptr<circle> 移动给 smart_ptr<shape>
smart_ptr<circle> ptr3{ new circle() };
smart_ptr<triangle> ptr4{std::move(ptr3)}; // 编译出错，因为 circle* 不能转换为 triangle*
```

# 5. 引用计数
shared_ptr

简化版，没考虑多线程安全：
```c++
#include <utility> //std::swap

class shared_count {
public:
    shared_count(): count_(1) {}
    void add_count()
    {
        ++count_;
    }
    long reduce_count()
    {
        return --count_;
    }
    long get_count() const
    {
        return count_;
    }
private:
    long count_;
};
```
引用计数智能指针：
```c++
template <typename T>
class smart_ptr {
public:
    template <typename U>
    friend class smart_ptr; // 模板的各个实例之间没有 friend 关系，不能互相访问私有成员 ptr_

    // 构造函数，如果传入的指针不为空则构造 shared_count() 对象
    explicit smart_ptr(T* ptr = nullptr): ptr_(ptr)
    {
        if (ptr) {
            shared_count_ = new shared_count();
        }
    }
    // 析构函数，ptr_ 不为空，且计数器减一之后为0，则 delete
    ~smart_ptr()
    {
        if (ptr_ && !shared_count_->reduce_count()) { // 会减一的
            delete ptr_;
            delete shared_count_;
        }
    }
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

    // 返回私有成员 ptr_
    T* get() const noexcept
    {
        return ptr_;
    }
    // 返回引用计数值
    long use_count() const noexcept
    {
        if (ptr_) {
            return shared_count_->get_count();
        } else {
            return 0;
        }
    }
    void swap(smart_ptr& rhs) noexcept
    {
        using std::swap;
        swap(ptr_, rhs.ptr_);
        swap(shared_count_, rhs.shared_count_);
    }

    T& operator*() const noexcept { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }
    operator bool() const noexcept { return ptr_; }

private:
    T* ptr_;
    shared_count* shared_count_;
};
```

# 6. 指针类型转换
强制类型转换：

## **static_cast**

在编译期间完成类型转换

它主要有如下几种用法：
1. 用于类层次结构中基类和派生类之间指针或引用的转换
    * 进行上行转换（把派生类的指针或引用转换成基类表示）是安全的
    * 进行下行转换（把基类的指针或引用转换为派生类表示），由于没有动态类型检查，所以是不安全的
2. 用于基本数据类型之间的转换，如short转为int, int转为double, **非const转为const类型**

这种转换的安全也要开发人员来保证
```c++
short sh;
int i = static_cast<int>(sh);
const int ci = static_cast<const int>(i);
```

1. 把空指针转换成目标类型的空指针
2. 把任何类型的表达式转换为void类型或者反之

注意：static_cast不能转换掉expression的const、volitale或者__unaligned属性。

## **const_cast**

常量指针(引用)被转化成非常量指针(引用)，并且仍然指向原来的对象
```c++
const int ci = 1;
int *p = const_cast<int*>(&ci);
*p = 10;
// 我们只能通过const_cast忽略对象的属性, 却依然不能修改对象
puts(ci); // 1 
puts(*p); // 10 未定义
```

## **reinterpret_cast**

这种转换仅仅是对二进制位的重新解释(修改), 不会借助已有的转换规则对数据进行调整, 非常简单粗暴, 风险很高, 一般我们不推荐使用

reinterpret_cast用在任意指针（或引用）类型之间的转换；以及指针与足够大的整数类型之间的转换；从整数类型（包括枚举类型）到指针类型，无视大小。

## **dynamic_cast**

运行时处理，运行时要进行类型检查

用于在类的继承层次之间进行类型转换, 它既允许向上转型, 也允许向下转型

* dynamic_cast转换如果成功的话返回的是指向类的指针或引用，转换失败的话则会返回NULL
* 使用dynamic_cast进行转换的，基类中一定要有虚函数，否则编译不通过
* 在类的转换时，在类层次间进行上行转换时，dynamic_cast和static_cast的效果是一样的。在进行下行转换时，dynamic_cast具有类型检查的功能，比static_cast更安全


**smart_ptr 类型转换实现**

```c++
// 添加一个构造函数
template <typename U>
smart_ptr(const smart_ptr<U>& other, T* ptr) noexcept
{
    ptr_ = ptr;
    if (ptr_) {
        other.shared_count_->add_count();
        shared_count_ = other.shared_count_;
    }
}

template <typename T, typename U>
smart_ptr<T> static_pointer_cast(const smart_ptr<U>& other) noexcept
{
    T* ptr = static_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}
template <typename T, typename U>
smart_ptr<T> dynamic_pointer_cast(const smart_ptr<U>& other) noexcept
{
    T* ptr = dynamic_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}
template <typename T, typename U>
smart_ptr<T> reinterpret_pointer_cast(const smart_ptr<U>& other) noexcept
{
    T* ptr = reinterpret_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}
template <typename T, typename U>
smart_ptr<T> const_pointer_cast(const smart_ptr<U>& other) noexcept
{
    T* ptr = const_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}
```

最后添加一个swap
```c++
template <typename T>
void swap(smart_ptr<T>& lhs, smart_ptr<T>& rhs) noexcept
{
    lhs.swap(rhs);
}
```