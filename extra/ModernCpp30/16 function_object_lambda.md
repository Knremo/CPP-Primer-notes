# 1. C++ 98 的函数对象
函数对象（function object） 自 C++98 开始就已经被标准化了

# 2. 函数的指针和引用
除非你用一个引用模板参数来捕捉函数类型，传递给一个函数的函数实参会退化成为一个函数指针。不管是函数指针还是函数引用，你也都可以当成函数对象来用。

```c++
int add_2(int x)
{
  return x + 2;
};
```
```c++
template <typename T>
auto test1(T fn)
{
  return fn(2);
}

template <typename T>
auto test2(T& fn)
{
  return fn(2);
}

template <typename T>
auto test3(T* fn)
{
  return (*fn)(2);
}
```
当我们拿 add_2 去调用这三个函数模板时，fn 的类型将分别被推导为 `int (*)(int)`、`int (&)(int)` 和 `int (*)(int)`

不管我们得到的是指针还是引用，我们都可以直接拿它当普通的函数用.在函数指针的情况下，我们直接写 *value 也可以

# 3. lambda 表达式
```c++
auto add_2 = [](int x) { return x + 2; };
```
* Lambda 表达式一般不需要说明返回值（相当于 auto）；有特殊情况需要说明时，则应使用箭头语法的方式：`[]​(int x) -> int { … }`

* 每个 lambda 表达式都有一个全局唯一的类型，要精确捕捉 lambda 表达式到一个变量中，只能通过 auto 声明的方式

```c++
auto adder = [](int n) {
    return [n](int x) {
        return x + n;
    };
};

auto seven = adder(2)(5);
```
捕获 n 的效果相当于在一个函数对象中用成员变量存储其数值

**常见用法**
```c++
transform(v.begin(), v.end(), v.begin(),
          [](int x) { return x + 2; };);
```

**立即求值**
```c++
[](int x) { return x * x; }(3)
```
免去了我们定义一个 constexpr 函数的必要。只要能满足 constexpr 函数的条件，一个 lambda 表达式默认就是 constexpr 函数

**解决多重初始化路径**
```c++
auto obj = [init_mode]() {
  switch (init_mode) {
  case init_mode1:
    return Obj(…);
    break;
  case init_mode2:
    return Obj(…);
    break;
  …
  }
}();
```

## 变量捕获
变量捕获的开头是可选的默认捕获符 = 或 &，表示会自动按值或按引用捕获用到的本地变量，然后后面可以跟（逗号分隔）：
* 本地变量名标明对其按值捕获（不能在默认捕获符 = 后出现；因其已自动按值捕获**所有本地变量**）
* `&` 加本地变量名标明对其按引用捕获（不能在默认捕获符 & 后出现；因其已自动按引用捕获**所有本地变量**）
* `this` 标明按引用捕获外围对象（针对 lambda 表达式定义出现在一个非静态类成员内的情况）；注意默认捕获符 = 和 & 号可以**自动捕获 this**（并且在 C++20 之前，在 = 后写 this 会导致出错）
* `*this` 标明按值捕获外围对象（针对 lambda 表达式定义出现在一个非静态类成员内的情况；C++17 新增语法）
* `变量名 = 表达式` 标明按值捕获表达式的结果（可理解为 auto 变量名 = 表达式）
* `&变量名 = 表达式` 标明按引用捕获表达式的结果（可理解为 auto& 变量名 = 表达式）

按值捕获是比较安全的做法,按引用捕获时则需要更小心些，必须能够确保被捕获的变量和 lambda 表达式的生命期至少一样长，并在有下面需求之一时才使用：

* 需要在 lambda 表达式中修改这个变量并让外部观察到
* 需要看到这个变量在外部被修改的结果
* 这个变量的复制代价比较高

希望以移动的方式来捕获某个变量的话，则应考虑 `变量名 = 表达式` 的形式。表达式可以返回一个 prvalue 或 xvalue，比如可以是 `std::move(需移动捕获的变量)`

```c++
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

using namespace std;

int get_count()
{
    static int count = 0;
    return ++count;
}

class task {
public:
    task(int data) : data_(data) {}
    auto lazy_launch()
    {
        return [*this, count = get_count()]() mutable
        {
            ostringstream oss;
            oss << "Done work " << data_ 
                << " (No. " << count 
                << ") in thread " 
                << this_thread::get_id() << '\n';
            msg_ = oss.str();
            calculate();
        };
    }
    void calculate()
    {
        this_thread::sleep_for(100ms);
        cout << msg_;
    }

private:
    int data_;
    string msg_;
};

int main()
{
    auto t = task{37};
    thread t1{t.lazy_launch()};
    thread t2{t.lazy_launch()};
    t1.join();
    t2.join();
}
```
* `mutable` 标记使捕获的内容可更改
* `[*this]` 按值捕获外围对象（task）
* `[count = get_count()]` 捕获表达式可以在生成 lambda 表达式时计算并存储等号后表达式的结果

将 `*this` 改成 `this` 则是在同一个线程

# 4. 泛型 lambda 表达式
```c++
auto sum = [](auto x, auto y) { return x + y; };
```

# bind 模板
