#include <iostream>

using namespace std;

//13.4
class Point
{
public:
    Point() { }
    Point(const Point&);
private:
    int num = 0;
};
Point::Point(const Point &orig):
    num(orig.num)
{
    cout << "I'm here." << endl;
}

Point global;
Point foo_bar(Point arg) //类作为实参传递给非引用类型的形参，调用1
{
    Point local = arg, *heap = new Point(global);
    // 拷贝初始化调用2
    // 用一个对象去初始化另一个对象调用3
    *heap = local; //赋值没有调用 
    Point pa[4] = { local, *heap }; // 用花括号列表初始化一个数组中的元素有两个调用4，5
    return *heap; //从一个返回类型为非引用类型的函数返回一个对象，调用6
}

//13.5
class HasPtr
{
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr&);
private:
    std::string *ps;
    int i;
};
HasPtr::HasPtr(const HasPtr &o):
    ps(new string(*o.ps)), i(o.i) { }
// {
//     ps = new string();
//     *ps = *o.ps;
// }

int main()
{
    Point p; //不会调用
    foo_bar(p);
    /** result:
    I'm here.
    I'm here.
    I'm here.
    I'm here.
    I'm here.
    I'm here.
    */
    return 0;
}