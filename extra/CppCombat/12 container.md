# 1. 容器的通用特性
保存元素采用值语义

尽量为元素实现转移构造和转移赋值函数
```cpp
Point p;

v.push_back(p);
v.push_back(std::move(p));
```
也可以使用 C++11 新增的 emplace()，可以“就地”构造元素，免去了构造后再拷贝、转移的成本，不但高效，而且用起来也很方便

# 2. 容器的具体特性
## 2.1 顺序容器
顺序容器就是数据结构里的线性表，一共有 5 种：array、vector、deque、list、forward_list

按照存储结构，这 5 种容器又可以再细分成两组。
* 连续存储的数组：array、vector 和 deque。
* 指针结构的链表：list 和 forward_list。

**array 和 vector 直接对应 C 的内置数组，内存布局与 C 完全兼容，所以是开销最低、速度最快的容器。它们两个的区别在于容量能否动态增长。**

deque 也是一种可以动态增长的数组，它和 vector 的区别是，它**可以在两端高效地插入删除元素**，这也是它的名字 double-end queue 的来历，而 vector 则只能用 push_back 在末端追加元素
```c++
deque<int> d;                  // 初始化一个deque，长度是0
d.emplace_back(9);              // 末端添加一个元素
d.emplace_front(1);              // 前端添加一个元素
assert(d.size() == 2);          // 长度动态增长到2
```

vector 和 deque 里的元素因为是连续存储的，所以**在中间的插入删除效率就很低**，而 list 和 forward_list 是链表结构，插入删除操作只需要调整指针，所以**在任意位置的操作都很高效**

链表的缺点是查找效率低，只能沿着指针顺序访问，这方面不如 vector 随机访问的效率高。list 是双向链表，可以向前或者向后遍历，而 forward_list 是单向链表

链表结构比起数组结构还有一个缺点，就是**存储成本略高**，因为必须要为每个元素附加一个或者两个的指针，指向链表的前后节点

当 vector 的容量到达上限的时候（capacity），它会再分配一块两倍大小的新内存，然后把旧元素拷贝或者移动过去，deque、list 只会按照固定的“步长”（例如 N 个字节、一个节点）去增加容量

## 2.2 有序容器
元素在插入容器后就被按照某种规则自动排序

C++ 的有序容器使用的是树结构，通常是红黑树——有着最好查找性能的二叉树

标准库里一共有四种有序容器：set/multiset 和 map/multimap

有序容器与顺序容器的另一个根本区别，在**定义容器的时候必须要指定 key 的比较函数**。通常是默认的 less：
```cpp
template <class T> 
class vector;                      // vector

template<class Key, class Compare = std::less<Key>> 
class set;                        // 集合

template<class Key, class T, class Compare = std::less<Key>> 
class map;                        // 关联数组
```

自定义类型没有默认的比较函数,解决这个问题有两种办法：
* 一个是重载“<”
* 另一个是自定义模板参数

```cpp
bool operator<(const Point& a, const Point& b)
{
    return a.x < b.x;            // 自定义比较运算
}

set<Point> s;                    // 现在就可以正确地放入有序容器
s.emplace(7);
s.emplace(3);
```
```cpp
set<int> s = {7, 3, 9};           // 定义集合并初始化3个元素

auto comp = [](auto a, auto b)  // 定义一个lambda，用来比较大小
{   
    return a > b;                // 定义大于关系
};  

set<int, decltype(comp)> gs(comp)  // 使用decltype得到lambda的类型

std::copy(begin(s), end(s),          // 拷贝算法，拷贝数据
          inserter(gs, gs.end()));  // 使用插入迭代器

for(auto& x : gs) {                // 范围循环输出元素
    cout << x << ",";                // 从大到小排序，9,7,3
}
```
## 2.3 无序容器
内部数据结构：它不是红黑树，而是散列表

unordered_set/unordered_multiset、unordered_map/unordered_multimap

要求 key 具备两个条件，

一是可以计算 hash 值，二是能够执行相等比较操作。

第一个是因为散列表的要求，只有计算 hash 值才能放入散列表，第二个则是因为 hash 值可能会冲突，所以当 hash 值相同时，就要比较真正的 key 值

**自定义类型也就可以放进无序容器**
```cpp
template<
    class Key,                          // 第一个模板参数是key类型
    class T,                            // 第二个模板参数是元素类型
    class Hash = std::hash<Key>,        // 计算散列值的函数对象
    class KeyEqual = std::equal_to<Key> // 相等比较函数
> class unordered_map; 
```

散列函数就略麻烦一点，你可以用函数对象或者 lambda 表达式实现，内部最好调用标准的 std::hash 函数对象，而不要自己直接计算，否则很容易造成 hash 冲突：
```cpp
bool operator==(const Point& a, const Point& b)
{
    return a.x == b.x;              // 自定义相等比较运算
}

auto hasher = [](const auto& p)    // 定义一个lambda表达式
{
    return std::hash<int>()(p.x);  // 调用标准hash函数对象计算
};

unordered_set<Point, decltype(hasher)> s(10, hasher);
```