# 6.1 函数基础
### 编写函数
### 调用函数
### 形参和实参
求值顺序

### 形参列表
```c++
void f1() {} //空形参列表
void f2(void) {}
```
每个形参都有类型

函数最外层中的局部变量不能使用与函数形参一样的名字

### 返回类型
不能是数组或函数，但可以是指向的指针

## 6.1 局部对象
名字有作用域，对象有作用周期

### 自动对象
### 局部静态对象
```c++
static int cnt = 0;
```
## 6.1.2 函数声明
使用前声明，函数原型

```c++
void print(vector<int>::const_iterator beg,
           vector<int>::const_iterator end);
```
分号，可以不要参数名字

### 在头文件中声明
头文件中声明，源文件中定义

包含头文件

## 6.1.3 分离式编译
### 编译链接

# 6.2 参数传递
引用传递、值传递
## 6.2.1 传值参数
### 指针形参
```c++
void reset(int *ip)
{
    *ip = 0;
    ip = 0;
}
```
实参所指的对象的值改变，实参的值没有改变

## 6.2.2 传引用参数
```c++
void reset(int &i)
{
    i = 0;
}
```
### 使用引用避免拷贝
大的对象
### 使用引用形参返回额外信息

## 6.2.3 const形参和实参
当形参有顶层const时，传给它常量对象或者非常量对象都可以

### 指针或引用形参与const
调用引用形参，只能是int，字面值、int表达式、const int不能

调用指针形参，只能int*

常量引用形参可以用字面值初始化

### 尽量使用常量形参
```c++
string::size_type find_char(const string &s, char c, 
                            string::size_type &occurs);
```
否则只能作用于string对象，字面值就不行

## 6.2.4 数组形参
```c++
void print(const int*);
void print(const int[]);
void print(const int[10]);
```
### 使用标记指定数组长度
C风格字符串空字符
```c++
void print(const char *cp)
{
    if (cp)    //不是空指针
        while (*cp) //不是空字符
            cout << *cp++;
}
```
### 使用标准库规范
```c++
void print(const int *beg, const int *end)
{
    while (beg != end)
        cout << *beg++ << endl;
}
```

`print(begin(j), end(j));`

### 显式传递一个表示数组大小的形参
```c++
void print(const int ia[], size_t size)
{
    ...
}

print(j, end(j) - begin(j));
```
### 数组引用参数
```c++
void print(int (&arr)[10])
{
    for (auto elem : arr)
        cout << elem << endl;
}
```
### 传递多维数组
```c++
void print(int (*matrix)[10], int rowSize) {}

void print(int matrix[][10], int rowSize) {}
```

## 6.2.5 main:处理命令行选项
```c++
int main(int argc, char *argv[]) {}
```
argv是一个数组，它的元素指向C风格字符串的指针；argc表示数组中字符串额数量

也可以定义为
```c++
int main(int argc, char **argv) {}
```
argv[0]是程序的名字

## 6.2.6 含有可变形参的函数
### initializer_list形参
类型相同

initializer_list头文件
```c++
initializer_list<T> lst; //默认初始化
initializer_list<T> lst{a,b,c...}; //lst的元素是对应初始值的副本，const
lst2(lst)
lst2 = lst //拷贝或赋值之后共享元素
lst.size() //元素数量
lst.begin() 
lst.end()
```

可变数量的实参：
```c++
void error_msg(initializer_list<string> il)
{
    for (auto beg - il.begin(); beg != il.end(); ++beg)
        cout << *beg << " ";
    cout << endl;
}

error_msg({"a", "dwdwdw", "ggggg"});
```
还可以使用范围for
```c++
for (auto &elem : il)
    ...
```

### 省略符形参
使用varargs的C标准库

```c++
void foo(parm_list, ...);
void foo(...);
```

# 6.3 返回类型和return语句
## 6.3.1 无返回值函数
void函数 return

## 6.3.2 有返回值函数
### 值是如何被返回的

### 不要返回局部对象的引用或指针

### 引用返回左值

### 列表初始化返回值
```c++
return {"a", "b", "c"};
```
### 主函数main的返回值
cstdlib头文件
```c++
return EXIT_FAILURE;
//
return EXIT_SUCCESS;
```
### 递归

## 6.3.3 返回数组指针
```c++
typedef int arrT[10];
//or
using arrT = int[10];

arrT* func(int i);
```
### 不使用别名的声明
```c++
int (*func(int i))[10];
```
### 使用尾置返回类型
```c++
auto func(int i) -> int(*)[10];
```
### 使用decltype
```c++
int odd[] = {1, 3, 5, 7,9};
int even[] = {0, 2, 4, 6, 8};

decltype(odd) *arrPtr(int i)
{
    return (i % 2) ? &odd : &even;
}
```

# 6.4 函数重载
### 定义重载函数
形参不同

### 重载和const形参
一个拥有顶级const的形参无法和没有的区分
```c++
Record lookup(Phone);
Record lookup(const Phone); //wrong

Record lookup(Phone*);
Record lookup(Phone* const); //wrong
```
底层const可以
```c++
Record lookup(Phone&);
Record lookup(const Phone&); 

Record lookup(Phone*);
Record lookup(const Phone*); 
```

### const_cast

## 6.4.1 重载与作用域
内层同名会覆盖外层声明

内层没有就会暴露外面所有的

# 6.5 特殊用途语言特性
## 6.5.1 默认实参
