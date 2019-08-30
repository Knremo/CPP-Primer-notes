#include "example.h"
#include <iostream>

double Example::rate = 1.0;
//std::vector<double> Example::vec(10); //重定义了，报错

int main()
{
    Example e;
    std::cout << e.vec.size() << std::endl;
}