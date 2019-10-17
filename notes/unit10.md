# 10.1 概述
```c++
auto result = find(vec.cbegin(), vec.cend(), val);
```

# 10.2 初识泛型算法
## 10.2.1 只读算法
find,count,

accumulate
```c++
#include <numeric>

int sum = accumulate(vec.cbegin(), vec.cend(), 0);
// 求和（迭代器范围，和的初值）
// int double long string
```

equal
```c++
equal(roster1.cbegin(), roster1.end(), roster2.cbegin());
// true or false
```
## 10.2.2 写容器元素的算法
### fill
```c++
fill(vec.begin(), vec.end(), 0);
```
### fill_n
```c++
fill_n(vec.begin(), vec.size(), 0);
```
### back_inserter
```c++
#include <iterator>

vector<int> vec;

auto it = back_inserter(vec); //返回一个迭代器
*it = 42;

fill_n(back_inserter(vec), 10, 0);
```
### 拷贝算法
内置数组的拷贝
```c++
int a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int a2[sizeof(a1)/sizeof(*a1)]; //a2与a1大小相同

auto ret = copy(begin(a1), end(a1), a2); //返回目的位置末尾的迭代器，a2至少要有a1的长度
```

replace
```c++
replace(ilst.begin(), ilst.end(), 0, 42);

//不改变原序列
replace_copy(ilst.begin(), ilst.end(), back_inserter(ivec), 0, 42);
```

