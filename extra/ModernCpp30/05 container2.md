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

严格弱序关系(strict weak ordering)
