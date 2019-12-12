#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class StrBlobPtr;
class ConstStrBlobPtr;

class StrBlob
{
public:
    friend class StrBlobPtr; //友元，可以访问data
    friend class ConstStrBlobPtr;
    typedef vector<string>::size_type size_type;
    StrBlob();
    StrBlob(initializer_list<string> il); // 列表初始化
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
    string &deref2() const;
    // 递增下标，返回自身
    StrBlobPtr &incr();

private:
    // 检查一个下标和当前的wptr是否合法，是返回vector的sp
    shared_ptr<vector<string>> check(size_t, const string &) const;
    // 两个成员，wptr指向StrBlob的vector,curr指示一个下标值默认0
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

class ConstStrBlobPtr
{
public:
    ConstStrBlobPtr() : curr(0) {}
    ConstStrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    // 解引用，返回curr下标的值
    string &deref() const;
    // 递增下标，返回自身
    ConstStrBlobPtr &incr();

private:
    // 检查一个下标和当前的wptr是否合法，是返回vector的sp
    shared_ptr<vector<string>> check(size_t, const string &) const;
    // 两个成员，wptr指向StrBlob的vector,curr指示一个下标值默认0
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

//构造函数
StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}
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
string &StrBlobPtr::deref2() const
{
    return (*check(curr, "dereference past end"))[curr];
}
StrBlobPtr &StrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

// 12.20
void f2()
{
    ifstream text("text.txt");
    string line;
    StrBlob s;
    const StrBlob s2 = {"happy", "love"};
    while (getline(text, line))
    {
        s.push_back(line);
    }
    StrBlobPtr sp(s);
    ConstStrBlobPtr csp(s2);
    ConstStrBlobPtr csp2(s);

    for(size_t i=0; i < s.size(); ++i)
    {
        cout << sp.deref2() << endl;
        sp.incr();
    }
    
    text.close();
}

//12.21
//deref2()似乎没啥问题


int main()
{
    f2();

    return 0;
}