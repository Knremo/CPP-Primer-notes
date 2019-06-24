#include <iostream>

using namespace std;

//3.43
int ia[3][4] = {
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {8, 9, 10, 11}
};

void f1()
{
    for (int (&row)[4] : ia)
        for (int col : row)
            cout << col << " ";
}

void f2()
{
    for (int (*p)[4] = ia; p != ia + 3; ++ p)
    {
        for (int *q = *p; q != *p + 4; ++q)
            cout << *q << " ";
    }
}

void f3()
{
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 4; ++col)
            cout << ia[row][col] << " ";
}

//3.44
void f4()
{
    using int_array = int[4];
    //typedef int int_array[4]

    for (int_array &row : ia)
        for (int col : row)
            cout << col << " ";
}

void f5()
{
    typedef int int_array[4];

    for (int_array *p = ia; p != ia + 3; ++ p)
    {
        for (int *q = *p; q != *p + 4; ++q)
            cout << *q << " ";
    }
}

//3.45
void f6()
{
    for (auto &row : ia)
        for (auto col : row)
            cout << col << " ";
}

void f7()
{
    for (auto p = ia; p != ia + 3; ++ p)
    {
        for (auto q = *p; q != *p + 4; ++q)
            cout << *q << " ";
    }
}

int main()
{
    //不使用类型别名，auto
    f1();
    cout << endl;
    f2();
    cout << endl;
    f3();

    //使用类型别名，不用auto
    cout << endl;
    f4();
    cout << endl;
    f5();

    //使用类型别名，auto
    cout << endl;
    f6();
    cout << endl;
    f7();
    
    return 0;
}