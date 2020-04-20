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
工厂方法：
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

class shape_wrapper {
public:
    explicit shape_wrapper(shape* ptr=nullptr): ptr_(ptr) {}
    ~shape_wrapper()
    {
        delete ptr_;
    }
    shape* get() const { return ptr_; }
private:
    shape* ptr_;
};

```

