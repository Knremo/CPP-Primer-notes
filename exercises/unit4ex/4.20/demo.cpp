#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string>::iterator iter;

    *iter++;
    //(*iter)++; //string对象没有++操作符
    //*iter.empty(); //迭代器iter没有empty()成员
    iter->empty();
    //++*iter; //string对象没有++操作符
    iter++->empty();
}