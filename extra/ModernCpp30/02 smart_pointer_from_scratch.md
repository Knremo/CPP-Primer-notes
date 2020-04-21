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