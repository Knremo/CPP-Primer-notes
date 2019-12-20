#include <iostream>
#include <string>

using namespace std;

class HasPtr
{
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr&);
    HasPtr& operator=(const HasPtr&);
private:
    std::string *ps;
    int i;
};
HasPtr::HasPtr(const HasPtr &o):
    ps(new string(*o.ps)), i(o.i) { }
HasPtr& HasPtr::operator=(const HasPtr& rhs )
{
    ps = new string(*rhs.ps);
    i = rhs.i;
    return *this;
}