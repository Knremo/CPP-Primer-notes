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
