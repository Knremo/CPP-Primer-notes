#include <iostream>
#include <string>

using namespace std;

//6.16
bool is_empty(const string& s)
{
    return s.empty();
}

//6.17
void f1(const string& s)
{
    for (auto e : s)
        if (isupper(e))
        {
            cout << "Upper found!" << endl;
            break;
        }
}

void f2(string& s)
{
    for (auto &e : s)
        if (isupper(e))
        {
            e = tolower(e);
        }
    cout << s << endl;
}

//6.19

//6.20


int main()
{
    string s1 = "AssAsfF";
    f2(s1);

    return 0;
}