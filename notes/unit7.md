# 7.1 定义抽象数据类型
## 7.1.2 定义Sales_data类
```c++
struct Sales_data {
    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data&);
    double avg_price() const;

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
}
