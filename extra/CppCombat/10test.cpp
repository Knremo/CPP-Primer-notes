#include <iostream>

using namespace std;

class DemoLambda final
{
private:
    int x = 0;
public:
    auto print()              // 返回一个lambda表达式供外部使用 c++14
    {
        return [this]()      // 显式捕获this指针
        {
            cout << "member = " << x << endl;
        };
    }
};

int main()
{
    DemoLambda d;
    auto f = d.print();
    f();

    return 0;
}