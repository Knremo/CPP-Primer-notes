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
