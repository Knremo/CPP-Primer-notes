# 10.1 概述
```c++
auto result = find(vec.cbegin(), vec.cend(), val);
```

# 10.2 初识泛型算法
## 10.2.1 只读算法
find,count,
```c++
int sum = accumulate(vec.cbegin(), vec.cend(), 0);
// 求和（迭代器范围，和的初值）
// int double long string
```