#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

class QueryResult;
class StrBlob;
string ModifyWord(const string &);

class TextQuery
{
public:
    using line_no = vector<string>::size_type;
    TextQuery(ifstream&);
    QueryResult query(const string&) const;
private:
    shared_ptr<StrBlob> file;
    map<string, shared_ptr<set<line_no>>> wm;
};

class QueryResult
{
    friend ostream& print(ostream&, const QueryResult&);
public:
    using line_no = vector<string>::size_type;
    QueryResult(string s,
                shared_ptr<set<line_no>> p,
                shared_ptr<StrBlob> f):
        sought(s), lines(p), file(f) { }
    set<line_no>::iterator begin() { return lines->begin(); }
    set<line_no>::iterator end() { return lines->end(); }
    shared_ptr<shared_ptr<StrBlob>> get_file();
private:
    string sought;
    shared_ptr<set<line_no>> lines;
    shared_ptr<StrBlob> file;

};

string modifyWord(string &word)
{
    auto &e = word.back();
    if (ispunct(e))
        word.erase(word.end() - 1);
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    return word;
}

class StrBlobPtr;

class StrBlob
{
public:
    friend class StrBlobPtr; //友元，可以访问data
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

    StrBlobPtr query(size_t);

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

TextQuery::TextQuery(ifstream &is): file(new StrBlob)
{
    string text;
    cout << "t1" << endl;
    while (getline(is, text))
    {
        cout << text << endl;
        file->push_back(text); //每一行存入vector
        int n = file->size() - 1; //行号减一当作下标
        istringstream line(text);
        string word;
        while (line >> word) //把word存入map
        {
            word = modifyWord(word); //大小写转换去除标点
            auto &lines = wm[word]; //指向set
            if (!lines) //第一次遇到这个单词时这个指针为空
                lines.reset(new set<line_no>); //分配一个新的set
            lines->insert(n); //插入一个行号
        }
    }
}

QueryResult TextQuery::query(const string &sought) const
{
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

shared_ptr<shared_ptr<StrBlob>> QueryResult::get_file()
{
    return make_shared<shared_ptr<StrBlob>>(file);
}

string make_plural(size_t s, const string word, const string p)
{
    if (s > 1)
        return word + p;
    return word; 
}

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
inline StrBlobPtr StrBlob::query(size_t curr)
{
    return StrBlobPtr(*this, curr);
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

ostream &print(ostream &os, const QueryResult &qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " "
       << make_plural(qr.lines->size(), "time", "s") << endl;
    
    for (auto num : *qr.lines)
        os << "\t(line " << num + 1 << ") "
           << (qr.file->query(num)).deref() << endl; //StrBlobPtr没有定义加的运算符和*解引用
    return os;                                       //定义一个query相当于迭代器的加操作
}