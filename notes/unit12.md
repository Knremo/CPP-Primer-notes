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
