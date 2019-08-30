#include <vector>

class Example
{
public:
    static double rate; //类内初始化数据成员必须有constexpr
    static constexpr int vecSize = 20;
    static std::vector<double> vec; //vector不能类内初始化
};

//类内声明类外初始化
std::vector<double> Example::vec(Example::vecSize, 1.0);
