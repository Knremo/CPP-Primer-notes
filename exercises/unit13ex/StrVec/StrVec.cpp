#include <string>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
using namespace std;

class StrVec
{
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(initializer_list<string>);
    StrVec(const StrVec &);
    StrVec &operator=(const StrVec &);
    ~StrVec();

    void push_back(const string &);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    string *begin() const { return elements; }
    string *end() const { return first_free; }
    void resize(size_t, const string&);
    void list();
private:
    static allocator<string> alloc;

    void chk_n_alloc()
    {
        if (size() == capacity())
            reallocate();
    }
    pair<string *, string *> alloc_n_copy(const string *, const string *);
    void free();
    void reallocate();
    string *elements;
    string *first_free;
    string *cap;
};
allocator<string> StrVec::alloc;

StrVec::StrVec(initializer_list<string> ilst) : elements(nullptr), first_free(nullptr), cap(nullptr)
{
    cout << "StrVec(initializer_list<string>);" << endl;
    for (auto s : ilst)
        push_back(s);
}
void StrVec::push_back(const string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s); // first_free指向第一个未构造内存，在此构造之后first_free再+1
}
pair<string *, string *> StrVec::alloc_n_copy(const string *b, const string *e)
{
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};
}
void StrVec::free()
{
    if (elements)
    {
        for (auto p = first_free; p != elements;)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}
StrVec::StrVec(const StrVec &s)
{
    cout << "StrVec(const StrVec &s);" << endl;
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}
StrVec::~StrVec()
{
    cout << "~StrVec();" << endl;
    free();
}
StrVec &StrVec::operator=(const StrVec &rhs)
{
    cout << "StrVec &operator=(const StrVec&);" << endl;
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
void StrVec::reallocate()
{
    cout << "reallocate()" << endl;
    auto newcapacity = size() ? 2 * size() : 1;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}
void StrVec::resize(size_t n, const string &s = string())
{
    if (n >= size())
        for (size_t i = size(); i != n; ++i)
        {
            push_back(s);
        }
    else
    {
        auto d = size() - n;
        for (auto p = first_free; p != first_free - d;)
        {
            alloc.destroy(--p);
        }
        first_free -= d;
    }
    reallocate();
}
void StrVec::list()
{
    auto p = elements;
    while (p != first_free)
        cout << *p++ << " ";
    cout << " size: " << size() 
         << " capacity: " << capacity() <<  endl;
}

int main()
{
    StrVec sv = {"a", "b"};
    sv.push_back("c");
    cout << *(sv.begin() + 2) << endl;
    sv.list();
    sv.resize(5, "p");
    sv.list();
    sv.resize(10, "f");
    sv.list();
    sv.resize(2);
    sv.list();
    sv.push_back("bbb");
    sv.list();
    sv.resize(0);
    sv.list();
    sv.push_back("0");
    sv.list();
    sv.push_back("1");
    sv.list();
    sv.push_back("2");
    sv.list();
    sv.resize(0);
    sv.list();
    return 0;
}