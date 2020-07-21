# 1. 函数式编程的特点
纯函数（pure function），要点在于：
* 会影响函数结果的只是函数的参数，没有对环境的依赖
* 返回的结果就是函数执行的唯一后果，不产生对环境的其他影响

一些函数式编程的特点：
* 函数就像普通的对象一样被传递、使用和返回。
* 代码为说明式而非命令式。在熟悉函数式编程的基本范式后，你会发现说明式代码的可读性通常比命令式要高，代码还短。
* 一般不鼓励（甚至完全不使用）可变量。

# 2. 高阶函数
* sort
* transform
* accumulate
* fmap
* adder

map, reduce, filter
* transform
* accumulate
* copy_if, partition

`copy_if` 是把满足条件的元素拷贝到另外一个迭代器里

`partition` 则是根据过滤条件来对范围里的元素进行分组，把满足条件的放在返回值迭代器的前面

`remove_if` 通常用于删除满足条件的元素。它确保把不满足条件的元素放在返回值迭代器的前面（但不保证满足条件的元素在函数返回后一定存在），然后你一般需要使用容器的 erase 成员函数来将待删除的元素真正删除

# 3. 不可变性和并发
函数式编程强调不可变性（immutability）、无副作用，天然就适合并发

C++17 的并行执行策略
```c++
int count_lines(const char** begin,
                const char** end)
{
  vector<int> count(end - begin);
  transform(execution::par,
            begin, end,
            count.begin(),
            count_file);
  return reduce(
    execution::par,
    count.begin(), count.end());
}
```

# 4. Y 组合子
```c++
#include <functional>
#include <iostream>
#include <type_traits>
#include <utility>

using namespace std;

// Y combinator as presented by Yegor Derevenets in P0200R0
// <url:http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html>
template <class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template <class T>
    explicit y_combinator_result(T&& fun) : fun_(std::forward<T>(fun)) {}

    template <class... Args>
    decltype(auto) operator()(Args&&... args)
    {
        // y(f) = f(y(f))
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template <class Fun>
decltype(auto) y_combinator(Fun&& fun)
{
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

int main()
{
  // 上面的那个 F
  auto almost_fact = [](auto f, int n) -> int {
    if (n == 0)
        return 1;
    else
        return n * f(n - 1);
  };
  // fact = y(F)
  auto fact = y_combinator(almost_fact);
  cout << fact(10) << endl;
}
```

# 5. 实现一个惰性迭代器
