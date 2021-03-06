# 4.1 基础
## 4.1.1 基本概念
一元，二元，三元运算符

### 组合运算符和运算对象
### 运算对象转换
### 重载运算符
### 左值和右值
当一个对象被用作右值时，用的是对象的值；当对象被用作左值时，用的是对象的身份（在内存中的位置）

在需要右值的地方可以用左值代替

`decltype`作用于左值得到一个引用类型，假定`int *p`，解引用生成左值，所以`decltype(*p)`的结果是`int&`

取地址符生成右值，所以`decltype(&p)`的结果是`int**`

## 4.1.2 优先级与结合律

## 4.1.3 求值顺序
```c++
&& //注意
||
?:
,
```

# 4.2 算术运算符
```c++
+ //一元正号
- //一元负号

* //乘法
/ //除法
% //求余

+ //加法
- //减法
```
左结合

整数相除丢掉小数部分

除法中商向0取整

`m%n`的符号与m相同，`m%(-n) == m%n`,`(-m)%n == -(m%n)`

# 4.3 逻辑和关系运算符
```c++
! //右结合

< //
<= //
> //
>= //

== //
!= //

&& //当且仅当左侧为真时才对右侧求值

|| //当且仅当左侧为假时才对右侧求值
```

# 4.4 赋值运算符
左侧运算对象必须是一个可修改的左值

结果是左侧运算对象，所以
```c++
int i;
if (i = 0) cout << 1 << endl; //不会有0
if (i = 1) cout << 2 << endl; //只有1
```

右结合律
```c++
string s1, s2;
s1 = s2 = "OK";
```

优先级低
```c++
int i;
while ((i = get_value()) != 42) {}
```

复合赋值运算符
```c++
+=
-=
*=
/=
%=

<<=
>>=
&=
^=
|=
```

# 4.5 递增和递减运算符
```c++
int i = 0, j;
j = ++i; //j=1,i=1,前置版本得到递增之后的值
j = i++; //j=1,i=2,后置版本得到递增之前的值
```

### 混用解引用和递增运算符
```c++
auto pbeg = v.begin();
while (pbeg != v.end() && *pbeg >= 0)
    cout << *pbeg++ <<endl;
```

# 4.6 成员访问运算符
`ptr->mem` == `(*ptr).mem`

# 4.7 条件运算符
`cond?expr1:expr2;`

### 嵌套条件运算符
```c++
finalgrade = (grade > 90) ? "high pass" 
                          : (grade < 60) ? "fail" : "pass";
```
### 在输出表达式中使用条件运算符
```c++
cout << ((grade < 60) ? "fail" : "pass");
```

# 4.8 位运算符
```c++
~ //位求反
<< //左移
>> //右移
& //位与
^ //位异或
| //位或
```
移位、位求反、位与、位异或、位或运算符会提升为int

bitset
```c++
#inculde <bitset>

char x = 'q';
cout << bitset<32>(x << 6) << endl; //32 == sizeof(int)*8
```

# 4.9 sizeof运算符
所得值为size_t类型
```c++
sizeof(type)
sizeof expr
```
```c++
char* p = "abc";
char pp[] = "abc";

sizeof(p) // 8, 64位cpu的指针都是八字节
sizeof(pp) // 4, 返回的是数组的长度，包括末尾的\0

p[3] == pp[3]  // 都可以下标索引

cout << p <<endl;
cout << pp << endl; // 都没有问题
```
# 4.10 逗号运算符
真正的结果是右侧表达式的值
```c++
vector<int>::size_type cnt = ivec.size();

for(vector<int>::size_type ix = 0;
                 ix != ivec.size(); ++ix, --cnt)
    ivec[ix] = cnt;
```

# 4.11 类型转换
### 发生隐式类型转换
* 大多数表达式中，比int小的整型值首先提升为较大的整型类型
* 在条件中，非布尔值转换成布尔类型
* 初始化中，初始值转换成变量的类型；赋值中，右侧对象转换成左侧的类型

## 4.11.1 算术转换
### 整型提升
提升为int

### 无符号类型的运算对象

### 理解算术转换

## 4.11.2 其他隐式类型转换
### 数组转换成指针
decltype, &, sizeof, typeid时，转换不会发生，

### 指针的转换
### 转换成布尔类型
### 转换成常量
### 类类型定义的转换

## 4.11.3 显式转换
### static_cast
只要不包含底层const
```c++
int i, j;
double slope = static_cast<double>(j) / i;
```

找回void*指针中的值
```c++
void* p = &d;
double *dp = static_cast<double*>(p);
```

### const_cast
```c++
const char *pc;
char *p = const_cast<char*>(pc);
```
改变运算对象的底层const

### reinterpret_cast
```c++
int *ip;
char *pc = reinterpret_cast<char*>(ip);
```

### 旧式强制类型转换

# 4.12 运算符优先级表
p166