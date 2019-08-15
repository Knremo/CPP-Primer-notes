#include <iostream>
#include <string>

using namespace std;

//6.36
string a1[4] = {"a", "b", "c", "d"};

string (&f1(string (&stringarr)[4]))[4]
{
    return stringarr; 
}

//6.37
typedef string arr[4];
//using arr = string[4];
arr &f2(arr &stringarr)
{
    return stringarr;
}

auto f3(arr &stringarr) -> string(&)[4]
{
    return stringarr;
}

decltype(a1) &f4(arr &stringarr)
{
    return stringarr;
}

//6.38
int odd[] = {1,3,5,7,9};
int even[] = {0,2,4,6,8};

decltype(odd) &arrPtr(int i)
{
    return (i % 2) ? odd : even;
}

int main()
{
    string a2[4];
    f1(a1);
}