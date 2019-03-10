# 3.1 命名空间的using声明
`using std::cin;`

# 3.2 标准库类型string
```c++
#include <string>
using std::string;
```
## 3.2.1 定义和初始化string对象
```c++
string s1;
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

第一个对应的字符中小的较小

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
for (auto c : str)
    cout << c << endl;
```
### 只处理一部分字符
下标运算符,string::size_type类型

`s[0]`

### 使用下标执行迭代
```c++
for (decltype(s.size()) index = 0;
    index != s.size() && !isspace(s[index]); ++index)
        s[index] = toupper(s[index]);
```