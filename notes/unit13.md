# 13 拷贝控制
五种特殊的成员函数
* 拷贝构造函数
* 拷贝赋值函数
* 移动构造函数
* 移动赋值函数
* 析构函数
## 13.1 拷贝赋值与销毁
### 13.1.1 拷贝构造函数
第一个参数是自身类类型的引用，额外参数都有默认值
```c++
class Foo
{
public:
    Foo();
    Foo(const Foo&);
    //...
}
```
#### 合成拷贝构造函数
```c++
class Sales_data
{
public:
    // ...
    Sales_data(const Sales_data&);
private:
    std::string bookNo;
    int units_sold = 0;
    double revenue = 0.0;
;}
// 与Sales_data的合成的拷贝构造函数等价
Sales_data::Sales_data(const Sales_data &orig):
    bookNo(orig.bookNo),
    units_sold(orig.units_sold),
    revenue(orig.revenue)
    { }
```
#### 拷贝初始化
```c++
string dots(10, '.'); // 直接初始化
string nines = string(100, '9'); // 拷贝初始化
```
```c++
class Point
{
public:
    Point() { }
    Point(const Point&);
private:
    int num = 0;
};
Point::Point(const Point &orig):
    num(orig.num)
{
    cout << "I'm here." << endl;
}

Point global;
Point foo_bar(Point arg) //类作为实参传递给非引用类型的形参，调用1
{
    Point local = arg, *heap = new Point(global);
    // 拷贝初始化调用2
    // 用一个对象去初始化另一个对象调用3
    *heap = local; //赋值没有调用 
    Point pa[4] = { local, *heap }; // 用花括号列表初始化一个数组中的元素有两个调用4，5
    return *heap; //从一个返回类型为非引用类型的函数返回一个对象，调用6
}
int main()
{
    Point p;
    Foo_bar(p);
    // 6次
}
```
哈哈