# 7.1 定义抽象数据类型
## 7.1.2 定义Sales_data类
```c++
struct Sales_data {
    //成员函数，声明在内部，定义可以在外
    std::string isbn() const { return bookNo; }
    //this额外隐形参数
    Sales_data& combine(const Sales_data&);
    double avg_price() const;
    
    
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);
```
