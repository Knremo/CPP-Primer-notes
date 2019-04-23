# 7.1 定义抽象数据类型
## 7.1.2 定义Sales_data类
```c++
struct Sales_data {
    //成员函数，声明在内部，定义可以在外
    std::string isbn() const { return bookNo; }

    //this额外隐形参数，this指针默认是指向非常量对象的常量指针
    //cosnt，isbn()不会改变对象，所以把this声明成指向常量对象的常量指针，则不能写入
    //使用const的成员函数被称为常量成员函数

    Sales_data& combine(const Sales_data&);

    double avg_price() const;
    
    
    std::string bookNo;
    //bookNo在isbn()之后也可以，先处理所有声明在处理函数体

    unsigned units_sold = 0;
    double revenue = 0.0;
};

//外部定义成员函数
double Sales_data::avg_price() const {
    if(units_sold)
        return revenue/units_sold;
    else
        return 0;
}

//返回this对象的函数
//返回一个引用类型可以作为左值
Sales_data& Sales_data::combine(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

//非成员函数
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);
```
## 7.1.3 定义类相关的非成员函数
```c++
//IO类不能拷贝，只能通过引用传递
istream &read(istream &is, Sales_data &item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

ostream &print(ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}
```

## 7.1.4 构造函数
构造函数的名字和类名相同，没有返回类型，可以重载

不能声明成const

### 合成的默认构造函数
当类没有声明任何构造函数时，编译器才会生成默认构造函数

默认初始化

### 某些类不能依赖合成的默认构造函数
定义在块中的内置类型或复合类型的对象被默认初始化将是未定义

### 定义Sales_data的构造函数
```c++
struct Sales_data {
    Sales_data() = default; //默认行为
    Sales_data(const std::string &s): bookNo(s) {}
    Sales_data(const std::string &s, unsigned n, double p):
               bookNo(s), units_sold(n), revenue(p*n) {}
    //:后面是初始值列表

    Sales_data(std::istream &); //只有声明
    
    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data&);
    double avg_price() const;
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
//外部定义
Sales_data::Sales_data(std::istream &is)
{
    read(is, *this); //read前面有定义
}
```

## 7.1.5 拷贝赋值和析构

# 7.2 访问控制与封装
```c++
class Sales_data {
public:
    Sales_data() = default;
    Sales_data(const std::string &s): bookNo(s) {}
    Sales_data(const std::string &s, unsigned n, double p):
               bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data(std::istream &);
    
    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data&);
private:
    double avg_price() const;
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
```
`class`和`struct`的默认访问权限不同
## 7.2.1 友元
```c++
class Sales_data {
friend Sales_data add(const Sales_data&, const Sales_data&);
friend std::istream &read(std::istream&, Sales_data&);
friend std::ostream &print(std::ostream&, const Sales_data&);

public:
    ...
private:
    ...
};
```
# 7.3 类的其他特性
## 7.3.1 类成员再探
### 定义一个类型成员
```c++
class Screen {
public:
    typedef std::string::size_type pos;
    //using pos = std::string::size_type;

    Screen() = default;
    Screen(pos ht, pos wd, char c): height(ht), width(wd),contents(ht * wd, c) {}

    //重载
    char get() const {return contents[cursor];}
    inline char get(pos ht, pos wd) const;
    Screen &move(pos r, pos c);
private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
};

inline Screen &Screen::move(pos r, pos c) //声明内联
{
    pos row = r * width;
    cursor = row + c;
    return *this;
}
char Screen::get(pos r, pos c) const
{
    pos row = r * width;
    return contents[row + c];
}
```
### 可变数据成员
```c++
class Screen {
public:
    void some_member() const;
private:
    mutable size_t access_ctr;
};

void Screen::some_member() const
{
    ++access_ctr;
}
### 类数据成员的初始值
```c++
class Window_mgr {
private:
    std::vector<Screen> screens{Screen(24,80,'')};
};
```
## 7.3.2 返回*this的成员函数
```c++
class Screen {
public:
    Screen &set(char);
    Screen &set(pos, pos, char);
    //同上
};
inline Screen &Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}
inline Screen &Screen::set(pos r, pos col, char ch)
{
    contents[r*width + col] = ch;
    return *this;
}
```
返回引用类型，左值，原副本
### 从const成员函数返回*this
```c++
class Screen {
public:
    Screen &display(std::ostream &os)
    {
        do_display(os); return *this;
    }
    //返回非常量对象
    const Screen &display(std::ostream &os) const
    {
        do_display(os); return *this;
    }
    //返回常量对象
private:
    void do_display(std::ostream &os) const {os << contents;}
};
```
调用的对象是否是const决定了调用哪一个
```c++
Screen myScreen(5, 3);
const Screen blank(5, 3);
```
## 7.3.3 类类型

## 7.3.4 友元再探
###  类之间的友元关系
```c++
class Screen {
    friend class Window_mgr; 
    //Window_mgr的成员可以访问Screen的私有部分
    ...
};

class Window_mgr {
public:
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear(ScreenIndex);
private:
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};

void Window_mgr::clear(ScreenIndex i)
{
    Screen &s = Screen[i];
    s.contents = string(s.height * s.width, ' ');
}
```
没有传递性
### 令成员函数作为友元
```c++
class Screen {
    friend void Window_mgr::clear(ScreenIndex);
};
### 函数重载和友元
分别声明
### 友元声明和作用域

# 7.4 类的作用域
