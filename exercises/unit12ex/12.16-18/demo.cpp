#include <memory>
#include <iostream>

using namespace std;

//12.16
void f1()
{
    unique_ptr<int> p1(new int(42));
    //unique_ptr<int> p2(p1);
    unique_ptr<int> p3;
    //p3 = p1;
}

void f2()
{
    int ix = 1024, *pi = &ix, *pi2 = new int(2048);
    typedef unique_ptr<int> IntP;
    //IntP p0(ix);
    IntP p1(pi);
    IntP p2(pi2);
    IntP p3(&ix);
    IntP p4(new int(2048));
    IntP p5(p2.get());
}

//12.18

int main()
{
    f1();

    return 0;
}