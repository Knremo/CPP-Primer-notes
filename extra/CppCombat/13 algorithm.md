# 1. 迭代器
```cpp
vector<int> v = {1,2,3,4,5};    // vector容器

auto iter1 = v.begin();        // 成员函数获取迭代器，自动类型推导
auto iter2 = v.end();
```
或者 begin(), end(), cbegin(), cend()

迭代器和指针类似，也可以前进和后退，但你不能假设它一定支持“++”“--”操作符，最好也要用函数来操作，常用的有这么几个：
* distance()，计算两个迭代器之间的距离；
* advance()，前进或者后退 N 步；
* next()/prev()，计算迭代器前后的某个位置。

```cpp
array<int, 5> arr = {0,1,2,3,4};  // array静态数组容器

auto b = begin(arr);          // 全局函数获取迭代器，首端
auto e = end(arr);            // 全局函数获取迭代器，末端

assert(distance(b, e) == 5);  // 迭代器的距离

auto p = next(b);              // 获取“下一个”位置
assert(distance(b, p) == 1);    // 迭代器的距离
assert(distance(p, b) == -1);  // 反向计算迭代器的距离

advance(p, 2);                // 迭代器前进两个位置，指向元素'3'
assert(*p == 3);
assert(p == prev(e, 2));     // 是末端迭代器的前两个位置
```

# 2. 最有用的算法
## for_each
```cpp
vector<int> v = {3,5,1,7,10};   // vector容器

for(const auto& x : v) {        // range for循环
    cout << x << ",";
}

auto print = [](const auto& x)  // 定义一个lambda表达式
{
    cout << x << ",";
};
for_each(cbegin(v), cend(v), print);// for_each算法

for_each(                      // for_each算法，内部定义lambda表达式
    cbegin(v), cend(v),        // 获取常量迭代器
    [](const auto& x)          // 匿名lambda表达式
    {
        cout << x << ",";
    }
);
```
## sort
* 要求排序后仍然保持元素的相对顺序，应该用 stable_sort，它是稳定的；
* 选出前几名（TopN），应该用 partial_sort；
* 选出前几名，但不要求再排出名次（BestN），应该用 nth_element；
* 中位数（Median）、百分位数（Percentile），还是用 nth_element；
* 按照某种规则把元素划分成两组，用 partition；
* 第一名和最后一名，用 minmax_element。
```cpp
// top3
std::partial_sort(
    begin(v), next(begin(v), 3), end(v));  // 取前3名

// best3
std::nth_element(
    begin(v), next(begin(v), 3), end(v));  // 最好的3个

// Median
auto mid_iter =                            // 中位数的位置
    next(begin(v), v.size()/2);
std::nth_element( begin(v), mid_iter, end(v));// 排序得到中位数
cout << "median is " << *mid_iter << endl;
    
// partition
auto pos = std::partition(                // 找出所有大于9的数
    begin(v), end(v),
    [](const auto& x)                    // 定义一个lambda表达式
    {
        return x > 9;
    }
); 
for_each(begin(v), pos, print);         // 输出分组后的数据  

// min/max
auto value = std::minmax_element(        //找出第一名和倒数第一
    cbegin(v), cend(v)
);
```
它们对迭代器要求比较高，通常都是**随机访问迭代器**（minmax_element 除外），所以最好在顺序容器 array/vector 上调用

list 容器，应该调用成员函数 sort()，它对链表结构做了特别的优化

## search
binary_search，在已经排好序的区间里执行二分查找。它只返回一个 bool 值，告知元素是否存在
```cpp
auto found = binary_search(cbegin(v), cend(v), 7); 
```

lower_bound  大于等于值的第一个位置

upper_bound  第一个大于值的元素
```cpp
auto pos = std::lower_bound(cbegin(v), cend(v), 7);
auto found = (pos != cend(v)) && (*pos == 7); // 可能找不到，所以必须要判断
assert(found);                          // 7在容器里
```

对于有序容器 set/map，就不需要调用这三个算法了，它们有等价的成员函数 find/lower_bound/upper_bound   

find

用于查找区间的 find_first_of/find_end
```cpp
vector<int> v = {1,9,11,3,5,7};  // vector容器

decltype(v.end()) pos;          // 声明一个迭代器，使用decltype

pos = std::find(begin(v), end(v), 3);// 查找算法，找到第一个出现的位置
      
assert(pos != end(v));         // 与end()比较才能知道是否找到

pos = std::find_if(            // 查找算法，用lambda判断条件
    begin(v), end(v),
    [](auto x) {              // 定义一个lambda表达式
        return x % 2 == 0;    // 判断是否偶数
    }
);  
assert(pos == end(v));        // 与end()比较才能知道是否找到

array<int, 2> arr = {3,5};    // array容器
pos = std::find_first_of(      // 查找一个子区间
    begin(v), end(v),
    begin(arr), end(arr)
);  
assert(pos != end(v));       // 与end()比较才能知道是否找到
```

## 其他
copy/move

all_of/any_of

equal_range 算法可以一次性获得 [lower_bound, upper_bound)

C++17 允许算法并行处理，需要传递 std::execution::par等策略参数

C++20 引入了 range，不必显式写出 begin(),end(), 重载了 |

