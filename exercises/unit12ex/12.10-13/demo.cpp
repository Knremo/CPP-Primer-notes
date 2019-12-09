#include <memory>
#include <iostream>

using namespace std;
//12.10
void process(shared_ptr<int> ptr)
{
    (*ptr)++;
}
void f1()
{
    shared_ptr<int> p(new int(42));
    process(shared_ptr<int>(p));
    cout << *p << endl;
}

//12.11  xxxxxxxx
void f2()
{
    shared_ptr<int> p(new int(42));
    process(shared_ptr<int>(p.get()));
    cout << *p << endl;
}

//12.12
void f3()
{
    auto p = new int();
    auto sp = make_shared<int>();
    process(sp);
    //process(new int());  xxxxxxx
    //process(p); xxxxxxx
    process(shared_ptr<int>(p)); // undefined
}

//12.13
void f4()
{
    auto sp = make_shared<int>(42);
    auto p = sp.get();
    //delete p; 这行会导致出错

    //cout << *p << endl; p已被删除
    //cout << *sp << endl; sp也不能用
    cout << sp.unique() ;
    cout << " asd";
}

int main()
{
    f4();

    return 0;
}