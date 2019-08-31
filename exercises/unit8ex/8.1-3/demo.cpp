#include <iostream>
#include <string>
using namespace std;

//8.1
istream &readfromstream(istream &is)
{
    string s;
    while(!is.eof())
    {
        is >> s;
        cout << s;
    }
    is.clear();
    return is;
}

int main()
{
    readfromstream(cin);

    return 0;
}