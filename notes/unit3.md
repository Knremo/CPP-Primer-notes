# 3.1 命名空间的using声明
`using std::cin;`

# 3.2 标准库类型string
```c++
#include <string>
using std::string;
```
## 3.2.1 定义和初始化string对象
```c++
string s1; //默认初始化，空string
string s2 = s1;
string s3 = "hiya"; //= string s3("hiya");
string s4(10, 'c'); // 'c'x10
```
### 直接初始化和拷贝初始化

## 3.2.2 string对象上的操作
```c++
<<
>>
getline(is, s); //从is中读取一行赋给s，返回is
s.empty(); //s为空返回true
s.size(); //返回s中字符的个数
s[n]
s1+s2
s1=s2
s1==s2
s1!=s2
<, <=, >, >=
```
### string::size_type类型
size的返回值类型

### 比较string对象
长度不同，字符相同，较短的小

第一个对应不同的字符中小的较小

### 字面值和string对象相加
每个+的两侧至少有一是string
```c++
string s1 = "hello"+","; //wrong
```
## 3.2.3 处理string对象中的字符
```c++
#include <cctype>
isalnum(c) //字母和数字
isalpha(c) //字母
iscntrl(c) //控制字符
isdigit(c) //数字
isgraph(c) //不是空格但可以打印
islower(c) //小写字母
isprint(c) //可打印字符
ispunct(c) //标点符号
isspace(c) //空白
isupper(c) //大写字母
isxdigit(c) //十六进制数字
tolower(c) //变小写
toupper(c) //变大写
```
### 范围for
```c++
string str("some string");
for (auto c : str) //c: char
    cout << c << endl;
```
`for(auto &c : str)`改变值

### 只处理一部分字符
下标运算符,string::size_type类型

`s[0]`

### 使用下标执行迭代
```c++
for (decltype(s.size()) index = 0;
    index != s.size() && !isspace(s[index]); ++index)
        s[index] = toupper(s[index]);
```

### 使用下标执行随机访问
```c++
const string hexdigits = "0123456789ABCDEF";
string result;
string::size_type n;
while(cin >> n)
    if (n < hexdigits.size())
        result += hexdigits[n];
cout << result << endl;
```

# 3.3 标准库类型vector
```c++
#include <vector>
using std::vector;
```
类模板
```c++
vector<int> ivec;
```
不包含引用

## 3.3.1 定义和初始化vector对象
```c++
vector<T> v1; //空vector,默认初始化
vector<T> v2(v1); //v2中包含v1所有元素的副本
vector<T> v2 = v1; //等价于v2(v1),v2中包含有v1所有元素的副本
vector<T> v3(n, val); //n个重复元素
vector<T> v4(n); //n个重复执行了值初始化的对象
vector<T> v5{a,b,c...};
vector<T> v5={a,b,c...};
```
拷贝元素类型需相同

### 列表初始化vector对象

## 3.3.2 向vector对象中添加元素
```c++
vector<int> v2;
for (int i = 0; i != 100; ++i)
    v2.push_back(i);
```
## 3.3.3 其他vector操作
```c++
v.empty()
v.size()
v.push_back()
v[in]
v1 = v2
v1 = {a,b,c...}
== != < <=
```
`vector<int>::size_type`

不能用下标形式添加元素

# 3.4 迭代器介绍

## 3.4.1 使用迭代器
```c++
auto b = v.begin(), e = v.end();
```
### 迭代器运算符
```c++
*iter //返回迭代器iter所指元素的引用
iter->mem //(*iter).mem
++iter
--iter
iter1 == iter2
iter1 != iter2
```
```c++
string s("some string");
if (s.begin() != s.end())
{ 
    auto it = s.begin();
    *it = toupper(*it);
}
```

### 移动迭代器
```c++
for (auto it = s.begin(); it != s.end() && !isspace(*it); ++it)
    *it = toupper(*it);
```

### 迭代器类型
```c++
vector<int>::iterator it;
vector<int>::const_iterator it2;
```

### begin和end的返回值类型
如果不是常量，返回`iterator`

`cbegin,cend`返回`const_iterator`类型

### 箭头运算符
`it->mem` = `(*it).mem`

### 迭代器失效
不要在循环中向迭代器所属的容器添加元素

## 3.4.2 迭代器运算
string和vector

```c++
iter+n //向前移动n
iter-n //向后移动n，或结尾元素下一位置
iter1 += n 
iter1 - iter2 //距离
>, >=, <, <=
```

### 迭代器的算术运算
距离类型`difference_type`

### 使用迭代器运算
```c++
auto mid = text.begin() + (end - beg)/2;
```

# 3.5 数组
## 3.5.1 定义和初始化内置数组
```c++
unsigned cnt = 42; //不是常量表达式
constexpr unsigned sz = 42; //常量表达式
int arr[10];
int *parr[sz]; //right
string bad[cnt]; //wrong
string strs[get_size()]; //constexpr function
```
### 显式初始化数组元素
```c++
string a4[3] = {"hi", "bye"};
```
### 字符数组的特殊性
```c++
char a3[] = "C++";
```
### 不允许拷贝和赋值
### 理解复杂的数组声明
```c++
int *ptrs[10];
int &refs[10] = ?; //wrong,不存在引用得到数组
int (*Parray)[10] = &arr; //指向一个含有10个整数的数组
int (&arrRef)[10] = arr; //引用一个含有10个整数的数组
int *(&arry)[10] = ptrs; //arry是数组的引用，该数组含有10个指针
```
由内向外，从右向左

## 3.5.2 访问数组元素
数组下标size_t类型，定义在cstddef头文件

范围for

## 3.5.3 指针和数组
```c++
string *p = &nums[0];
string *p2 = nums;     //等价

int ia[] = {0,1,2,3,4,5,6,7,8,9};
auto ia2(ia);  //ia2是一个整型指针，指向ia的第一个元素

decltype(ia) ia3 = {0,1,2,3,4,5,6,7,8,9}; //返回的类型是由10个整数构成的数组
```

### 指针也是迭代器
```c++
++p;
```
### 标准库函数begin和end
```c++
int ia[] = {0,1,2,3,4,5,6,7,8,9};
int *beg = begin(ia);
int *last = end(ia);  //c++11
```
定义在iterator头文件

### 指针运算
同迭代器运算

两个指针相减的结果的类型`ptrdiff_t`,定义在`cstddef`头文件

### 解引用和指针运算的交互

### 下标和指针
```c++
int k = p[-2]; 
```
内置的下标运算符所用的索引值不是无符号整数，与vector,string不同

## 3.5.4 C风格字符串
字符数组

### C标准库String函数
```c++
#include <cstring>
strlen(p); //不算空字符
strcmp(p1, p2); //p1==p2,0;p1>p2,+;p1<p2,-;
strcat(p1, p2); //将p2附到p1之后，返回p1
strcpy(p1, p2); //p2拷贝给p1，返回p1
```
必须以空字符结束

## 3.5.5 与旧代码的接口
### 混用string对象与C风格字符串
```c++
string s("Hello world");
const char *str = s.c_str();
```

### 使用数组初始化vector对象
```c++
int int_arr[] = {0, 1, 2, 3, 4, 5};
vector<int> ivec(begin(int_arr), end(int_arr));
```

# 3.6 多维数组
### 多维数组的初始化
```c++
int ia[3][4] = {
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {8, 9, 10, 11}
};

int ia[3][4] = {0,1,2,3,4,5,6,7,8,9,10,11}; //==above

int ia[3][4] = {{0},{4},{8}}; //初始化每行首元素

int ix[3][4] = {0,3,6,9}; //初始化第一行
```

### 多维数组的下标引用
```c++
int (&row)[4] = ia[1]; //把row绑定到ia的第二个4元素数组上
```
### 范围for
```c++
size_t cnt = 0;
for (auto &row : ia)
    for (auto &col : row){
        col = cnt;
        ++cnt;
    }
```
外层必须声明为引用，否则会当成指针出错。内层不需要写操作时可以不用。

### 指针和多维数组
```c++
int *ip[4];  //int指针数组
int (*ip)[4]; //指向含有4个整数的数组
```
```c++
int ia[3][4] = {};
for (auto p = ia; p != ia + 3; ++p) {
    for (auto q = *p; q != *p + 4; ++q) //指针p指向一个含有四个整数的数组，解引用之后才是该数组
        cout << *q << ' ';
    cout << endl;
}
// ==
for (auto p = begin(ia); p != end(ia); ++p) {
    for (auto q = begin(*p); q != end(*p); ++q)
    ...
}
```
### 类型别名简化
```c++
using int_array = int[4];
typedef int int_array[4]; //or

for (int_array *p = ia; p != ia + 3; ++p){
    for (int *q = *p; q != *p + 4; ++q)
        cout << *q << ' ';
}