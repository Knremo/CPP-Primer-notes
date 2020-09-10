# 7.1 定义抽象数据类型
## 7.1.2 定义Sales_data类
```c++
struct Sales_data {
    //成员函数，声明在内部，定义可以在外
    std::string isbn() const { return bookNo; }

    //this额外隐形参数，this指针默认是指向非常量对象的常量指针
    //const改变this指针的类型，isbn()不会改变对象，所以把this声明成指向常量对象的常量指针，则不能写入
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
public://整个程序内可以被访问
    Sales_data() = default;
    Sales_data(const std::string &s): bookNo(s) {}
    Sales_data(const std::string &s, unsigned n, double p):
               bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data(std::istream &);
    
    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data&);
private://可以被类的成员函数访问
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
    Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht * wd, c) {}

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
```

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
### 类的声明
前向声明
```c++
class Screen;
```

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
    Screen &s = screens[i];
    s.contents = string(s.height * s.width, ' ');
}
```
没有传递性
### 令成员函数作为友元
```c++
class Screen {
    friend void Window_mgr::clear(ScreenIndex);
};
```
必须先定义Window_mgr,声明clear,定义Screen,clear的友元声明,定义clear.
### 函数重载和友元
分别声明
### 友元声明和作用域
```c++
class X
{
    friend void f() { /* 友元函数可以定义在类的内部 */}
    X() {f();}
    void g();
    void h();
};
void X::g() {return f();} //xxxxxx
void f();
void X::h() {return f();} //OK
```

# 7.4 类的作用域
返回类型
```c++
class Window_mgr
{
public:
    ScreenIndex addScreen(const Screen&);
    //···
};

Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}
```
## 7.4.1 名字查找与类的作用域
编译器处理完类中的全部声明后才会处理成员函数的定义.

# 7.5 构造函数再探
## 7.5.1 构造函数初始值列表
const成员和引用成员必须初始化

构造函数初始值的顺序与成员声明的顺序一致

默认实参和构造函数
```c++
class Sales_data {
public:
    Sales_data(std::string s=""): bookNo(s) {}
    //与default相同
    ...
};
```

## 7.5.2 委托构造函数
使用其他构造函数
```c++
class Sales_data {
public:
    Sales_data(std::string s, unsigned snt, double price): bookNo(s), units_sold(cnt), revenue(cnt*price) {}
    //委托给第一个用括号里的三个参数，默认初始化
    Sales_data(): Sales_data("", 0, 0) {}
    //委托给第一个用括号里的三个参数
    Sales_data(std::string s): Sales_data(s, 0, 0) {}
    //委托给第二个，在间接委托给第一个
    Sales_data(std::istream &is): Sales_data() { read(is, *this); }
};
```
先执行被委托函数的初始值列表和函数体，在执行委托函数的函数体

## 7.5.3 默认构造函数的作用
声明默认构造函数初始化的对象
```c++
Sales_data obj;
```

## 7.5.4 隐式的类类型转换
```c++
string null_book = "9-999-99999-9";
//构造一个临时的Sales_data对象
//该对象的units_sold和revenue等于0，bookNo等于null_book
item.combine(null_book);
```
只允许一步转换

```c++
item.combine(cin);
```
### 抑制构造函数定义的隐式转换
```c++
class Sales_data {
public:
    Sales_data() = default;
    Sales_data(const std::string &s, unsigned n, double p):
               bookNo(s), units_sold(n), revenue(p*n) {}
    explicit Sales_data(const std::string &s): bookNo(s) {}
    explicit Sales_data(std::iosteam&);
}
```
只对一个实参的构造函数有效

显式转换
```c++
item.combine(static_cast<Sales_data>(cin));
```

## 7.5.5 聚合类
只有public成员，没有任何构造函数，没有类内初始值，没有基类、virtual函数

```c++
struct Data
{
    int ival;
    string s;
};

Data val1 = {0, "Anna"};
```

## 7.5.6 字面值常量类
数据成员都是字面值类型

至少含有一个constexpr构造函数...

```c++
class Debug
{
public:
    constexpr Debug(bool b = true): hw(b), io(b), other(b) {}
    constexpr Debug(bool h, bool i, bool o):
                    hw(h), io(i), other(o) {}
    constexpr bool any() { return hw || io || other}
    void set_io(bool b) { io = b; }
    void set_hw(bool b) { hw = b; }
    void set_other(bool b) { other = b; }
private:
    bool hw;
    bool io;
    bool other;
};
```

# 7.6 类的静态成员
声明静态成员
```c++
class Account {
public:
    void calculate() { amount += amount * interestRate; }
    static double rate() { return interestRate; }
    static void rate(double);
private:
    std::string owner;
    double amount;
    static double interestRate;
    static double initRate();
};
```
不能声明成const，不能使用this指针

### 使用类的静态成员
```c++
double r;
r = Account::rate();

Account ac1;
Account *ac2 = &ac1;

r = ac1.rate();
r = ac2->rate();
```
### 定义静态成员
```c++
//外部定义
void Account::rate(double newRate)
{
    interestRate = newRate;
}
//
double Account::interestRate = initRate();
```
### 静态成员的类内初始化
通常情况下类的静态成员不应该再类的内部初始化，但可以为constexpr静态成员提供const整数类型的类内初始值
```c++
static constexpr int period = 30;
```
