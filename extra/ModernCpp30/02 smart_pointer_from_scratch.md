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
    explicit smart_ptr(T* ptr = nullptr): ptr_(ptr)
    {
        if (ptr) {
            shared_count_ = new shared_count();
        }
    }
    ~smart_ptr()
    {
        if (ptr_ && !shared_count_->reduce_count()) {
            delete ptr_;
            delete shared_count_;
        }
    }

private:
    T* ptr_;
    shared_count* shared_count_;
};
```
