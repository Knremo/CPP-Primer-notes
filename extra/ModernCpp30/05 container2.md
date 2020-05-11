# 1. 函数对象及其特化

## less
```c++
template <class T>
struct less: binary_function<T, T, bool> {
    bool operator() (const T& x, const T& y) const
    {
        return x < y;
    }
};
```
less 是一个函数对象，二元函数，执行对任意类型值的比较，返回布尔类型

C++ 默认会使用 less，相反顺序可以使用 greater

## hash
把一个某类型的值转换成一个无符号整数哈希值，类型为 `size_t`

没有可用的默认实现，对于常用的类型，系统提供了需要的特化
```c++
template <class T> struct hash;

template <>
struct hash<int>: public unary_function<int, size_t> {
    size_t operator()(int v) const noexcept
    {
        return static_cast<size_t>(v);
    }
};
```

# 2. priority_queue
容器适配器，顺序内部排序，less，最大的数值出现在顶部

push, pop, top
```c++
#include <functional> // std::greater
#include <iostream> // std::cout/endl
#include <memory> // std::pair
#include <queue> // std::priority_queue
#include <vector>

using namespace std;

int main()
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({1,1});
    q.push({2,2});
    q.push({0,3});
    q.push({9,4});

    while (!q.empty()) {
        cout << q.top() << endl;
        q.pop();
    }
}

/*
(0,3)
(1,1)
(2,2)
(9,4)
*/
```

# 3. 关联容器
set, map, multiset, multimap

```c++
set<int> s{1,1,1,2,3,4};

multiset<int, greater<int>> ms{1,1,1,2,3,4};

map<string, int> mp{
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4}
};
mp.insert({"four",4});
mp.find("four") == mp.end()
mp.find("five") == mp.end()
mp["five"] = 5;
mp.find("four")->second // 4
mp.lower_bound("four")->second // 4 第一个不小于的元素
(--mp.upper_bound("four"))->second // 4 第一个大于

multimap<string, int> mmp{
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4}
};
mmp.insert({"four", -4});
mp.lower_bound("four")->second // 4 第一个不小于的元素
(--mp.upper_bound("four"))->second // -4 第一个大于

// 区间
#include <tuple>
multimap<string, int>::iterator lower, upper;
std::tie(lower, upper) = mmp.equal_range("four");
// 检测区间非空
(lower != upper) // true
lower->second // 4
upper->second // -4
```
关联容器默认 less 排序，对于自定义类型，重载 <

存储在关联容器中的健一般应满足严格弱序关系(strict weak ordering)

通过比较来进行查找、插入、和删除，复杂度为对数 O(log(n)), 有没有达到更好的性能的方法？

# 4. 无序关联容器
unordered_set, unordered_map, unordered_multiset, unordered_multimap

不要求提供一个排序的函数对象，而要求一个可以计算哈希值的函数对象

通常使用 hash

```c++
#include <complex> // std::complex
#include <iostream> // 
#include <unordered_map>
#include <unordered_set>
#include "output_container.h"

using namespace std;

namespace std {

template <typename T>
struct hash<complex<T>> {
    size_t operator()(const complex<T>& v) const noexcept
    {
        hash<T> h;
        return h(v.real()) + h(v.imag());
    }
};

} // namespace std

int main()
{
    unordered_set<int> s{
        1,1,2,3,5,8,13,21
    };
    cout << s << endl;
    unordered_map<complex<double>, double> umc{
        {{1.0, 1.0}, 1.4142},
        {{3.0, 4.0}, 5.0}
    };
    cout << umc << endl;
}
```
在 std 名空间中添加了特化，这是少数用户可以向 std 名空间添加内容的情况之一

性能

# 5. array
array 保留了 C 数组在栈上分配的特点，提供 begin, end, size 等
```c++
#include <array>
#include <iostream>
#include <map>
#include "output_container.h"

typedef std::array<char, 8> mykey_t;

int main()
{
    std::map<mykey_t, int> mp;
    mykey_t mykey{"hello"};
    mp[mykey] = 5; // ok
    std::cout << mp << std::endl;
}
```
可以作为键
