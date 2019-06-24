#include <iostream>
#include <vector>
using namespace std;

int txt_size()
{
    return 5;
}

string sa[10];
int iaa[10];

int main()
{
    //3.27
    unsigned buf_size = 1024;
    int ia[buf_size];
    int ib[4 * 7 -14];
    int ic[txt_size()]; // right
    //char st[11] = "fundamental"; // x

    //3.28
    string sa2[10];
    int iaa2[10];

    cout << "sa" << "< " << "iaa"  << "< "<< "sa2" << "< " << "iaa2" << "< " << endl; 
    for (unsigned i = 0; i < 10; ++i)
    {
        cout << sa[i] << "< " << iaa[i] << "< " << sa2[i] << "< " << iaa2[i] << endl; 
        //函数内外string数组初始化为空，int数组在函数外初始化为0，函数内似乎undefine
    }
}

