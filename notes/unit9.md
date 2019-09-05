# 9.1 顺序容器概述
```c++
vector //可变大小，支持快速随机访问，在尾部之外的位置插入或删除元素可能很慢
deque //双端队列，支持快速随机访问，在头部尾部插入删除很快
list //双向链表，只支持双向顺序访问，任何位置插入删除很快
forward_list //单向链表，单向顺序访问，任何位置插入删除都很快
array //固定大小数组，支持快速随机访问，不能添加删除
string //与vector相似
```

# 9.2 容器库概览
```c++
//类型别名
iterator //迭代器类型
const_iterator //
size_type //
difference_type //距离
value_type //元素类型
reference //元素的左值类型
const_reference //

//构造函数
C c;
C c1(c2); //拷贝
C c(b, e); //构造c，将be指定范围内的元素拷贝到c(array不支持)
C c(a, b, c...); //列表初始化

//赋值与swap
c1 = c2 //
a.swap(b) //交换ab元素
swap(a, b) //==

//大小
c.size() //不支持forward_list
c.max_size() //可保存的最大元素数目
c.empty() //

//添加/删除元素(不适用array)
c.insert(args) //将args中的元素拷贝进c
c.emplace(inits) //使用inits构造c中的一个元素
c.erase(args) //删除
c.clear() //删除所有元素

//关系运算符
==, !=
<, <=, >, >=

//获取迭代器
c.begin(), c.end()
c.cbegin(), c.cend()

//反向容器的额外成员(不支持forward_list)
reverse_iterator
const_reverse_iterator
c.rbegin(), c.rend()
c.crbegin(), c.crend()
```
## 9.2.1 迭代器