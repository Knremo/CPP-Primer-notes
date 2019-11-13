#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

// 10.29
void f1()
{
    ifstream file("text.txt");
    istream_iterator<string> in(file), eof;
    ostream_iterator<string> out(cout, "\n");
    vector<string> vec;

    while (in != eof)
        vec.push_back(*in++);

    file.close();
    copy(vec.begin(), vec.end(), out);
}

// 10.30
void f2()
{
    istream_iterator<int> in(cin), eof;
    ostream_iterator<int> out(cout, "\n");
    vector<int> vec;

    while (in != eof)
    {
        vec.push_back(*in++);
    }

    sort(vec.begin(), vec.end());
    copy(vec.begin(), vec.end(), out);
}

//10.31
void f3()
{
    istream_iterator<int> in(cin), eof;
    ostream_iterator<int> out(cout, "\n");
    vector<int> vec;

    while (in != eof)
        vec.push_back(*in++);

    sort(vec.begin(), vec.end());
    unique_copy(vec.begin(), vec.end(), out);
}

//10.32
struct Sales_data
{
    Sales_data(const string &isbn, const int c) : bookNo(isbn), count(c) {}

    string isbn() const { return bookNo; }
    string bookNo;
    int count;
};
vector<Sales_data> sv = {Sales_data("997", 12), Sales_data("9966", 2), Sales_data("998", 3), Sales_data("9966", 4)};

bool compareIsbn(const Sales_data &s1, const Sales_data &s2)
{
    return s1.isbn().size() < s2.isbn().size();
}

void f4(vector<Sales_data> &sv)
{
    stable_sort(sv.begin(), sv.end(), compareIsbn);
    for (auto e : sv)
        cout << e.isbn() << endl;

}

//10.33
void f5(const string &in, const string &out_odd, const string &out_even)
{
    ofstream out_o(out_odd);
    ofstream out_e(out_even);
    ifstream in_s(in);
    istream_iterator<int> in_iter(in_s), eof;
    ostream_iterator<int> out_iter_o(out_o, " ");
    ostream_iterator<int> out_iter_e(out_e, "\n");

    while (in_iter != eof)
    {
        if (*in_iter % 2 == 0)
            out_iter_o = *in_iter;
        else
            out_iter_e = *in_iter;
        
        in_iter++;
    }

    out_o.close();
    out_e.close();

}

int main()
{
    f5("num.txt", "odd.txt", "even.txt");

    return 0;
}