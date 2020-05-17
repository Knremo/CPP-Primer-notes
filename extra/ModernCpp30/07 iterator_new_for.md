# 1. 什么是迭代器
在 C++17 之前，begin 和 end 返回的类型 I 和 S 必须是相同的。从 C++17 开始，I 和 S 可以是不同的类型

Iterator: 支持 ++ 和 *
|-> OutputIterator: 用 * 输出
|-> InputIterator: 用 * 读取, 相等比较
    |-> ForwardIterator: 可反复读取
        |-> BidirectionIterator: 支持 --
            |-> RandomAccessIterator: 支持跳跃 + - += -=, [], 和大小比较
                |-> ContiguousIterator: 存储连续

# 2. 常用迭代器
* vector::iterator, array::iterator 连续迭代器
* deque::iterator 随机访问迭代器
* list::iterator 双向迭代器
* forward_list::iterator 前向迭代器

back_inserter 返回的 back_inserter_iterator ，在容器尾部进行插入操作

ostream_iterator, 输出迭代器
```c++
#include <algorithm> // std::copy
#include <iterator> // std::back_inserter
#include <vector> // std::vector

using namespace std;
vector<int> v1{1,2,3,4,5};
vector<int> v2;
copy(v1.begin(), v1.end(), back_inserter(v2));

#include <iostream>
copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));
```

# 3. 使用输入行迭代器
