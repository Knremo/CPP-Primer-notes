# 1. optional
C++17

构造一个 optional<T> 对象有以下几种方法：
1. 不传递任何参数，或者使用特殊参数 std::nullopt（可以和 nullptr 类比），可以构造一个“空”的 optional 对象，里面不包含有效值。 
2. 第一个参数是 std::in_place，后面跟构造 T 所需的参数，可以在 optional 对象上直接构造出 T 的有效值。
3. 如果 T 类型支持拷贝构造或者移动构造的话，那在构造 optional<T> 时也可以传递一个 T 的左值或右值来将 T 对象拷贝或移动到 optional 中。

第 1 种情况，optional 对象里是没有值的，在布尔值上下文里，会得到 false

对于上面的第 2、3 两种情况，optional 对象里是有值的，在布尔值上下文里，会得到 true

在 optional 对象有值的情况下，你可以用 * 和 -> 运算符去解引用（没值的情况下，结果是未定义行为）

* 安全的析构行为
* 显式的 has_value 成员函数，判断 optional 是否有值
* value 成员函数，行为类似于 *，但在 optional 对象无值时会抛出异常 std::bad_optional_access
* value_or 成员函数，在 optional 对象无值时返回传入的参数
* swap 成员函数，和另外一个 optional 对象进行交换
* reset 成员函数，清除 optional 对象包含的值
* emplace 成员函数，在 optional 对象上构造一个新的值（不管成功与否，原值会被丢弃）
* make_optional 全局函数，产生一个 optional 对象（类似 make_pair、make_unique 等）
* 全局比较操作

e.g.
```c++
template <typename T>
constexpr bool has_value(const optional<T>& x) noexcept
{
    return x.has_value();
}

template <typename T, typename... Args>
constexpr bool has_value(const optional<T>& first, 
                         const optional<Args>&... args) noexcept
{
    return first.has_value() && has_value(other...);
}

template <typename F>
auto lift_optional(F&& f)
{
    return [f = forward<F>(f)](auto&&... args) {
        typedef decay_t<decltype(f(forward<decltype(args)>(args).value()...))> result_type; // f(a,b)
        if (has_value(args...)) {
            return optional<result_type>(f(forward<decltype(args)>(args).value()...));
        } else {
            return optional<result_type>();
        }
    };
}
```
最后返回的则是 result_type 的 optional 封装。函数内部会检查所有的参数是否都有值（通过调用 has_value）：有值时会去拿参数的值去调用原先的函数，否则返回一个空的 optional 对象

使用：
```c++
#include <iostream>
#include <functional>
#include <optional>
#include <type_traits>
#include <utility>
using namespace std;

constexpr int increase(int n)
{
    return n + 1;
}

ostream& operator<<(ostream& os, optional<int>(x))
{
    if (x) {
        os << '(' << *x << ')';
    } else {
        os << "(Nothing)";
    }
    return os;
}

int main()
{
    auto inc_opt = lift_optional(increase);
    auto plus_opt = lift_optional(plus<int>());
    cout << inc_opt(optional<int>()) << endl;
    cout << inc_opt(make_optional(41)) << endl;
    cout << plus_opt(make_optional(41), optional<int>()) << endl;
    cout << plus(make_optional(41), make_optional(1)) << endl;
}
```
结果：
> (Nothing)
> (42)
> (Nothing)
> (42)

# 2. variant
optional 要么是你想放进去的对象，要么是 nullopt

希望除了我们想放进去的对象，还可以是 nullopt 之外的对象

可以用 union ，不建议

variant:
```c++
variant<string, int, char> obj{"Hello world"};
cout << get<string>(obj) << endl;
```
构造时使用的是 `const char*`，但构造函数仍然能够正确地选择 string 类型，这是因为标准要求实现在没有一个完全匹配的类型的情况下，会选择成员类型中能够以传入的类型来构造的那个类型进行初始化（有且只有一个时）

string 类存在形式为 `string(const char*)` 的构造函数，所以上面的构造能够正确进行

variant 上可以使用 get 函数模板，其模板参数可以是**代表序号的数字**，也可以是**类型**

variant 上还有一个重要的成员函数是 index，通过它我们能获得当前的数值的序号，正常情况下，variant 里总有一个有效的数值（缺省为第一个类型的默认构造结果），但如果发生了异常，variant 里也可能没有任何有效数值，此时 `index()` 将会得到 `variant_npos`

# 3. expected
 不是 C++ 标准里的类型

一个 `expected<T, E>` 差不多可以看作是 `T` 和 `unexpected<E>` 的 variant
```c++
#include <climits>
#include <iostream>
#include <string>
#include <tl/expected.hpp>
using namespace std;
using tl::expected;
using tl::unexpected;

expected<int, string> safe_divide(int i, int j)
{
    if (j == 0)
        return unexpected("divide by zero"s); // 字面量后缀
    if (i == INT_MIN && j == -1)
        return unexpected("integer divide overflows"s);
    if (i % j != 0)
        return unexpected("not integer division"s);
    else
        return i / j;
}

// 支持 expected 的输出函数
template <typename T, typename E>
ostream& operator<<(  ostream& os,  const expected<T, E>& exp)
{  
    if (exp) {    
        os << exp.value();  
    } else {    
        os << "unexpected: " << exp.error();  
    }  
    return os;
}

// 一个测试函数
expected<int, string>caller(int i, int j, int k)
{  
    auto q = safe_divide(j, k);  
    if (q)    
        return i + *q;  
    else    
        return q;
}

// 调试使用的检查宏
#define CHECK(expr)                                  \
{                                                    \    
    auto result = (expr);                            \    
    cout << result;                                  \    
    if (result == unexpected("divide by zero"s)) {   \      
        cout << ": Are you serious?";                \    
    } else if (result == 42) {                       \      
        cout << ": Ha, I got you!";                  \
    }                                                \    
    cout << endl;                                    \  
}

int main()
{  
    CHECK(caller(2, 1, 0));  
    CHECK(caller(37, 20, 7));  
    CHECK(caller(39, 21, 7));
}
```
* 如果一个函数要正常返回数据，代码无需任何特殊写法；如果它要表示出现了异常，则可以返回一个 unexpected 对象
* 这个返回值可以用来和一个正常值或 unexpected 对象比较，可以在布尔值上下文里检查是否有正常值，也可以用 * 运算符来取得其中的正常值, 与 optional 类似，在没有正常值的情况下使用 * 是未定义行为
* 可以用 value 成员函数来取得其中的正常值，或使用 error 成员函数来取得其中的错误值——与 variant 类似，在 expected 中没有对应的值时产生异常 bad_expected_access

# 4. Herbception
