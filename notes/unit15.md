# 面向对象程序设计
## 15.1 OOP
数据抽象，继承，动态绑定
#### 继承
虚函数，派生类自定义适合自身的版本
```c++
class Quote {
public:
    std::string isbn() const;
    virtual double net_price(std::size_t n) const;
};
```
类派生列表
```c++
class Bulk_quote : public Quote {
public:
    double net_price(std::size_t) const override;
};
```
#### 动态绑定
使用基类的引用或指针调用一个虚函数时将发生动态绑定

## 15.2 定义基类和派生类
### 15.2.1 定义基类
```c++
class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price): 
                                        bookNo(book), price(sales_price) {}
    std::string isbn() const { return bookNo; }
    virtual double net_price(std::size_t n) const
    { return n * price; }
    virtual ~Quote() = default;
private:
    std::string bookNo;
protected:
    double price = 0.0;
};
```
基类通常都应该定义一个虚析构函数

任何构造函数之外的非静态函数都可以是虚函数，`virtual`只能出现在类内部的声明语句之前，该函数在派生类中隐式的也是虚函数

派生类需要访问`Quote`的`price`，所以定义成`protected`，而`bookNo`通过`isbn()`调用，所以`private`
### 15.2.2 定义派生类
```c++
class Bulk_quote: public Quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string&, double, std::size_t, double);
    double net_price(std::size_t) const override;
private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};
```
如果一个派生是公有的，则基类的公有成员也是派生类接口的组成部分

如果派生类没有覆盖其基类中的某个虚函数，会直接继承基类中的版本

`override`显式注明覆盖

```c++
Quote item;
Bulk_quote bulk;
Quote *p = &item;
p = &bulk;
Quote &r = bulk;
```
#### 派生类构造函数
```c++
Bulk_quote(const std::string& book, double p, std::size_t qty, double disc):
                        Quote(book, p), min_qty(qty), discount(disc) {  }
```
#### 派生类使用基类的成员
```c++
double Bulk_quote::net_price(size_t cnt) const
{
    if (cnt >= min_qty)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}
```
#### 继承与静态成员
在整个继承体系中只存在唯一定义，遵循通用的访问控制规则
#### 派生类的声明
```c++
class Bulk_quote; // 没有派生列表
```
#### 防止继承的发生
```c++
class NoDerived final {};
```

### 15.2.3 类型转换与继承
基类的指针或引用的静态类型可能与其动态类型不一致

* 从派生类向基类的类型转换只对指针或引用类型有效
* 基类向派生类不存在隐式类型转换
* 派生类向基类的转换可能会由于访问受限而变的不可行

## 15.3 虚函数
#### final和override说明符
override防止没有覆盖已存在的虚函数

final防止覆盖的发生

#### 虚函数和默认实参
如果虚函数使用默认实参，则基类和派生类中定义的默认实参最好一致

#### 回避虚函数的机制
派生类虚函数调用基类的虚函数，使用作用域运算符
```c++
double undiscounted = baseP->Quote::net_price(42);
```
## 15.4 抽象基类
