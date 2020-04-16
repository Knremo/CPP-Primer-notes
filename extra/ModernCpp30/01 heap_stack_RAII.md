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

