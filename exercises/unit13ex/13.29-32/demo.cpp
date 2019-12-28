#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//13.30
class HasPtr
{
    friend void swap(HasPtr &, HasPtr &);

public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
    HasPtr(const char *cs) : ps(new std::string(cs)), i(0) {}
    HasPtr(const HasPtr &);
    ~HasPtr();
    HasPtr &operator=(const HasPtr &);
    bool operator<(const HasPtr &) const;
    void info() { cout << *ps << endl; }
private:
    std::string *ps;
    int i;
};
HasPtr::HasPtr(const HasPtr &o) : ps(new string(*o.ps)), i(o.i) {}
HasPtr::~HasPtr()
{
    delete ps;
}
HasPtr &HasPtr::operator=(const HasPtr &rhs)
{
    auto nps = new string(*rhs.ps);
    delete ps;
    ps = nps;
    i = rhs.i;
    return *this;
}
bool HasPtr::operator<(const HasPtr &rhs) const 
{
    cout << *ps << " " << *rhs.ps << endl;
    return *ps < *rhs.ps;
}
inline void swap(HasPtr &lhs, HasPtr &rhs) {
    std::cout << "swap(HasPtr &lhs, HasPtr &rhs) between <" << *lhs.ps
              << "> and <" << *rhs.ps << ">" << std::endl;
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

int main()
{
    vector<HasPtr> v = { "Hello", "World", "P", "Q", "R", "S", "T", "U",
      "ABC", "DEF", "AB", "C", "D", "E", "F", "G", "H"};
    sort(v.begin(), v.end());
    return 0;
}