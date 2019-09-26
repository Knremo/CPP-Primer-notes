#include <iostream>
#include <string>

using namespace std;

//9.43
void f2(string &s, const string &oldVal, const string &newVal)
{
    auto sit = s.begin();
    while (sit <= s.end()-oldVal.size())
    {
        if (*sit == oldVal.front())
        {
            string temp(sit, sit + oldVal.size());
            if (temp == oldVal)
            {
                sit = s.erase(sit, sit + oldVal.size());
                sit = s.insert(sit, newVal.begin(), newVal.end());
                sit += newVal.size();
                continue;
            }
        }
        sit++;
    }
}

//9.44
void f1(string &s, const string &oldVal, const string &newVal)
{
    size_t i = 0;
    while (i <= s.size() - oldVal.size())
    {
        if (s[i] == oldVal.front())
        {
            string temp(s, i, oldVal.size());
            if (temp == oldVal)
            {
                s.replace(i, oldVal.size(), newVal);
                i += newVal.size() - 1;
            }
        }
        i++;
    }
}

//9.45
string addpre(const string &s1, const string &p, const string &b)
{
    string sr = s1;
    sr.insert(0, p);
    sr.append(b);
    return sr;
}

//9.46
string addpre2(const string &s1, const string &p, const string &b)
{
    string sr = s1;
    sr.insert(0, p);
    sr.insert(sr.size(), b);
    return sr;
}

int main()
{
    string s = "thethe one the best the";
    f2(s, "the", "aa");

    cout << s << endl;

    cout << addpre2("hahaha", "HH", "gg");
    return 0;
}