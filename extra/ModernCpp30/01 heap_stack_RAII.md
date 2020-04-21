# 1. 基本概念
* **堆**，heap，指的是动态分配内存的区域，跟数据结构里的堆不是一回事
* **自由存储区**，free store，特指使用 `new` 和 `delete` 来分配和释放内存的区域，是堆的一个子集
  * `new` 和 `delete`，free store
  * `malloc` 和 `free`，heap
* **栈**，stack，函数调用过程中产生的本地变量和调用数据的区域，LIFO
* **RAII**，Resource Acquisition Is Initialization，C++ 资源管理方式

# 2. 堆
在堆上分配内存并构造对象
```c++
auto ptr = new std::vector<int>();
```

**内存溢出**

# 3. 栈
函数调用，本地变量

后进先出

在大部分计算机体系架构中，栈的增长方向是低地址

栈帧（stack frame）：

POD类型（Plain Old Data）：简单类型

栈展开（stack unwinding）：发生异常是对析构函数的调用。编译器会自动调用析构函数，包括在函数执行发生异常的情况。

在C++里，所有的变量缺省都是值语义

# 4. RAII
工厂方法，返回值是基类的指针或引用：
```c++
enum class shape_type {
    circle,
    triangle,
    rectangle,
    ...
};

class shape {};
class circle : public shape {};
class triangle : public shape {};
class rectangle : public shape {};

shape* create_shape(shape_type type)
{
    ...
    switch (type) {
        case shape_type::circle:
            return new circle(...);
        case shape_type::triangle:
            return new triangle(...);
        case shape_type::rectangle:
            return new rectangle(...);
    ...
    }
}
```
对象切片（object slicing）：返回类型是基类的值，实际返回一个具体类，会被切割成基类对象

为了确保在使用 create_shape 的返回值时不会发生内存泄漏，**析构函数和栈展开**：

把这个返回值放到一个本地变量里，并确保其析构函数会删除该对象
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

void foo()
{
    ...
    shape_wrapper ptr_wrapper(create_shape(...));
    ...
}
```
在析构函数里做必要的清理工作，这就是 RAII 的基本用法：
* 关闭文件
* 释放同步锁
* 释放其他重要的系统资源

e.g.
```c++
std::mutex mtx;

void some_func()
{
    std::lock_gard<std::mutex> guard(mtx);
    // 需要同步的工作
}

// 而不是
std::mutex mtx;

void some_func()
{
    mtx.lock();
    // 需要同步的工作
    // 如果发生异常或提前返回，下面这一句不会自动执行
    mtx.unlock();
}
```

# 5. QA
在 C++ 里，用 `Obj obj;` 这种方式定义的对象，在函数里就是栈上分配，在函数外就是静态分配

