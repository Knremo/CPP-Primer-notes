#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// // 13.46
// int f();
// vector<int> vi(100);
// //int& r1 = f();   //xxxx
// // f()是一个右值，非常量左值引用只能绑定到左值
// int&& r1 = f(); // ok

// int& r2 = vi[0]; // ok
// //int&& r2_2 = vi[0];  //xxxxx
// // 右值引用无法绑定到左值

// int& r3 = r1; // ok
// //int&& r3_2 = r1; //xxxx

// int&& r4 = vi[0] * f();
 


// 13.47-48
class String
{
    friend ostream& operator<<(ostream&, const String&);
private:
    char *elements;
    char *first_free;
    char *cap;

    static allocator<char> alloc;

    void reallocate();
    void free();
    void chk_n_alloc();
    pair<char*, char*> alloc_n_copy(const char*, const char*);
public:
    String(const char[]);
    String();
    ~String();
    String(const String&);
    String& operator=(const String&);

    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }

    void push_back(const char);
    void pop_back();
};

allocator<char> String::alloc;

String::String():
    elements(nullptr), first_free(nullptr), cap(nullptr) {  }

String::String(const char p[]):
    elements(nullptr), first_free(nullptr), cap(nullptr)
{
    auto cp = p;
    while (*cp != '\0')
        push_back(*cp++);
}
String::~String()
{
    free();
}
String::String(const String& o)
{
    cout << "String(const String&)" << endl;
    auto newdata = alloc_n_copy(o.elements, o.first_free);
    elements = newdata.first;
    first_free = cap = newdata.second;
}
String& String::operator=(const String& rhs)
{
    cout << "String& operator=(const String&)" << endl;
    auto newdata = alloc_n_copy(rhs.elements, rhs.first_free);
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
    return *this;
}
ostream& operator<<(ostream& o, const String& rhs)
{
    for (auto p = rhs.elements; p != rhs.first_free; ++p)
        o << *p;
    return o;
}

void String::push_back(const char c)
{
    chk_n_alloc();
    alloc.construct(first_free++, c);
}
void String::pop_back()
{
    alloc.destroy(--first_free);
}
void String::chk_n_alloc()
{
    if(size() == capacity())
        reallocate();
}
void String::free()
{
    if (elements)
    {
        for (auto p = first_free; p != elements;)
            alloc.destroy(--p);
        alloc.deallocate(elements, capacity());
    }
}
void String::reallocate()
{
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
pair<char*, char*> String::alloc_n_copy(const char* b, const char* e)
{
    auto newdata = alloc.allocate(e - b);
    return { newdata, uninitialized_copy(b, e, newdata) };
}

int main()
{
    vector<String> vS;
    vS.push_back("s1");
    vS.push_back("s2");

    return 0;
}