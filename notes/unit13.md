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
### 13.1.2 拷贝赋值运算符
#### 重载赋值运算符
如果一个运算符是一个成员函数，其左侧运算对象就绑定到隐式的this参数，对于=，其右侧运算符作为显式参数传递
```c++
class Foo
{
public:
    Foo& operator=(const Foo&); //返回其左侧运算对象的引用
}
```
#### 合成拷贝赋值运算符
```c++
Sales_data&
Sales_data::operator=(const Sales_data &rhs)
{
    bookNo = rhs.bookNo;
    units_sold = rhs.units_sold;
    revenue = rhs.revenue;
    return *this;
}
```
### 13.1.3 析构函数
释放对象使用的资源并销毁对象的非static数据成员
```c++
class Foo
{
public:
    ~Foo(); //没有返回值不接受参数
};
```
首先执行函数体然后销毁成员，成员按初始化顺序的逆序销毁，通常，析构函数释放对象在生存期分配的所有资源

#### 何时调用析构函数
* 变量离开作用域
* 对象被销毁时其成员被销毁
* 容器被销毁时元素被销毁
* delete
* 临时对象当创建它的完整表达式结束时被销毁

#### 合成析构函数
```c++
struct X
{
    X(const string &name) : n(name) { cout << "X()+" + n << endl; }
    X(const X &s)
    {
        n = s.n + "*";
        cout << "X(const X&)+" + n << endl;
    }
    X &operator=(const X &rhs)
    {
        cout << "X& operator=(const X&)+" + n << endl;
        return *this;
    }
    ~X() { cout << "~X()+" + n << endl; }
    string n;
};
void fref(X &x)
{
    cout << "void fref(X& x)" << endl;
}
void fnref(X x)
{
    cout << "void fnref(X x)" << endl;
}

int main()
{
    X x("1");
    fref(x);
    fnref(x);
    auto p = new X("2");
    vector<X> vec = {x, *p};
    X x2("3");
    vec.reserve(100);
    vec.push_back(x2);
    return 0;
    /* 结果：
    X()+1 //x构造函数
    void fref(X& x) //fref 没有拷贝构造
    X(const X&)+1* //fnref 的形参拷贝构造一个1的拷贝1*
    void fnref(X x) //fnref
    ~X()+1* //fnref结束销毁之前的局部变量1*
    X()+2 //2的构造函数 new
    X(const X&)+1* //vec添加元素x，拷贝构造1*
    X(const X&)+2* //同上
    X(const X&)+1** //可能是vec内存分配不够大换地方
    X(const X&)+2**
    ~X()+2* //销毁之前的vec中的2*和1*因为已经拷贝到新的大地方
    ~X()+1*
    X()+3 //3构造
    X(const X&)+1*** //vec.reserve(100)开辟了一块大内存，先把1**和2**拷贝构造过来
    X(const X&)+2***
    ~X()+1** //销毁不用的1**，2**
    ~X()+2**
    X(const X&)+3* //添加3，因为够大不需要将2***，1***再次移动
    //ruturn结束之后自动销毁对象
    ~X()+3 //3
    ~X()+1*** //vec
    ~X()+2***
    ~X()+3*
    ~X()+1 //1 ，new的2无人销毁因为没有delete
    */
}
```
### 13.1.4 三/五法则
#### 需要析构函数的类也需要拷贝和赋值操作
合成析构函数不会delete一个指针数据成员

```c++
class HasPtr
{
public:
    HasPtr(const string &s = string()):
        ps(new string(s)), i(0) { }
    ~HasPtr() { delete ps; }
    // ...
}
```
如果使用合成拷贝构造和赋值函数，多个对象的ps可能指向同一个内存，可能delete多次
#### 需要拷贝操作的类也需要赋值操作，反之亦然

### 13.1.5 使用=default
```c++
class Sales_data
{
public:
    Sales_data() = default;
    Sales_data(const Sales_data&) = default;
    Sales_data& opreator=(const Sales_data &);
    ~Sales_data() = default;
};
Sales_data& Sales_data::opreator=(const Sales_data&) = default;
```
### 13.1.6 阻止拷贝
#### 定义删除的函数
```c++
struct NoCopy
{
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete; //阻止拷贝
    NoCopy &operator=(const NoCopy&) = delete; //阻止赋值
    ~NoCopy() = default; 
}
```
析构函数不能是删除的成员

合成的拷贝控制成员可能是删除的

对于有引用类型的类合成拷贝赋值运算符被定义为删除的

## 13.2 拷贝控制和资源管理
### 13.2.1 行为像值的类
对于类管理的资源，每个对象都应该拥有一份自己的拷贝
```c++
class HasPtr
{
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr&): ps(new string(*o.ps)), i(o.i) { }
    HasPtr& operator=(const HasPtr&);
    ~HasPtr() { delete ps; }
private:
    std::string *ps;
    int i;
};
```
#### 赋值运算符
赋予自身ok，先销毁左侧

先将右侧运算对象拷贝到一个局部临时对象中，拷贝完成，销毁左侧运算对象，从临时拷贝到左侧

```c++
HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
    auto newp = new string(*rhs.ps);
    delete ps;
    ps = newp;
    i = rhs.i;
    return *this;
}
```
### 13.2.2 定义行为像指针的类
#### 引用计数
```c++
class HasPtr
{
public:
    // 构造函数分配新的string和新的计数器，置为1
    HasPtr(const string &s = string()):
        ps(new string(s)), i(0), use(new size_t(1)) {}
    // 拷贝构造函数拷贝三个成员递增计数器
    HasPtr(const HasPtr &p):
        ps(p.ps), i(p.i), use(p.use) { ++*use; }
    HasPtr& operator=(const HasPtr&);
    ~HasPtr();
private:
    string *ps;
    int i;
    size_t *use;
};
HasPtr::~HasPtr()
{
    if (--*use == 0)
    {
        delete ps;
        delete use;
    }
}
HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    ++*rhs.use;
    if (--*use == 0)
    {
        delete ps;
        delete use;
    }
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;
}
```
## 13.3 交换操作
```c++
class HasPtr
{
    friend void swap(HasPtr &, HasPtr &);
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
    HasPtr(const HasPtr &);
    ~HasPtr();
    HasPtr &operator=(const HasPtr &);
    bool operator<(const HasPtr &) const;
    void info() { cout << *ps << endl; }
private:
    std::string *ps;
    int i;
};
inline
void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps); //如果存在类型特定的swap版本，其匹配程度会优于std中定义的版本
    swap(lhs.i, rhs.i);
}
```
vector的元素太少sort不会调用swap

#### 在赋值运算符中使用swap
拷贝并交换，将左侧运算对象与右侧运算对象 的一个副本进行交换
```c++
HasPtr& HasPtr::operator=(HasPtr rhs) //按值传递，拷贝构造函数将右侧运算对象中的string拷贝到rhs
{
    swap(*this, rhs); //交换左侧对象与rhs，rhs指向对象曾经使用的内存
    return *this; // rhs被销毁，delete了rhs中的指针
}
```
## 13.4 拷贝控制示例
每个Folder都保存一个包含的Message的set，每个Message都会保存一个Folder的指针set
Message: save, remove


明年加油！
考试加油！