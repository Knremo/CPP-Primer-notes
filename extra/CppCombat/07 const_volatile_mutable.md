# 1. const 和 volatile
const 定义的常量在预处理阶段并不存在，而是直到运行阶段才会出现

volatile 禁止编译器做优化,变量在内存中

# 2. const
**常量引用**和**常量指针**
```cpp
int x = 100;

const int& rx = x;
const int* px = &x;
```
const 放在声明的最左边，表示指向常量的指针

const 在“*”的右边，表示指针不能被修改，而指向的变量可以被修改

**const 成员函数**
函数的执行过程是 const 的，不会修改对象的状态（即成员变量）

# 3. mutable
mutable 却只能修饰类里面的成员变量，表示变量即使是在 const 对象里，也是可以修改的

换句话说，就是标记为 mutable 的成员不会改变对象的状态，也就是不影响对象的常量性，所以允许 const 成员函数改写 mutable 成员变量
```cpp
class DemoClass final
{
private:
    mutable mutex_type  m_mutex;    // mutable成员变量
public:
    void save_data() const          // const成员函数
    {
        // do someting with m_mutex
    }
};
```

# 4. 其他
C++11 里 mutable 又多了一种用法，可以修饰 lambda 表达式

C++11 引入了新关键字 constexpr，能够表示真正的编译阶段常量，甚至能够编写在编译阶段运行的数值函数

