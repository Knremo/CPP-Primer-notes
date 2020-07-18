# 1. constexpr
* constexpr 变量
* constexpr 函数

一个 constexpr 变量是一个编译时完全确定的常数

一个 constexpr 函数至少对于某一组实参可以在编译期间产生一个编译期常数

* constexpr 变量必须立即初始化
* 初始化只能使用字面量或常量表达式，后者不允许调用任何非 constexpr 函数

下面的代码可以工作：
```c++
#include <array>
constexpr int sqr(int n) { return n * n; }

int main()
{
    constexpr int n = sqr(3);
    std::array<int, n> a;
    int b[n];
}
```

# 2. constexpr 和编译期计算
阶乘函数：
```c++
constexpr int factorial(int n)
{
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

constexpr int n = factorial(10); // ok
```
在这个 constexpr 函数里，是不能写 static_assert(n >= 0) 的。一个 constexpr 函数仍然可以作为普通函数使用.显然，传入一个普通 int 是不能使用静态断言的

替换方法是在 factorial 的实现开头加入：
```c++
if (n < 0) {
    throw std::invalid_argument("Arg must be non-negative");
}
```

# 3. constexpr 和 const
本质上，const 用来表示一个**运行时常量**

从编译器的角度，为了向后兼容性，const 和 constexpr 在很多情况下还是等价的。但有时候，它们也有些细微的区别，其中之一为是否**内联**的问题

## 内联变量
C++17 引入了内联（inline）变量的概念，允许在头文件中定义内联变量，然后像内联函数一样，只要所有的定义都相同，那变量的定义出现多次也没有关系

对于**类的静态数据成员**，const 缺省是不内联的，而 constexpr 缺省就是内联的

```c++
#include <iostream>
#include <vector>

struct magic {
  static const int number = 42;
};

int main()
{
  std::cout << magic::number << std::endl; // ok
  
  std::vector<int> v;
  // 调用 push_back(const T&) ODR-use
  v.push_back(magic::number); // 报错
  std::cout << v[0] << std::endl;
}
```
这是因为 ODR-use 的类静态常量也需要有一个定义，在没有内联变量之前需要在某一个源代码文件（非头文件）中这样写：
```c++
const int magic::number = 42;
```
修正这个问题的简单方法是把 magic 里的 `static const` 改成 `static constexpr` 或 `static inline const`

## constexpr 变量模板
变量模板是 C++14 引入的新概念
```c++
template <class T>
inline constexpr bool is_trivially_destructible_v =
    is_trivially_destructible<T>::value;
```

## constexpr 变量仍是 const
!!!!编译失败
```c++
constexpr int a = 42;
constexpr const int& b = a;
```
第二行里，constexpr 表示 b 是一个编译期常量，const 表示这个引用是常量引用

# 4. constexpr 构造函数和字面类型
一个合理的 constexpr 函数，应当至少对于某一组编译期常量的输入，能得到编译期常量的结果。为此，对这个函数也是有些限制的：
* 最早，constexpr 函数里连循环都不能有，但在 C++14 放开了。
* 目前，constexpr 函数仍不能有 try … catch 语句和 asm 声明，但到 C++20 会放开。
* constexpr 函数里不能使用 goto 语句。
* 等等。

如果一个类的构造函数里面只包含常量表达式、满足对 constexpr 函数的限制的话（这也意味着，里面不可以有任何动态内存分配），并且类的析构函数是平凡的，那这个类就可以被称为是一个**字面类型**

为了全面支持编译期计算，C++14 开始，很多标准类的构造函数和成员函数已经被标为 constexpr，以便在编译期使用

面这些不使用动态内存分配的字面类型则可以在常量表达式中使用：
* array
* initializer_list
* pair
* tuple
* string_view
* optional
* variant
* bitset
* complex
* chrono::duration
* chrono::time_point
* shared_ptr(仅限默认构造和空指针构造)
* unique_ptr(仅限默认构造和空指针构造)

```c++
#include <array>
#include <iostream>
#include <memory>
#include <string_view>

using namespace std;

int main()
{
    constexpr string_view sv{"hi"};
    constexpr pair pr{sv[0], sv[1]};
    constexpr array a{pr.first, pr.second};
    constexpr int n1 = a[0];
    constexpr int n2 = a[1];
    cout << n1 << ' ' << n2 << '\n';
}
```

## if constexpr
C++17
```c++
template <typename C, typename T>
void append(C& container, T* ptr, size_t size)
{
  if constexpr (has_reserve<C>::value) {
    container.reserve(container.size() + size);
  }
  for (size_t i = 0; i < size; ++i) {
    container.push_back(ptr[i]);
  }
}
```

# 5. output_container.h 解读
```c++
// Type trait to detect std::pair
template <typename T>
struct is_pair : std::false_type {};
template <typename T, typename U>
struct is_pair<std::pair<T, U>> : std::true_type {}; // 特化
template <typename T>
inline constexpr bool is_pair_v = is_pair<T>::value;
```
```c++
// Type trait to detect whether an
// output function already exists
template <typename T>
struct has_output_function {
    template <class U>
    static auto output(U* ptr) -> decltype(
        std::declval<std::ostream&>() << *ptr, // ptr是nullptr，但是可以做<<的测试,不能实际使用
        std::true_type());
    template <class U>
    static std::false_type output(...);
    static constexpr bool value = decltype(output<T>(nullptr))::value;
};
template <typename T>
inline constexpr bool has_output_function_v =
    has_output_function<T>::value;
```
这段代码使用 SFINAE 技巧，来检测模板参数 T 的对象是否已经可以直接输出到 ostream。然后，一样用一个内联 constexpr 变量来简化表达。

```c++
// Element output function for containers that define a key_type
// and have its value type as std::pair
template <typename T, typename Cont>
auto output_element(std::ostream& os, 
                    const T& element, 
                    const Cont&, 
                    const std::true_type)
    -> decltype(std::declval<typename Cont::key_type>(), os)
{
    os << element.first << " => " << element.second;
    return os;
}
// Element output function for other containers
template <typename T, typename Cont>
auto output_element(std::ostream& os,
                    const T& element, 
                    const Cont&,
                    ...) -> decltype(os)
{
    os << element;
    return os;
}
```
对于容器成员的输出，我们也声明了两个不同的重载。我们的意图是，如果元素的类型是 pair 并且容器定义了一个 `key_type` 类型，我们就认为遇到了关联容器，输出形式为“x => y”（而不是“(x, y)”）

```c++
// Main output function, enabled only if no output function already exists
template <typename T,
          typename = std::enable_if_t<!has_output_function_v<T>>>
auto operator<<(std::ostream& os, const T& container)
    -> decltype(container.begin(), container.end(), os)
{
    using std::decay_t;
    using std::is_same_v;

    using element_type = decay_t<decltype(*container.begin())>;
    constexpr bool is_char_v = is_same_v<element_type, char>;
    if constexpr (!is_char_v) {
        os << '{';
    }
    auto end = container.end();
    bool on_first_element = true;
    for (auto it = container.begin(); it != end; ++it) {
        if constexpr (is_char_v) {
            if (*it == '\0') {
                break;
            }
        } else {
            if (!on_first_element) {
                os << ", ";
            } else {
                os << ' ';
                on_first_element = false;
            }
        }
        output_element(os, *it, container, is_pair<element_type>()); // 标签分发
    }
    if constexpr (!is_char_v) {
        if (!on_first_element) {  // Not empty
            os << ' ';
        }
        os << '}';
    }
    return os;
}
```
* 对于类型 T ，如果有输出函数，则 `!has_output_function_v<T>` 为假，`enable_if_t` 就未定义，模板匹配出错，就忽略下面的重载函数
* 其次，类型 T 必须有 `begin()`  和 `end()` 成员函数
* 如果是 char 元素，则直接一个个输出
* 其他的则是 { ., ., . }

```c++
// Output function for std::pair
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& pr)
{
    os << '(' << pr.first << ", " << pr.second << ')';
    return os;
}
```
针对 pair 的重载，pair 就是 (x,y)