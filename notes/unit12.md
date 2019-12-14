# 12 动态内存
静态内存：局部static对象，类static数据成员，定义在函数之外的变量
栈内存：定义在函数内的非static对象

堆heap 自由空间

## 12.1 动态内存与智能指针
memory头文件

`shared_ptr`允许多个指针指向同一个对象
`unique_ptr`独占
`weak_ptr`

### 12.1.1 shared_ptr类
```c++
shared_ptr<string> p1;
shared_ptr<list<int>> p2;

p.get() // 返回指针
swap(p, q)
p.swap(q)

// shared_ptr only
make_shared<T>(args) // 返回一个shared_ptr, 一个用args初始化的T
shared_ptr<T>p(q) // p是shared_ptr q的拷贝

p = q

p.unique() // p.use_count()为1，返回true
p.use_count() // 返回p共享对象的智能指针数量
```
#### make_shared
```c++
shared_ptr<string> p = make_shared<string>("ssss");
auto p = make_shared<vector<string>>();
```
引用计数

析构函数

#### 共享数据
```c++
class StrBlob
{
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const std::string &t) {data->push_back(t);}
    void pop_back();
    std::string& front();
    std::string& back();
private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const;
};
//构造函数
StrBlob::StrBlob(): data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il): data(make_shared<vector<string>>(il)) {}
//元素访问检查
void StrBlob::check(size_type i, const string &msg) const
{
    if (i >= data->size())
        throw out_of_range(msg);
}
string& StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}
string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}
void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    return data->pop_back();
}
```
拷贝，赋值，销毁该对象，shared_ptr成员会被拷贝等

对于构造函数分配的vector，当最后一个指向它的对象被销毁时，它会自动销毁
### 12.1.2 直接管理内存
new delete

```c++
int *pi = new int;  //默认初始化
string *ps = new string;

int *pi = new int(1024);
string *ps = new string(10, '9');

vector<int> *pv = new vector<int>{0, 1, 2, 3, 4, 5};

int *pi2 = new int(); //值初始化为0

auto p1 = new auto(obj); //自动推断

//const
const int *pci = new const int(1024);
const string *pcs = new const string;
//const对象必须初始化

//内存耗尽
//抛出bad_alloc异常
//如果分配失败new返回一个空指针
//头文件 new
int *p1 = new int; // std::bad_alloc
int *p2 = new (nothrow) int; //返回空指针

//释放
delete p;
delete pci; // const对象
```
记得释放

### 12.1.3 shared_ptr和new结合使用
接受指针参数的智能指针构造函数是explicit的，必须使用直接初始化
```c++
shared_ptr<int> p1 = new int(1024); // xxxxx
shared_ptr<int> p2(new int(1024)); // ok

shared_ptr<int> clone(int p)
{
    return shared_ptr<int>(new int(p));
}

shared_ptr<T> p(q) //p管理内置指针q所指的对象
shared_ptr<T> p(u) //p从unique_ptr u接管对象所有权将u置为空
shared_ptr<T> p(q, d) //p将使用d来代替delete

p.reset() //若p是唯一释放
p.reset(q) //将p指向q
p.reset(q, d) //调用d释放
```
#### 不要使用get初始化另一个智能指针
```c++
shared_ptr<int> p(new int(42)); //引用计数1
int *q = p.get(); // ok
{
    // 两个独立的shared_ptr指向相同的内存
    shared_ptr<int>(q);
} // 程序块结束q被销毁指向的内存被释放
// p指向的内存已被释放
int foo = *p;
```
#### 其他操作
将新的指针赋予shared_ptr
```c++
p.reset(new int(1024));
```
改变底层对象时如果不是仅有的用户则制作一份新的拷贝
```c++
if (!p.unique())
    p.reset(new string (*p));
*p += newVal;
```
### 12.1.4 智能指针和异常
使用shared_ptr管理没有定义析构函数的类
```c++
struct destination; // 正在连接什么
struct connection;  // 使用连接所需的信息
connection connect(destination*); // 打开连接
void disconnect(connection); // 关闭给定的连接

void f(destination &d)
{
    // 获得一个连接
    connection c = connect(&d);
    // 使用连接
    // 如果在f退出前忘记调用disconnect，就无法关闭c
}

//使用shared_ptr
// 定义deleter
void end_connection(connection *p) {disconnect(*p);}

void f(destination &d)
{
    connection c = connect(&d);
    shared_ptr<connection> p(&c, end_connection);
    //当f退出时，connection会被正确关闭
}
```

TIPS:
* 不使用相同的内置指针值初始化(reset)多个智能指针
* 不delete get()返回的指针
* 不使用get()初始化或reset另一个智能指针
* 如果使用get()返回的指针，当最后一个智能指针销毁后指针就无效了
* 如果使用智能指针管理的资源不是new分配的内存，传递一个删除器

### 12.1.5 unique_ptr
```c++
unique_ptr<double> p1; //
unique_ptr<int> p2(new int(42));

//不支持普通的拷贝赋值操作
//unique_ptr<string> p2(p1);  xxxxxx
//p3 = p2; xxxxxxx

unique_ptr<T, D> u2; //使用一个类型为D的可调用对象来释放它的指针
unique_ptr<T, D> u(d); //空，指向类型为T的对象，用类型为D的对象d代替delete

u = nullptr; //释放u指向的对象，将u置为空

u.release(); //u放弃对指针的控制权，返回指针并将u置为空
u.reset(); //释放u指向的对象
u.reset(q); //令u指向q
u.reset(nullptr); 
```
转移
```c++
// p1 -> p2
unique_ptr<string> p2(p1.release()); //将p1置为空
unique_ptr<string> p3(new string("Trex"));
// p3 -> p2
p2.reset(p3.release()); //reset释放p2原来指向的内存
```
#### 传递参数和返回
"拷贝"即将销毁的对象
```c++
unique_ptr<int> clone(int p)
{
    return unique_ptr<int>(new int(p));
}

unique_ptr<int> clone(int p)
{
    unique_ptr<int> ret(new int (p));
    return ret;
}
```
#### 传递删除器
```c++
unique_ptr<objT, delT> p(new objT, fcn);
//p指向一个类型为objT的对象，并使用一个类型为delT的对象释放objT对象
//他会调用一个名为fcn的delT类型对象

void f(destination &d)
{
    connection c = connect(&d);
    //当p被销毁时，连接将会关闭
    unique_ptr<connection, decltype(end_connection) * > p(&c, end_connection);
    //使用连接
    //当f退出时connection会被正确关闭
}
```
### 12.1.6 weak_ptr
指向一个shared_ptr管理的对象，不会改变shared_ptr的引用计数
```c++
auto p = make_shared<int>(42);
weak_ptr<int> wp(p);

w = p; //p可以是shared_ptr或weak_ptr

w.reset() //w置为空
w.use_count() //
w.expired() //若w.use_count()为0，返回true
w.lock() // 如果expired为true，返回一个空shared_ptr，否则返回指向w的sp

if (shared_ptr<int> np = wp.lock())
{
    ...
}
```
#### 检查指针类
```c++
class StrBlobPtr;

class StrBlob
{
public:
    friend class StrBlobPtr;
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const std::string &t) {data->push_back(t);}
    void pop_back();
    std::string& front();
    std::string& back();

    //begin, end
    StrBlobPtr begin();
    StrBlobPtr end();
private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const;
};

class StrBlobPtr
{
public:
    StrBlobPtr(): curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0): wptr(a.data), curr(sz) {}
    std::string& deref() const;
    StrBlobPtr& incr();
private:
    std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};

//构造函数
StrBlob::StrBlob(): data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il): data(make_shared<vector<string>>(il)) {}
//元素访问检查
void StrBlob::check(size_type i, const string &msg) const
{
    if (i >= data->size())
        throw out_of_range(msg);
}
string& StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}
string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}
void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    return data->pop_back();
}
StrBlobPtr StrBlob::begin() 
{
    return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end()
{
    auto ret = StrBlobPtr(*this, data->size());
    return ret;
}

std::shared_ptr<std::vector<std::string>> 
StrBlobPtr::check(std::size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg); //检查索引值
    return ret;
}
std::string& StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}
StrBlobPtr& StrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}
```
StrBlob实际上是模仿了vector，有size，empty,push_back,pop_back,end,begin等操作，
把string存储在内部，通过begin和end返回的StrBlobPtr就像迭代器，指向某一个下标的元素，
可以通过解引用读取以及递增

* 两个类相互调用写法
最好放在头文件里
```c++
class B;
class A
{
    friend class B;
    int f1(); //A中有用到B的成员函数的应该先声明把定义放在B后面
};
class B
{
    int f2();
};

A::f1() {}
B::f2() {}
```
* `const StrBlob` 可以用的方法就是中间有const的方法
* 类成员返回本身是 `*this`

## 12.2 动态数组
### 12.2.1 new和数组
new分配一个对象数组
```c++
int *pia = new int[get_size()]; //指向第一个int
```
不能用begin，end，范围for

#### 初始化
```c++
int *pia = new int[10]; //10个未初始化的int
int *pia2 = new int[10](); //10个初始化为0的int
string *psa = new string[10]; //10个空string
string *psa2 = new string[10](); //10个空string

string *psa3 = new string[10]{"a", "an", "the", string[3, 'x']};
//初始化失败
//new头文件
//bad_array_new_length
```
#### 动态分配空数组
```c++
char arr[0]; //xxxx
char *cp = new char[0]; // ok

size_t n = get_size(); // n == 0
int *p = new int[n];
for (int* q = p; q != p + n; ++q)
    ...;
```
#### 释放动态数组
```c++
delete [] pa;
```
#### 智能指针管理动态数组
```c++
unique_ptr<int []> up(new int[10]);
up.release(); //自动用delete[]销毁

//不能使用点和箭头成员运算符
//可以下标运算
for (size_t i = 0; i != 10; ++i)
    up[i] = i;

unique_ptr<int []> u(p); //指向内置指针p指向的动态数组

// shared_ptr需要一个deleter
shared_ptr<int> sp(new int[10], [](int *p){delete [] p;});
```
### 12.2.2 allocator类
