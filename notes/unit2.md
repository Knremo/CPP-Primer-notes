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