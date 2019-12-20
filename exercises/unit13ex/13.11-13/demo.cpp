#include <iostream>
#include <string>
#include <vector>

using namespace std;

//13.11
class HasPtr
{
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
    HasPtr(const HasPtr &);
    HasPtr &operator=(const HasPtr &);
    ~HasPtr();

private:
    std::string *ps;
    int i;
};
HasPtr::HasPtr(const HasPtr &o) : ps(new string(*o.ps)), i(o.i) {}
HasPtr &HasPtr::operator=(const HasPtr &rhs)
{
    ps = new string(*rhs.ps);
    i = rhs.i;
    return *this;
}
HasPtr::~HasPtr() {}

//13.12
class Sales_data
{
public:
    Sales_data(const string &s) : bookNo(s), name(s + " dead") {}
    string isbn() { return bookNo; }
    ~Sales_data() { cout << name << endl; }

private:
    string bookNo;
    string name;
};

bool fcn(const Sales_data *trans, Sales_data accum)
{
    Sales_data item1(*trans), item2(accum); // item1 = s1 ,accum = s2 = item2
    return item1.isbn() != item2.isbn();    //accum被拷贝过来
}

//13.13
struct X
{
    X(const string &name) : n(name) { cout << "X()+" + n << endl; }
    X(const X &s)
    {
        n = s.n + "*";
        cout << "X(const X&)+" + n << endl;
    }
    X &operator=(const X &rhs)
    {
        cout << "X& operator=(const X&)+" + n << endl;
        return *this;
    }
    ~X() { cout << "~X()+" + n << endl; }
    string n;
};
void fref(X &x)
{
    cout << "void fref(X& x)" << endl;
}
void fnref(X x)
{
    cout << "void fnref(X x)" << endl;
}

int main()
{
    Sales_data *p1 = new Sales_data("s1"); // new的不会在结束时自动销毁
    Sales_data s2("s2");                   // 会自动销毁
    fcn(p1, s2);                           //有3个dead，item1,item2,accum

    delete p1; //s2第5个，p1第4个
    /*
    s2 dead
    s1 dead
    s2 dead
    s1 dead // delete p1
    s2 dead // 作用域结束s2自动销毁
    */

    //13.13
    X x("1");
    fref(x);
    fnref(x);
    auto p = new X("2");
    vector<X> vec = {x, *p};
    X x2("3");
    vec.reserve(100);
    vec.push_back(x2);
    /*
    X()+1 //x构造函数
    void fref(X& x) //fref 没有拷贝构造
    X(const X&)+1* //fnref 的形参拷贝构造一个1的拷贝1*
    void fnref(X x) //fnref
    ~X()+1* //fnref结束销毁之前的局部变量1*
    X()+2 //2的构造函数 new
    X(const X&)+1* //vec添加元素x，拷贝构造1*
    X(const X&)+2* //同上
    X(const X&)+1** //可能是vec内存分配换地方
    X(const X&)+2**
    ~X()+2* //销毁之前的vec中的2*和1*因为已经拷贝到新的大地方
    ~X()+1*
    X()+3 //3构造
    X(const X&)+1*** //vec.reserve(100)开辟了一块大内存，先把1**和2**拷贝构造过来
    X(const X&)+2***
    ~X()+1** //销毁不用的1**，2**
    ~X()+2**
    X(const X&)+3* //添加3，因为够大不需要将2***，1***再次移动
    //ruturn结束之后自动销毁对象
    ~X()+3 //3
    ~X()+1*** //vec
    ~X()+2***
    ~X()+3*
    ~X()+1 //1 ，new的2无人销毁因为没有delete
    */
    return 0;
}