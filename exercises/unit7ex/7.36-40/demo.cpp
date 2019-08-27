#include <iostream>
using namespace std;

//7.36
struct  X
{
    X(int i, int j): base(i), rem(base % j) {}
    int base, rem;
};

//7.37

//7.38
class c1
{
    c1(istream &is = cin) {}
};

//7.39
//不合法

//7.40
class Date
{
public:
    Date(unsigned y = 2000, unsigned m = 1, unsigned d = 1)
        : year(y), month(m), day(d) {}
    Date(istream &is) {cin >> year >> month >> day;}

    const Date printDate() const
    {
        cout << year << "-" << month << "-" << day << "." << endl;
        return *this;
    }

private:
    unsigned year;
    unsigned month, day;
};

int main()
{
    Date d1(cin);
    d1.printDate();

    Date d2(2019, 8, 31);
    d2.printDate();

    return 0;
}