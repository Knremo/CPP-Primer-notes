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
