#include <vector>
#include <numeric>
#include <iostream>

using namespace std;

//10.3
void f1()
{
    vector<int> iv = {1,2,3,4,5,6};

    cout << accumulate(iv.cbegin(), iv.cend(), 0) << endl;
}

// 10.4
void f2()
{
    vector<double> iv = {1.0,2.5,3.0,4.5,5.5,6.5};
    //cout << accumulate(iv.cbegin(), iv.cend(), 0) << endl; //小数部分会被舍掉 21
    cout << accumulate(iv.cbegin(), iv.cend(), 0.0) << endl;
}

//10.5 两个都是也没啥问题
void f3()
{
    vector<const char*> cv1 = {"s1", "s2"};
    //vector<string> cv1 = {"s1", "s2"};
    vector<const char*> cv2 = {"s1", "s2", "s3", "s4"};
    
    cout << equal(cv1.cbegin(), cv1.cend(), cv2.cbegin()) << endl;
    //cout << *cv1.begin() << endl;
}

int main()
{
    f3();

    const char* p = "abc";
    const char pp[] = "abc";
    //cout << *(p+3) << endl;
    //cout << p[0] << endl;

    cout << sizeof(pp) << endl;
    cout << p[0] << endl;

    int a1[] = {0,1,2,3,4,5,6,7,8,9};
    int a2[sizeof(a1) / sizeof(*a1)];
    cout << sizeof(a1) << " " << sizeof(*a1) << endl;
    
    return 0;
}