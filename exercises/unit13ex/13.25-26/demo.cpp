#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

class StrBlobPtr;

class StrBlob
{
public:
    friend class StrBlobPtr; //友元，可以访问data
    typedef vector<string>::size_type size_type;
    StrBlob();
    StrBlob(initializer_list<string> il); // 列表初始化
    StrBlob(const StrBlob&);
    StrBlob& operator=(const StrBlob&);

    // 模拟vector的一些方法
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const string &t) { data->push_back(t); }
    void pop_back();
    string &front();
    string &back();

    // 模拟begin, end
    StrBlobPtr begin();
    StrBlobPtr end();

    size_t print();
private:
    std::shared_ptr<std::vector<string>> data;
    void check(size_type i, const string &msg) const;
};

class StrBlobPtr
{
public:
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    // 解引用，返回curr下标的值
    string &deref() const;
    // 递增下标，返回自身
    StrBlobPtr &incr();

private:
    // 检查一个下标和当前的wptr是否合法，是返回vector的sp
    shared_ptr<vector<string>> check(size_t, const string &) const;
    // 两个成员，wptr指向StrBlob的vector,curr指示一个下标值默认0
    weak_ptr<vector<string>> wptr;
    size_t curr;
};
//构造函数
StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) { cout << "meme" << endl; }
StrBlob::StrBlob(const StrBlob& o)
{
    cout << "this is StrBlob(const StrBlob&)" << endl;
    data = make_shared<vector<string>>(*o.data);
    //data = shared_ptr<vector<string>>(o.data); //计数会加一
}
StrBlob& StrBlob::operator=(const StrBlob& rhs)
{
    cout << "this is StrBlob& StrBlob(const StrBlob&)" << endl;
    auto newp = new vector<string>(*rhs.data);
    data.reset(newp);
    return *this;
}

//元素访问检查
void StrBlob::check(size_type i, const string &msg) const
{
    if (i >= data->size())
        throw out_of_range(msg);
}
string &StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}
string &StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}
void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    return data->pop_back();
}
size_t StrBlob::print()
{ 
    for (auto e : *data)
        cout << e << " ";
    return data.use_count();
}
inline StrBlobPtr StrBlob::begin()
{
    return StrBlobPtr(*this);
}
inline StrBlobPtr StrBlob::end()
{
    auto ret = StrBlobPtr(*this, data->size());
    return ret;
}

shared_ptr<vector<string>>
StrBlobPtr::check(size_t i, const string &msg) const
{
    auto ret = wptr.lock(); //返回一个空指针或者指向data的sp
    if (!ret)
        throw runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw out_of_range(msg); //检查索引值
    return ret;
}
// 解引用
string &StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr &StrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

int main()
{
    StrBlob c1({"a", "b"}), c3 = {"c"}; // 前为直接初始化，后为拷贝初始化，编译器可能绕过了拷贝初始化的拷贝构造函数
    auto c2 = c1; // 拷贝构造
    c3 = c2; // 拷贝赋值
    c3 = c3; // 拷贝赋值
    c1.pop_back();
    c2.push_back("d");

    cout << c1.print() << endl;
    cout << c2.print() << endl;
    cout << c3.print() << endl;
    // 1，1，1
    /*
    meme
    meme
    this is StrBlob(const StrBlob&)
    this is StrBlob& StrBlob(const StrBlob&)    
    this is StrBlob& StrBlob(const StrBlob&)    
    a 1
    a b d 1
    a b 1
    */
    
    return 0;
}