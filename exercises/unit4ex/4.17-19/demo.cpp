#include <iostream>
#include <vector>

using namespace std;

//4.17

//4.18
//从第二个开始，先输出下一个元素，如果为负就停止

//4.19
void f1()
{
    int i = 0;
    int *ptr = &i;
    vector<int> vec = {1, 2, 3};
    int ival = 0;

    //如果ptr没有初始化，即为未定义，也不是0空指针；初始化为0才会==0
    //ptr如果初始化为i的指针，则不是空指针
    //*ptr++先+1但结果是原来的值，ptr如果没有初始化，则*ptr为未定义，
    //*ptr++和*++ptr都是未定义，不为0
    //如果初始化为i，则对*ptr++，i=0为0，i=1为1;对*++ptr都为0
    if (ptr != 0 && *ptr++)
        cout << 1 << endl;

    //默认初始化ival++为false,ival为false
    //ival=0,1,ival++会不一样
    //有明确的求值顺序
    if (ival++ && ival)
        cout << 2 << endl;

    //前一个元素小于等于后一个
    if (vec[ival++] <= vec[ival])
        cout << 3 << endl;
}

int main()
{
    f1();

    return 0;
}