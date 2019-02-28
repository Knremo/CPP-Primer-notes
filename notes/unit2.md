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