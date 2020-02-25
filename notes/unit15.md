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
