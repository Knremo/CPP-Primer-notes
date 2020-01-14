// 13.49
/* StrVec
StrVec &StrVec::operator=(StrVec &&rhs) noexcept
{
    cout << "StrVec &operator=(StrVec&&);" << endl;
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
StrVec::StrVec(StrVec &&s) noexcept
    : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    cout << "StrVec(StrVec &&s);" << endl;
    s.elements = s.first_free = s.cap = nullptr;
    
}
*/
/* String
String::String(String&& s) noexcept
    : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    cout << "String(String&& s) noexcept" << endl;
    s.elements = s.first_free = s.cap = nullptr;
}
String& String::operator=(String&& rhs) noexcept
{
    cout << "String& operator=(String&&)" << endl;
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
*/

//13.50
/*
vector<String> vS;
vS.push_back("s1");
vS.push_back("s2");
>>>
String(String&& s) noexcept
String(String&& s) noexcept
String(String&& s) noexcept
*/

//13.51

//13.52
#include <string>
#include <iostream>

class HasPtr
{
    friend void swap(HasPtr&, HasPtr&);
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0) {  }
    HasPtr(const HasPtr &p):
        ps(new std::string(*p.ps)), i(p.i) 
    { std::cout << "HasPtr(const HasPtr&)" << std::endl; }
    HasPtr(HasPtr &&p) noexcept
        : ps(p.ps), i(p.i) 
    { 
        p.ps = 0; 
        std::cout << "HasPtr(HasPtr&&) noexcept" << std::endl;
    }
    HasPtr& operator=(HasPtr rhs)
    {
        std::cout << "HasPtr& operator=(HasPtr)" << std::endl;
        swap(*this, rhs);
        return *this;
    }
    ~HasPtr() { delete ps; std::cout << "~HasPtr()" << std::endl; }
private:
    std::string *ps;
    int i;
};
void swap(HasPtr& lhs, HasPtr& rhs)
{
    std::cout << "void swap(HasPtr&, HasPtr&)" << std::endl;
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

void f1()
{
    HasPtr hp, hp2;
    hp = hp2;
    hp = std::move(hp2);
    /*
    HasPtr(const HasPtr&) // 拷贝构造函数，rhs = hp2
    HasPtr& operator=(HasPtr) // 赋值运算符
    void swap(HasPtr&, HasPtr&) // swap(hp, hp2的副本)
    ~HasPtr() // 销毁rhs

    HasPtr(HasPtr&&) noexcept // 移动构造函数，rhs = std::move(hp2)
    HasPtr& operator=(HasPtr)
    void swap(HasPtr&, HasPtr&)
    ~HasPtr()
    ~HasPtr()
    ~HasPtr()
    */
}

int main()
{
    f1();

    return 0;
}