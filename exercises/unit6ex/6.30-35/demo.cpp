#include <iostream>
#include <string>
#include <vector>

using namespace std;

//6.30
bool str_subrange(const string &str1, const string &str2)
{
    if (str1.size() == str2.size())
        return str1 == str2;

    auto size = (str1.size() < str2.size())
                    ? str1.size()
                    : str2.size();

    for (decltype(size) i = 0; i != size; ++i)
    {
        if (str1[i] != str2[i])
            return 1;
        //return;
        //error: return-statement with no value, in function returning 'bool' [-fpermissive]
        //warning: control reaches end of non-void function [-Wreturn-type]
    }
}

//6.31

//6.32
int &get(int *arry, int index)
{
    return arry[index];
}

//6.33
void vout(vector<int> iv, vector<int>::size_type size)
{
    cout << iv[size - 1] << endl;
    if (size != 1)
        vout(iv, size - 1);
}

//6.34
int fact(int val)
{
    if (val != 0)  //似乎没有问题，除非传入参数值为负
        return fact(val - 1) * val;
    return 1;
}

//6.35

//val-- 先用后减

int main()
{
    //cout << str_subrange("fssfsfsf", "asdaffffff") << endl;

    // int ia[10];
    // for (int i = 0; i != 10; ++i)
    //     cout << (get(ia, i) = i);

    // vector<int> iv = {1,2,3,4,5};
    // vout(iv, iv.size());

    cout << fact(5);
}