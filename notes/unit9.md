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
左闭合区间

迭代器算术运算只能用于string, vector,deque,array

## 9.2.2 容器类型成员
反向迭代器

类型别名
```c++
list<string>::iterator iter;
vector<int>::difference_type count;
```

## 9.2.3 begin和end成员
```c++
list<string> a = {"Milton", "Shakespeare", "Austen"};
auto it1 = a.begin();
auto it2 = a.rbegin();
...
```

## 9.2.4 容器定义和初始化
```c++
C c(b, e) //c初始化为迭代器b和e指定范围中的元素的拷贝
```
定义array是除了指定元素类型，还要指定容器大小
```c++
array<int, 42>
```

## 9.2.5 赋值和swap
```c++
c1 = c2 //拷贝

c = {a, b, c...} //array不适用
swap(c1, c2) //交换c1,c2
c1.swap(c2)

//不适用关联容器和array
seq.assign(b, e)  //用迭代器be替换seq中的元素

seq.assign(il)  //初始化列表il
seq.assign(n, t) //n*t
```
赋值会导致左边内部的迭代器，引用，指针失效，swap不会

array允许赋值
```c++
array<int, 10> a1 = {0,1,2,3,4,5,6,7,8,9};
array<int, 10> a2 = {0};
a1 = a2; //ok
a2 = {0};   //xxxxx
```
### 使用assign
```c++
list<string> names;
vector<const char*> oldstyle;
names = oldstyle;  //xxxxx

names.assign(oldstyle.cbegin(), oldstyle.cend());
```
### 使用swap
交换相同类型容器的内容

## 9.2.6 容器大小操作
size

empty

max_size

## 9.2.7 关系运算符
每个容器类型都支持相等运算符(==和!=);除了无序关联容器外的所有容器都支持关系运算符(>,>=,<,<=)

# 9.3 顺序容器操作
