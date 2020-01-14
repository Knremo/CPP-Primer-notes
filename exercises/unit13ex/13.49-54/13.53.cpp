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
    HasPtr(HasPtr &&p) noexcept:
        ps(p.ps), i(p.i)
    { 
        p.ps = 0; 
        std::cout << "HasPtr(HasPtr&&) noexcept" << std::endl;
    }
    HasPtr& operator=(const HasPtr& rhs)
    {
        std::cout << "HasPtr& operator=(HasPtr&)" << std::endl;
        auto newp = new std::string(*rhs.ps);
        delete ps;
        ps = newp;
        i = rhs.i;
        return *this;
    }
    HasPtr& operator=(HasPtr&& rhs) noexcept
    {
        std::cout << "HasPtr& operator=(HasPtr&&)" << std::endl;
        if (this != &rhs)
        {
            delete ps;
            ps = rhs.ps;
            rhs.ps = nullptr;
            rhs.i = 0;
        }
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