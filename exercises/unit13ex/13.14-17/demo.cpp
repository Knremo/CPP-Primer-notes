#include <iostream>

using namespace std;

struct numbered
{
    time_t mysn;
    static size_t count;

    numbered();
    numbered(const numbered&); //13.15
};
size_t numbered::count = 0;

numbered::numbered()
{
    ++count;
    mysn = count;
    cout << "mysn is: " << mysn << endl;
}
//13.15
numbered::numbered(const numbered& o)
{
    ++count;
    mysn = count;
    cout << "copy mysn is: " << mysn << endl;    
}

//13.14
void f(numbered s) 
{
    cout << s.mysn << endl;
}

void f2(const numbered &s) 
{
    cout << s.mysn << endl;
}

int main()
{
    numbered a, b = a, c = b; //只有第一个是构造函数，后两个是拷贝构造函数
    f(a); f(b); f(c); // 13.14 13.15

    /* 13.14
    mysn is: 1
    1
    1
    1
    */

    /* 13.15
    mysn is: 1
    copy mysn is: 2
    copy mysn is: 3
    copy mysn is: 4 //f
    4
    copy mysn is: 5
    5
    copy mysn is: 6
    6
    */
    
    f2(a); f2(b); f2(c); //13.16

    /* 13.16
    mysn is: 1
    copy mysn is: 2
    copy mysn is: 3
    1
    2
    3
    */
    return 0;
}