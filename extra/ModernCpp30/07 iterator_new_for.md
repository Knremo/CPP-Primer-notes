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
把一个输入流的内容一行行读进来，用 range for
```c++
for (const string& line : istream_line_reader(is)) {
    cout << line << endl;
}

// 如果用传统 for
string line;
for (;;) {
    getline(is, line);
    if (!is) {
        break;
    }
    cout << line << endl;
}
```

## 定义输入行迭代器
C++ 里有些固定的类型要求规范，对于一个迭代器，需要定义下面的类型：
```C++
class istream_line_reader {
public:
    class iterator {
    public:
        typedef ptrdiff_t difference_type; // 迭代器之间距离的类型
        typedef string value_type; // 迭代器指向的对象的值类型
        typedef const value_type* pointer; // 迭代器指向的对象的指针类型
        typedef const value_type& reference; // 常引用
        typedef input_iterator_tag iterator_category; // 标识这个迭代器的类型是 input iterator
        ...
    };
    ...
};
```
