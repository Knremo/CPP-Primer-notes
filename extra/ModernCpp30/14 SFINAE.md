替换失败非错（substitution failure is not an error），简称 SFINAE

# 1. 函数模板的重载决议
重载决议过程大致如下：
* 根据名称找出所有适用的函数和函数模板
* 对于适用的函数模板，要根据实际情况对模板形参进行替换；替换过程中如果发生错误，这个模板会被丢弃
* 在上面两步生成的可行函数集合中，编译器会寻找一个最佳匹配，产生对该函数的调用
* 如果没有找到最佳匹配，或者找到多个匹配程度相当的函数，则编译器需要报错

```c++
#include <stdio.h>
struct Test {
    typedef int foo;
};

template <typename T>
void f(typename T::foo)
{
    puts("1");
}

template <typename T>
void f(T)
{
    puts("2");
}

int main()
{
    f<Test>(10);
    f<int>(10);
}
```
output:
> 1
> 2

分析 `f<Test>(10);`：
* 有两个模板符合名字 f
* 替换结果为 `f(Test::foo)` 和 `f(Test)`
* 10 去匹配，10 是 int，所以只有前者可以匹配，被选择

分析 `f<int>(10)`:
* 两个模板符合名字 f
* 替换结果为 `f(int::foo)` 和 `f(int)`, 前者不合法的类型，被抛弃
* 10 匹配 `f(int)`, 没有问题

# 2. 编译期成员检测
 SFINAE 可以用于其他用途

检测一个类是否有一个名叫 reserve，参数类型为 size_t 的成员函数：
```c++
template <typename T>
struct has_reserve {
    struct good { char dummy; };
    struct bad { char dummy[2]; };
    template <class U, void (U::*)(size_t)>
    struct SFINAE {};
    template <class U>
    static good reserve(SFINAE<U, &U::reserve>*);
    template <class U>
    static bad reserve(...);
    static const bool value = sizeof(reserve<T>(nullptr)) == sizeof(good);
};

class MyContainer {
public:
    void reserve(size_t n) { puts(n); }
};
```
分析：
1. `has_reserve<MyContainer>::value` 只有一个叫做 `has_reserve` 的模板
2. 替换 `reserve<T>` 为 `reserve<MyContainer>`
3. 有两个 `reserve`, 对于第一个，`reserve(SFINAE<MyContainer,&MyContainer::reserve>*)`
4. 只有一个 `SFINAE`, `MyContainer` 匹配第一个模板参数，因为 `MyContainer::reserve` 的参数类型为 `size_t`, 返回值类型为 `void`, 所以可以成功匹配第二个模板参数 `void (U::*)(size_t)`. `SFINAE` 匹配成功，实例化成功
5. 所以第一个 `reserve` 匹配成功，实例化，传入参数 `nullptr`, 与 `SFINAE*` 匹配成功
6. 返回 `good`，再返回 `true`
7. 若 `MyContainer::reserve` 不满足，则 `SFINAE` 不能匹配，只能匹配第二个 `reserve`，返回 `bad`

我们定义常整型布尔值 value，结果是 true 还是 false，取决于 nullptr 能不能和 SFINAE* 匹配成功，而这又取决于模板参数 T 有没有返回类型是 void、接受一个参数并且类型为 size_t 的成员函数 reserve

# 3. SFINAE 模板技巧
## enable_if
