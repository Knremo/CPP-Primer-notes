# 重载运算与类型转换
## 14.1 基本概念
如果运算符函数是成员函数，它的左侧运算对象绑定到隐式的this指针，所以少一个参数

优先级和结合律保持一致
### 可以直接调用一个重载的运算符函数
```c++
// 非成员
data1 + data2; // ==
operator+(data1, data2);
// 成员
data1 += data2;
data1.operator+=(data2); //==
```
### 选择作为成员或者非成员
* `=, [], (), ->`必须是成员
* 复合赋值一般应该是成员
* 递增，递减，解引用应该是成员
* 算术，相等性，关系，位应该是非成员

```c++
string s = "world";
string t = s + "!";
string u = "hi" + s; // 如果+是string的成员，则等于“hi”.operator+("!"),显然const char*没有成员函数
```

## 14.2 输入输出运算符
### 14.2.1 重载输出运算符<<
```c++
...
friend operator<<(ostream&, const Sales_data&);
...


ostream &operator<<(ostream &os, const Sales_data &item)
{
    os << item.isbn();
    return os;
}
```

#### 输入输出运算符必须是非成员函数
如果是成员函数，则得是
```c++
Sales_data data;
data << cout; // data.operator<<(cout); 
// 显然不能这么写
```

### 14.2.2 重载输入运算符>>
```c++
istream &operator>>(istream &is, Sales_data &item)
{
    is >> item.bookNo;
    if (is) // 输入必须处理失败的情况
        item.revenue = 0;
    else
        item = Sales_data();
    return is;
}
```

## 14.3 算术和关系运算符
非成员
```c++
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum += rhs; // 定义一个复合赋值运算符再来定义算术运算符
    return sum;
}
```
### 14.3.1 相等运算符
```c++
bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() == rhs.isbn() &&
                  lhs.units_sold == rhs.units_sold &&
                  lhs.revenue == rhs.revenue;
}
bool operator!=(const Sales_data &lhs, const Sales_data &rhs)
{
    return !(lhs == rhs);
}
```
### 14.3.2 关系运算符
1. 定义顺序关系，令其与关联容器中对关键字的要求一致
2. 与==保持一致

## 14.4 赋值运算符
拷贝赋值，移动赋值，其他
比如
```c++
StrVec &operator=(std::initializer_list<std::string>);
```
### 复合赋值运算符
成员
```c++
Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
    ...
}
```
## 14.5 下标运算符
必须是成员函数
同时定义常量和非常量版本
```c++
std::string& operator[](std::size_t n)
{
    return elements[n];
}
const std::string& operator[](std::size_t n) const
{
    return elements[n];
}
```
## 14.6 递增和递减运算符
成员函数
### 前置版本
```c++
class StrBlobPtr{
public:
    StrBlobPtr& operator++();
    StrBlobPtr& operator--();
};
StrBlobPtr& StrBlobPtr::operator++()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}
StrBlobPtr& StrBlobPtr::operator--()
{
    --curr;
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}
```
### 区分后置运算符
后置版本赢爱返回对象的原值，返回的形式是一个值而非引用
```c++
class StrBlobPtr{
public:
    StrBlobPtr operator++(int); // 后置有一个额外的int参数，编译器赋值0，不会使用
    StrBlobPtr operator--(int);
};
StrBlobPtr StrBlobPtr::operator++(int)
{
    StrBlobPtr ret = *this;
    ++*this;
    return ret;
}
StrBlobPtr StrBlobPtr::operator--(int) // 不会用到无须命名
{
    StrBlobPtr ret = *this;
    --*this;
    return ret;
}
```
### 显式的调用后置运算符
```c++
p.operator++(0); // 后置
p.operator++(); // 前置
```
## 14.7 成员访问运算符
```c++
class StrBlobPtr{
public:
    std::string& operator*() const
    {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    std::string* operator->() const
    {
        return & this->operator*();
    }
};
```
## 14.8 函数调用运算符
必须是成员函数，可以有多个版本
```c++
struct absInt{
    int operator()(int val) const
    {
        return val < 0 ? -val : val;
    }
}

int i = -42;
absInt absObj;
int ui = absObj(i);
```
#### 含有状态的函数对象类

### 14.8.1 lambda是函数对象类
编译器将lambda翻译成一个未命名类的未命名对象，含有一个重载的函数调用运算符
```c++
[](const string& a, const string& b){ return a.size() < b.size(); };
// 类似于
bool operator() (const string& a, const string& b) const
{
    return a.size() < b.size();
}
```
### 14.8.2 标准库定义的函数对象
```c++
#include <functional>

plus<int> intAdd;
negate<int> intNegate; // 取反
int sum = intAdd(10, 20); // sum = 30
sum = intNegate(intAdd(10, 20));

// plus，minus, multiplies, divides, modulus, negate
// equal_to, not_equal_to, greater, greater_equal, less, less_equal
// logical_and, logical_or, logical_not
```
降序排序
```c++
sort(svec.begin(), svec.end(), greater<string>());
```
函数对象对于指针同样适用
```c++
vector<string *> nameTable;
//错误：直接比较两个无关指针产生未定义行为
sort(nameTable.begin(), nameTable.end(), [](string *a, string *b){ return a < b; });
//正确：标准库规定指针的less定义良好
sort(nameTable.begin(), nameTable.end(),  less<string *>());
```
### 14.8.3 可调用对象与function
C++可调用对象：函数，函数指针，lambda表达式，bind创建的对象，重载了函数调用运算符的类

两个不同类型的可调用对象可能共享同一种*调用形式*
```c++
// 普通函数
int add(int i, int j) { return i + j; }
// lambda,未命名的函数对象类
auto mod = [](int i, int j){ return i % j; };
// 函数对象类
struct divide {
    int operator()(int denominator, int divisor) {
        return denominator / divisor;
    }
};

// 同一种调用形式
int(int, int)
```
函数表
```c++
// 构建从运算符到函数指针的映射
map<string, int(*)(int, int)> binops;
// 可以添加add
binops.insert({"+", add}); // {...}是一个pair
//但是不能insert mod和divide，类型和函数指针不匹配

// 使用function
#include <functional>
function<int(int, int)> f1 = add;
function<int(int, int)> f2 = divide();
function<int(int, int)> f3 = [](int i, int j){ return i * j; };

// 重新定义map
map<string, function<int(int, int)>> binops = {
    {"+", add},
    {"-", std::minus<int>()},
    {"/", divide()},
    {"*", [](int i, int j){return i * j;}},
    {"%", mod}
};
// 调用
binops["+"](10, 5);
```
function<T>的成员的类型
```c++
result_type
argument_type
first_argument_type
second_argument_type
```
#### 重载的函数
```c++
int add(int i, int j) { return i + j; }
Sales_data add(const Sales_data&, const Sales_data&);
map<string, function<int(int,int)>> binops;

binops.insert({"+", add});    //xxxxx, 不知道哪个add

// 1. 存储函数指针
int (*fp)(int, int) = add;
binops.insert({"+", fp});

// 2. lambda
binops.insert( {"+", [](int a, int b)}{ return add(a, b); } );
```
## 14.9 重载，类型转换与运算符
### 14.9.1 类型转换运算符
类的一种特殊成员函数，将一个类类型的值转换为其他类型
```c++
class SmallInt {
public:
    SmallInt(int i = 0): val(i)
    {
        if (i < 0 || i > 255)
            throw std::out_of_range("Bad SmallInt value");
    }
    operator int() const { return val; }
private:
    std::size_t val;
};

SmallInt si;
si = 4; // 将4隐式转换为SmallInt，然后调用operator=
si + 3; // 将si隐式转换为int，然后执行加法

// 虽然编译器一次只能执行一个用户定义的类型转换，但是隐式的用户
// 定义类型转换何以至于一个内置类型转换之前或之后
SmallInt si = 3.14;
si + 3.14;
```

#### 显式的类型转换运算符
```c++
class SmallInt {
public:
    explicit operator int() const { return val; }
    // ...
};

SmallInt si = 3; // ok, 构造函数不是显式的
si + 3; // xxxxx, 
static_cast<int>(si) + 3; //ok
```
显式的类型转换将被隐式的执行：
* if, while, do的条件部分
* for的条件表达式
* !, ||, &&的运算对象
* ？：条件表达式

#### 转换为bool
```c++
while (std::cin >> value)
```
输入运算符将数据读入value并返回cin，cin被istream operator bool 隐式转换，如果cin状态是good，则返回真

向bool的转换通常用在条件，因此定义成explicit