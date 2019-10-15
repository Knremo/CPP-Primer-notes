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

