#include <iostream>
#include <vector>

//7.43
class NoDefault
{
public:
    NoDefault(int i) { std::cout << "init with " << i << std::endl; }
    //NoDefault() {}
};

class C
{
public:
    C(): nd(0) {}
    C(int i): nd(i) {}

private:
    NoDefault nd;
};

//7.44
//std::vector<NoDefault> vec(10); //没有默认初始化就会编译报错

//7.45
std::vector<C> vec2(10, C(5)); //没问题

//7.46

int main()
{
    C c, cc(1);
    //NoDefault nd; //xxxxxx

    std::cout << vec2.size() << std::endl;
}