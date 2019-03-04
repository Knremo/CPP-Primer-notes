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
`extern int i;` //声明

## 2.2.3 标识符
以字母，下划线开头.自定义标识符不能出现连续两个下划线，也不能以下划线紧连大写字母开头，定义在函数体外的标识符不能以下划线开头。

## 2.2.4 名字的作用域
允许内层作用域中重新定义外层作用域已有的名字。

# 2.3 复合类型
## 2.3.1 引用

```c++
int ival = 1024;
int &refVal = ival;
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
int *p1 = nullptr;
int *p2 = 0;
```
### void* 指针
### 指向指针的指针
### 指向指针的引用
```c++
int *p;
int *&r = p;
```

# 2.4 const 限定符
`const int bufSize = 512;`

多个文件共享
```c++
extern const int bufSize = fcn(); //file.cpp
extern const int bufSize;       //file.h
```

## 2.4.1 const的引用
```c++
const int ci = 1024;
const int &r1 = ci; //right
r1 = 42; //wrong
int &r2 = ci; //wrong
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