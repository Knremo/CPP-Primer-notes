# 1. 认识 lambda
C++11 引入

lambda 表达式是一个变量，可以在调用点就地定义函数，限制它的作用域和生命周期，实现函数的局部化

**捕获外部变量**
```cpp
int n = 10;
auto func = [=](int x)
{
    cout << x*n << endl;
};

func(3);
```
闭包

# 2. lambda 注意事项
## 2.1 lambda 的形式
```cpp
auto f1 = [](){};
```

**良好的缩进格式**
```cpp
auto f2 = []()                 // 定义一个lambda表达式
{
    cout << "lambda f2" << endl;

    auto f3 = [](int x)         // 嵌套定义lambda表达式
    {
        return x*x;
    };// lambda f3              // 使用注释显式说明表达式结束

    cout << f3(10) << endl;
};  // lambda f2               // 使用注释显式说明表达式结束
```

## 2.2 lambda 的变量捕获
* [=] 表示按值捕获所有外部变量，表达式内部是值的拷贝，并且不能修改
* [&] 是按引用捕获所有外部变量，内部以引用的方式使用，可以修改
* 可以在 [] 里指定变量名，指定按值还是按引用

```cpp
int x = 33;
auto f1 = [=]()
{
    // x += 10; // 按值捕获，不允许修改
}；
auto f2 = [&]()
{
    x += 10;
};
auto f3 = [=, &x]()
{
    x += 20; // x 是引用，其它按值捕获
};
```
**外部变量**：
upvalue

在 lambda 表达式定义之前所有出现的变量，不管它是局部还是全局

如果把lambda表达式看成一个常规的变量，那么相同作用域（比如同一个函数）内的变量跟常量对它都是可见的

**捕获this**

## 2.3 泛型 lambda
```c++
auto f = [](const auto& x)
{
    return x + x;
};
```

