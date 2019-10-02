#include <iostream>
#include <vector>
#include <string>
using namespace std;

//9.50
void istr2sum(const vector<string> &vs)
{
    int sum = 0;
    for (auto e : vs)
    {
        sum += stoi(e);
    }
    cout << sum << endl;
}

void fstr2sum(const vector<string> &vs)
{
    double sum = 0;
    for (auto e : vs)
    {
        sum += stod(e);
    }
    cout << sum << endl;
}

//9.51
class Date
{
private:
    unsigned year, month, day;

public:
    Date(const string &);
};

Date::Date(const string &s)
{
    cout << s;

    string spt = " ,./-";
    size_t sp1, sp2;
    sp1 = s.find_first_of(spt);
    sp2 = s.find_first_of(spt, sp1 + 1);

    //cout << sp2 << endl;
    string sm(s, 0, sp1), sd(s, sp1 + 1, sp2 - sp1 - 1), sy(s, sp2 + 1);
    //cout << sy << endl;

    vector<string> im = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (size_t i = 0; i < 12; ++i)
    {
        if (sm.find(im[i]) == 0)
            sm = to_string(i+1);
    }
    //cout << sm << endl;

    month = stoi(sm);
    day = stoi(sd);
    year = stoi(sy);

    cout << " --> " << year << "-" << month << "-" << day << endl;
}

int main()
{
    vector<string> vs = {"1", "2", "3"};
    istr2sum(vs);

    vector<string> vs2 = {"1.5", "2.5", "3.0"};
    fstr2sum(vs2);

    Date date("3-12,1566");

    return 0;
}