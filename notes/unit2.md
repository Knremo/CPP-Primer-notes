# 2.1 基本内置类型
## 2.1.1 算术类型
|类型|最小bits|
|-----|-----|
|bool|-|
|char|8|
|wchar_t|16|
|char16_t|16|
|char32_t|32|
|short|16|
|int|16|
|long|32|
|long long|64|
|float|6位有效数字|
|double|10位有效数字|
|long double|10位有效数字|

### 带符号和无符号类型

除`bool`,`wchar_t`,`char16_t`,`char32_t`,分为`signed`和`unsigned`.

`unsigned`=`unsigned int`.

`char`由编译器决定是`signed char` or `unsigned char`.

## 2.1.2 类型转换

* `bool b = 42` //初始值为0结果为false,否则为true

* `int i = 3.14`//i=3,仅保留浮点数中小数点之前的部分

* `unsigned char c = -1` //c=255

* `signed char c2 = 256` //undefined

### 含有无符号类型的表达式
算术表达式中既有无符号数又有int值时，int值会转换成无符号数.

从无符号数中减去一个值时，不管这个值是不是无符号数，须确保结果不为负.

## 2.1.3 字面值常量
### 整型和浮点型字面值
`20 024 0x14` 十进制类型是int,long,long long中尺寸最小的；八进制十六进制是int,unsigned int,unsigned long,unsigned long long.

`3.14 3.14E0 0. 0e0 .001` double.

### 字符和字符串字面值
`'a'`

`"Hello World!"` 字符数组，结尾有`'\0'`.

```
std::cout << "c1"
             "c2" << std::endl;
```

### 转义序列
```
\n //换行符
\t //tab
\a //alert
\v //纵向制表符
\b //backspace
\"
\\
\?
\'
\r //回车符
\f //进纸符
```

`'\115' or '\x4d'` = `'M'`
`\u5359`

### 指定字面值类型
|前缀|类型|
|---|---|
|u|char16_t|
|U|char32_t|
|L|wchar_t|
|u8|char|

|后缀|类型|
|---|---|
|u or U|unsigned|
|l or L|long|
|ll or LL|long long|
|f or F|float|
|l or L|long double|

# 2.2 变量
## 2.2.1 变量定义
初始化和赋值不同

定义在函数体内部的内置类型变量将不被初始化，值是未定义.

## 2.2.2 变量声明和定义的关系
`extern int i;` //声明而不定义

在函数体内初始化一个`extern`标记的变量引发错误

## 2.2.3 标识符
以字母，下划线开头.自定义标识符不能出现连续两个下划线，也不能以下划线紧连大写字母开头，定义在函数体外的标识符不能以下划线开头。

## 2.2.4 名字的作用域
允许内层作用域中重新定义外层作用域已有的名字。

# 2.3 复合类型
## 2.3.1 引用
必须初始化
```c++
int ival = 1024;
int &refVal = ival;

int &refVal = 10; //wrong, 引用必须是一个对象，左值引用
```

## 2.3.2 指针

```c++
double dval;
double *pd = &dval;
double *pd2 = pd;

int ival = 42;
int *p = &ival;
cout << *p;  //解引用符
```

```c++
int i = 42;
int &r = i;     //声明，引用
int *p;         //声明，指针
p = &i;         //表达式，取地址符
*p = i;         //表达式，解引用符
int &r2 = *p;   //&是声明的一部分，*是解引用符
```

### 空指针
```c++
int *p1 = nullptr; //c++11,可以转换为任意类型
int *p2 = 0;

// #include <cstdlib>
int *p3 = NULL; //==0
```
### void* 指针
存放任意类型

### 指向指针的指针

### 指向指针的引用
```c++
int *p;
int *&r = p;
```

# 2.4 const 限定符
`const int bufSize = 512;`

必须初始化，可以用字面值

多个文件共享
```c++
extern const int bufSize = fcn(); //file.cpp
extern const int bufSize;       //file.h
```

## 2.4.1 const的引用
对常量的引用
```c++
const int ci = 1024;
const int &r1 = ci; //right
r1 = 42; //wrong
int &r2 = ci; //wrong

//可以用非常量、字面值、表达式初始化
const int &r = 0; //right
```

## 2.4.2 指针和const
### 指向常量的指针
```c++
const double pi = 3.14;
double *ptr = &pi;  //wrong
const double *cptr = &pi;   //right
*cptr = 42; //wrong
```
允许一个指向常量的指针指向一个非常量对象
```c++
double dval = 3.14;
cptr = &dval;   //right
```

### 常量指针
```c++
int errNumb = 0;
int *const curErr = &errNumb;
const double pi = 3.14159;
const double *const pip = &pi;
```

## 2.4.3 顶层const

顶层const(top-level const):指针本身是个常量

底层const(low-level const):指针所指的对象是一个常量

## 2.4.4 constexpr和常量表达式
### constexpr变量

声明constecpr,由编译器验证

```c++
constexpr int mf = 20;
constexpr int limit = mf + 1;
constexpr int sz = size();   //size是一个constexpr函数
```
### 字面值类型
算术类型，引用，指针

### 指针和constexpr
```c++
const int *p = nullptr; //指向常量的指针
constexpr int *p = nullptr; //常量指针
```

```c++
constexpr int *np = nullptr;
int j = 0;
constexpr int i = 42;

//i和j都必须定义在函数体外
constexpr const int *p = &i;
constexpr int *p1 = &j;
```

# 2.5 处理类型
## 2.5.1 类型别名
### 类型别名
1. typedef 
```c++
typedef double wages;
typedef wages base, *p; //base是double的同义词，p是double*的同义词.
```

2. 别名声明
```c++
using SI = Sales_item;
```
### 指针、常量和类型别名
使人迷惑
```c++
typedef char *pstring; // == char*
const pstring cstr = 0;  //指向char的常量指针，而非指向常量字符的指针
const pstring *ps; //指向char的常量指针的指针
```
## 2.5.2 auto类型说明符
auto定义的变量必须有初始值
`auto i = 0, *p = &i;`

### 复合类型、常量和auto
以引用对象的类型作为auto的类型
```c++
int i = 0, &r = i;
auto a = r;  //a is int
```
auto一般会忽略顶层const，底层const会保留
```c++
const int ci = i, &cr = ci;  //top-level const
auto b = ci; // int b = ci;
auto c = cr;// c int
auto d = &i; //int pointer
auto e = &ci; //const int pointer, low-level const
```
需要顶层const
```c++
const auto f = ci; //f : const int
```
将引用的类型设为auto
```c++
auto &g = ci; //整型常量的引用
auto &h = 42; //wrong,不能为非常量引用绑定字面值
const auto &j = 42; //right
```

## 2.5.3 decltype类型指示符
```c++
const int ci = 0, &cj = ci;
decltype(ci) x = 0; //x: const int
decltype(cj) y = x; //y: const int&
decltype(cj) z; //wrong,z是一个引用，必须初始化
```

### decltype和引用
```c++
int i = 42, *p = &i, &r = i;
decltype(r+0) b; //right,r+0这个表达式的结果将是一个具体指而不是引用，所以r+0是int
decltype(*p) c; //wrong,解引用将得到引用类型，c是int&，必须初始化
```
变量加括号结果是引用
```c++
decltype((i)) d; //wrong,int&，必须初始化
decltype(i) e; //right,int
```

# 2.6 自定义数据结构
## 2.6.1 定义Sales_data类型
```c++
struct Sales_data{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
```
### 类数据成员
没有初始值的成员将被默认初始化

初始值不能使用圆括号

## 2.6.2 使用Sales_data类

## 2.6.3 编写自己的头文件
### 预处理器概述
头文件保护符

```c++
#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
struct Sales_data {
    ...
};
#endif
```