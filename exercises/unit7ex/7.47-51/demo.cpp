#include <iostream>

using namespace std;

//7.47

//7.48

//7.49
class Sales_data 
{
public://整个程序内可以被访问
    Sales_data() = default;
    Sales_data(const std::string &s): bookNo(s) {}
    Sales_data(const std::string &s, unsigned n, double p):
               bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data(std::istream &);
    
    std::string isbn() const { return bookNo; }

    Sales_data &combine(const Sales_data&);
    //Sales_data &combine(Sales_data);
    //Sales_data &combine(Sales_data&);//xxxx,string不能初始化&
    //Sales_data &combine(const Sales_data&) const; //xx,不能修改

private://可以被类的成员函数访问
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

Sales_data &Sales_data::combine(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

int main()
{
    Sales_data i("9-999-99999-9", 10, 4.4);
    string s("1-999-99999-9");
    i.combine(s);
}