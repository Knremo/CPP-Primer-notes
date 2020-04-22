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