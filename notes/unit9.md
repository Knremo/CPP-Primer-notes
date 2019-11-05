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
## 9.3.1 向顺序容器添加元素
```c++
//not array
c.push_back(t)
c.emplace_back(args)

c.push_front(t)  //头部创建元素
c.emplace_front(args)

c.insert(p, t) //在迭代器p之前创建，返回新创建元素的迭代器
c.emplace(p, args)

c.insert(p, n, t) //迭代器p之前插入n个t

c.insert(p, b, e) //将be之间的元素插入

c.insert(p, il) //将花括号il中的元素插入
```
forward_list 有自己专用版本的insert和emplace

forward_list 不支持push_back和emplace_back

vector string 不支持push_front emplace_front

向一个vector，string，deque插入元素会使指针迭代器引用失效

### 使用push_back

### 使用push_front
list,forward_list,deque

### 使用insert的返回值
反复插入元素

### emplace操作
构造元素
```c++
c.emplace_back("0909-0989876", 25, 15.99);

c.push_back(Sales_data("0909-0989876", 25, 15.99));
```

## 9.3.2 访问元素
```c++
//at and [] 只适用于string vector deque array
//back 不适用 forward_list
c.back()
c.front()
c[n]
c.at[n] //如果越界抛出out_of_range异常
```
## 访问成员函数返回的是引用
```c++
auto &v = c.back();
v = 1024;
```
## 9.3.3 删除元素
```c++
//forward_list 有特殊版本的erase
//forward_list不支持pop_back
//vector不支持pop_front
c.pop_back()
c.pop_front()
c.erase(p) //返回被删元素之后的元素的迭代器
c.erase(b, e)
c.clear() //删除所有元素
```
删除奇数
```c++
list<int> lst = {0,1,2,3,4,5};
auto it = lst.begin();
while (it != lst.end())
    if (*it % 2)
        it = lst.erase(it);
    else
        ++it;
```
 ## 9.3.4 特殊的forward_list操作
 单向链表
 ```c++
lst.before_begin()
lst.cbefore_begin()

lst.insert_after(p, t) //再p之后插入t，n是数量，be是迭代器范围，il是花括号列表
lst.insert_after(p, n, t)
lst.insert_after(p, b, e)
lst.insert_after(p, il)

emplace_after(p, args) //构造一个元素

lst.erase_after(p)
lst.erase_after(b, e)
```
## 9.3.5 改变容器大小
array不支持
```c++
c.resize(n) 
c.resize(n, t) //新元素初始化为t
```

## 9.3.6 迭代器失效
```c++
list<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
auto iter = vi.begin();
while (iter != vi.end())
{
    if (*iter % 2)
    {
        iter++;
        iter = vi.insert(iter, 12); //在iter之前插入
        iter++;
    }
    else
        iter = vi.erase(iter);
}
```

```c++
while (begin != vi.end())
    {
        if (*begin % 2)
            begin = vi.insert(begin, *begin++);  
        ++begin;
    }
```
# 9.4 vector对象是如何增长的
```c++
//shrink_to_fit 只适用 vector, string, deque
//capacity和reserve只适用vector,string
c.shrink_to_fit()
c.capacity()
c.reserve(n)
```

# 9.5 额外的string操作
```c++
string s(cp, n) //cp指向的数组中前n个字符的拷贝

string s(s2, pos2) //是s2从下标pos2开始的字符的拷贝

string s(s2, pos2, len2) //pos2开始的len2个字符

s.substr(pos, n) //返回一个string，s中从pos开始的n个字符
s.substr() //所有字符
```
## 9.5.2 改变string的其他办法
```c++
s.insert(s.size(), 5, '!'); //s的末尾插入5个！
s.erase(s.size()-5, 5); //删除最后5个字符串,个数

const char *cp = "Sdddd";
s.assign(cp, 3); //"Sdd"
s.insert(s.size(), cp + 7) //将cp前7个字符插入

//string s1, s2
s.insert(0, s2); //在s中位置0之前插入s2的拷贝
s.insert(0, s2, 0, s2.size()); //在s[0]之前插入s2中的s2[0]开始的s2.size()个字符

s2.append("ssss");

s2.replace(11, 3, "sdasdas") //从位置11开始删除3个字符并插入
```

## 9.5.3 string搜索操作
返回下标`string::size_type`类型，如果搜索失败，返回一个`string::npos`
```c++
string name("AnnaBelle");
auto pos1 = name.find("Anna");
// 0
//大小写敏感

//与任何一个字符匹配
string numbers("0123456789"), name("r2d2");
auto pos = name.find_first_of(numbers);
//搜索第一个非数字字符
string dept("03714p3");
auto pos = dept.find_first_not_of(numbers);

s.find_last_of(args)

s.find_last_not_of(args)
//args
c, pos //从s中位置pos开始查找字符c，默认0
s2, pos //string
cp, pos //c风格字符串指针
cp,pos, n //前n个字符
```
查找所有字符
```c++
string::size_type pos = 0;
while ((pos = name.find_first_of(numbers, pos)) != string::npos)
{
    cout << "found number at index: " << pos
         << "element is " << name[pos] << endl;
    ++pos;
}
```
逆向搜索
`rfind`
## 9.5.4 compare函数
s.compare(args)
```c++
s2 //与s2比较
pos1, n1, s2 //将s中pos1开始的n1个字符与s2比较
pos1, n1, s2, pos2, n2 //

cp 
pos1, n1, cp
pos1, n1, cp, n2
```
## 9.5.5 数值转换
```c++
to_string(val) //返回val的string表示

stoi(s, p, b)  //返回类型为int,long,unsigned long,...
stol(s, p, b)  //p为size_t指针，s中第一个非数字字符的下标，默认为0
stoul(s, p, b) //b表示转换的基数，默认10
stoll(s, p, b) 
stoull(s, p, b) 

stof(s, p) //浮点数
stod(s, p) 
stold(s, p) 
```
```c++
string s2 = "pi = 3.14";
d = stod(s2.substr(s2.find_first_of("+-.0123456789")));
```
# 9.6 容器适配器
所有适配器都支持
```c++
size_type
value_type
container_type //底层容器类型
A a;
A a(c); //创建一个a适配器带有c的拷贝
==,!=,<,<=,>,>=
a.empty()
a.size()
swap(a,b)
a.swap(b)
```
## 定义适配器
```c++
stack<int> stk(deq);
// stack queue 默认是基于deque

stack<string, vector<string>> str_stk;
```
stack: 除array和forward_list

queue: list, deque, vector

priority_queue: vector, deque

## 栈适配器
```c++
s.pop()
s.push()
s.emplace()
s.top()
```
## 队列适配器
queue默认基于deque实现，priority_queue默认基于vector实现

queue先进先出，priority_queue按优先级
```c++
q.pop() //返回queue首元素或priority_queue最高优先级元素
q.front()
q.back() //只适用于queue
q.top() //返回最高优先级元素，只适用priority_queue
q.push(item) //创建
q.emplace(args)
```
