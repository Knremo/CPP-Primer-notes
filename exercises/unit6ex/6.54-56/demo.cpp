#include <vector>
#include<iostream>

using namespace std;

//6.54
int f1(int a, int b){return a*10+b;}
vector<int(*)(int, int)> v1 = {f1};

//6.55
int add(int a, int b){return a+b;}
int minu(int a, int b){return a-b;}
int multiply(int a, int b){return a*b;}
int divide(int a, int b){return a/b;}

vector<int(*)(int, int)> v2 = {add, minu, multiply, divide};

//6.56
int main()
{
    cout << v1[0](3,4) << endl;
    cout << v2[0](3,4) << endl;
    cout << v2[1](3,4) << endl;
    cout << v2[2](3,4) << endl;
    cout << v2[3](3,4) << endl;
}