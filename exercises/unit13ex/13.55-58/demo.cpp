#include <vector>
#include <iostream>

using namespace std;

//13.56
class Foo
{
public:
    Foo sorted() &&; // 用于可改变的右值
    Foo sorted() const &; // 可用于任何类型的Foo
private:
    vector<int> data;
};
// 递归循环
// Foo Foo::sorted() const &
// {
//     Foo ret(*this);
//     return ret.sorted();
// }
Foo Foo::sorted() &&
{
    cout << "Foo sorted() &&" << endl;
    return *this;
}

// 13.57
Foo Foo::sorted() const &
{
    return Foo(*this).sorted(); //匹配右值引用版本
}

int main()
{
    Foo f1;
    f1.sorted();

    return 0;
}