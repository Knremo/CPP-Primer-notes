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
Message: save, remove, addFld, remFld
Folder: addMsg, remMsg

明年加油！
考试加油！

## 13.5 动态内存管理类
vector的简化版本，不使用模板只用于string

StrVec类

allocator分配未构造内存
三个指针成员：
element 首元素
first_free 最后一个元素之后的位置
cap 分配内存的最后位置

static allocator<string> alloc

alloc_n_copy 分配内存并拷贝
free 销毁构造的元素并释放内存
chk_n_alloc 保证至少有容纳一个新元素的空间，如果没有调用reallocate分配更多内存
reallocate 在内存用完时分配新内存

reallocate()
移动构造函数
move() 直接把string管理的内存指向新的，而不是拷贝

## 13.6 对象移动
### 13.6.1 右值引用
左值lvalue, 有标识符、可以取地址的表达式:
* 变量、函数或数据成员的名字
* 返回左值引用的表达式，++x, x = 1, cout << ' ', a[3], *p
* 字符串字面量，"hello world"
* 返回左值引用的函数

在函数调用时，左值可以绑定到左值引用的参数，如`T&`。一个常量只能绑定到常左值引用，如`const T&`。

纯右值prvalue, 没有标识符、不可以取地址的表达式，“临时对象”：
* 返回非引用类型的表达式，如x++, x + 1, make_shared<int>(42)
* 除字符串字面量之外的字面量，如42, true
* 返回非引用类型的函数

右值可以绑定到常左值引用`const T&`, 但不可以绑定到非常左值引用`T&`，以及右值引用

不能将一个右值引用绑定到一个右值引用类型的变量上
```c++
int &&rr1 = 42;   //ok
int &&rr2 = rr1;  //xxxxx
```
#### 标准库move函数
显式将一个左值转换未对应的右值引用类型
```c++
#include <utility>
int &&rr3 = std::move(rr1); //ok
```
这意味着：除了对rr1赋值或销毁它外，我们将不再使用它

### 13.6.2 移动构造函数和移动赋值运算符
```c++
StrVec::StrVec(StrVec &&s) noexcept
    : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;
}
```
移动构造函数必须确保移后源对象销毁时无害的，一旦资源完成移动，源对象必须不再指向被移动的资源

noexcept通知标准库构造函数不抛出任何异常

移动构造函数不分配任何新内存，接管源对象的内存，然后把源对象的指针置为nullptr，最终销毁源对象

#### noexcept
不分配任何资源所以不会抛出任何异常，通知标准库而减少一些额外工作

#### 移动赋值运算符
```c++
StrVec &StrVec::operator=(StrVec &&rhs) noexcept
{
    if (this != &rhs)
    {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}
```
#### 移后源对象必须可析构

#### 合成的移动操作
只有当一个类没有定义任何自己版本的拷贝控制函数，且它的所有数据成员都能移动构造或移动赋值时，编译器才会为它合成移动构造函数或移动赋值运算符

定义了一个移动构造函数或移动赋值运算符的类必须也定义自己的拷贝操作，否则这些成员默认被定义为删除的

如果没有移动构造函数，右值也被拷贝

#### Message类的移动操作
```c++
void Message::move_Folders(Message *m)
{
    folders = std::move(m->folders);
    for (auto f : folders) {
        f->remMsg(m);
        f->addMsg(this);
    }
    m->folders.clear(); //确保销毁m是无害的
}
// 移动构造函数
Message::Message(Message &&m): contents(std::move(m.contents))
{
    move_Folders(&m);
}
// 移动赋值运算符
Message& Message::operator=(Message &&rhs)
{
    if (this != &rhs)
    {
        remove_from_Folders();
        contents = std::move(rhs.contents);
        move_Folders(&rhs);
    }
    return *this;
}
```

#### 移动迭代器
移动迭代器解引用运算符生成一个右值引用

将移动迭代器传给`uninitialized_copy`
```c++
void StrVec::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    auto first = alloc.allocate(newcapacity);
    auto last = uninitialized_copy(make_move_iterator(begin()),
                                   make_move_iterator(end()),
                                   first);
    free();
    elements = first;
    first_free = last;
    cap = elements + newcapacity;
}
```
`uninitialized_copy`对每个元素调用`construct`来拷贝构造到目的位置，解引用一个移动迭代器得到一个右值引用，这意味着使用移动构造函数来构造元素。

### 13.6.3 右值引用和成员函数
成员函数也可以有两个版本
```c++
class StrVec
{
public:
    void push_back(const std::string&);
    void push_back(std::string&&);
};
void StrVec::push_back(const string& s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}
void StrVec::push_back(string&& s)
{
    chk_n_alloc();
    alloc.construct(first_free++, std::move(s));
}

StrVec vec;
string s = "some string or another";
vec.push_back(s); //push_back(const string&)
vec.push_back("done"); //push_back(string&&)
```
#### 右值和左值引用成员函数
可以在右值对象调用成员函数
`(s1 + s2).find('a');`

向一个右值赋值
`s1 + s2 = "wow!"`

阻止这种做法：
强制左侧运算对象是一个左值，*引用限定符*
```c++
class Foo {
public:
    Foo& operator=(const Foo&) &; //只能向可修改的左值赋值
};
Foo& Foo::operator=(const Foo &rhs) &
{
    ...
    return *this;
}
```
引用限定符可以是& &&，对应左值右值，只能用于非static成员函数，定义声明都要有
```c++
Foo& retFoo(); //返回一个引用，retFoo调用是一个左值
Foo retVal(); //返回一个值，retVal调用是一个右值
Foo i, j;      //i j是左值
i = j;         //ok
retFoo() = j;  //ok
retVal() = j;  //xxxxx
i = retVal();  // ok
```
有const的成员函数
```c++
class Foo {
public:
Foo someMem() & const;     // xxxxxxxxx
Foo anotherMem() const &;  //ok
};
```
#### 重载和引用函数
综合引用限定符和const来区分一个成员函数的重载版本
```c++
class Foo
{
public:
    Foo sorted() &&; // 用于可改变的右值
    Foo sorted() const &; // 可用于任何类型的Foo
private:
    vector<int> data;
};
//右值意味着没有别的用户，可以直接改变
Foo Foo::sorted() &&
{
    sort(data.begin(), data.end());
    return *this;
}
//const或是左值不能载原址上改变，先拷贝一份
Foo Foo::sorted() const & {
    Foo ret(*this); //拷贝一份
    sort(ret.data.begin(), ret.data.end()); //排序副本
    return ret; //返回副本
}
//编译器根据对象的左右值调用对应的sorted
retVal().sorted(); //右值
retFoo().sorted(); //左值
```

const成员函数可以用两个一样的版本除了const，而引用限定函数如果具有相同名字和参数列表，就必须都加上引用限定符，或者都不加
```c++
class Foo {
public:
    Foo sorted() &&;
    Foo sorted() const; // xxxxxxx
    using Comp = bool(const int&, const int&); //函数类型的别名。Comp*是一个函数指针
    Foo sorted(Comp*);  // ok.不同的参数列表
    Foo sorted(Comp*) const; //ok。都没有引用限定符
};
```