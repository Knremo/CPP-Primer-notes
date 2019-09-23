#include <iostream>
#include <string>

using namespace std;

//9.43
void f1(string &s, const string &oldVal, const string &newVal)
{
    size_t i = 0;
    while (i != s.size())
    {
        if (s[i] == oldVal.front())
        {
            //cout << "1 assert done" << endl;
            string temp(s, i, oldVal.size());
            //cout << temp << endl;
            if (temp == oldVal)
            {
                //
                //cout << "2 assert done" << endl;
                s.erase(i, oldVal.size());
                //cout << s << endl;
                s.insert(i, newVal);
                //cout << s << endl;

                i += newVal.size() - 1;
                //cout << i << endl;
            }
            else
                i++;

        }
        if (i == s.size() - oldVal.size())
            break;
        i++;
    }
}

int main()
{
    string s = "the one the best!";
    f1(s, "!", ".");

    cout << s << endl;

    return 0;
}