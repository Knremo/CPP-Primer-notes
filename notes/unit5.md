# 5.1 简单语句
### 空语句
```c++
while (cin >> s && s != sought)
    ;
```
### 别多写分号
### 块

# 5.2 语句作用域

# 5.3 条件语句
## 5.3.1 if语句
### 悬垂else
else与离它最近的尚未匹配的if匹配

```c++
if(...) {
    if(...)
        ...;
} else
    ...;
```
## 5.3.2 switch语句
```c++
while (cin >> ch)
{
    switch(ch) 
    {
        case 'a':
            ++aCnt;
            break;
        case 'e':
            ++eCnt;
            break;
    }
}
```

case标签必须是整型常量表达式

### switch内部控制流
匹配到一个case之后会执行之后的所有case
```c++
switch(ch) {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
        ++Cnt;
        break;
}
```

### default标签
```
switch() {
    ...
    default:
        ...;
}
```

# 5.4 迭代语句
## 5.4.1 while语句

## 5.4.2 for语句
init-statement只能有一条声明语句，可以定义多个对象

## 5.4.3 范围for语句
```c++
for (declaration : expression)
    statement
```
expression表示一个序列，花括号初始值列表、数组...

declaration需要写操作声明成引用类型

## 5.4.4 do while语句
```c++
do {
    ...;
} while (condition);
```

# 5.5 跳转语句
## 5.5.1 break语句
while, do while, for, switch

## 5.5.2 continue语句
## 5.5.3 goto语句
同一函数内
```c++
goto label;
...
label: return;
```

# 5.6 try语句块和异常处理
## 5.6.1 throw表达式
```c++
#include <stdexcept>

...
throw runtime_error("A message!");
```

## 5.6.2 try语句块
```c++
try {
    program
} catch (exception) {
    ...
} catch (exception) {
    ...
}
```
### 编写处理代码
```c++
#include <stdexcept>

try {
    ...
    throw runtime_error("A message!");
} catch (runtime_error err) {
    ...
}
```
没有找到任何匹配的catch子句，转到terminate

## 5.6.3 标准异常
exception 头文件定义exception,默认初始化

stdexcept 头文件

```c++
exception
runtime_error
range_error  //超出有意义的值域范围
overflow_error //计算上溢
underflow_error //计算下溢
logic_error //逻辑错误
domain_error //参数对应的结果值不存在
invaild_argument //无效参数
length_error //超出长度
out_of_range //超出有效范围
```

new 头文件定义了bad_alloc,默认初始化
type_info 头文件定义bad_cast,默认初始化