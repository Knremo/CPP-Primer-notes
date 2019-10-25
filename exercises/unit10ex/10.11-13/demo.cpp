#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//10.11
void elimDups(vector<string> &words)
{
    sort(words.begin(), words.end());
    auto end_unique = unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

void f1(vector<string> &words)
{
    elimDups(words);
    stable_sort(words.begin(), words.end(), isShorter);
}

//10.2
struct Sales_data
{
    Sales_data(const string &isbn) : bookNo(isbn) {}

    string isbn() const { return bookNo; }
    string bookNo;
};

vector<Sales_data> sv = {Sales_data("997"), Sales_data("9966"), Sales_data("998")};

bool compareIsbn(const Sales_data &s1, const Sales_data &s2)
{
    return s1.isbn().size() < s2.isbn().size();
}

void f2(vector<Sales_data> &sv)
{
    stable_sort(sv.begin(), sv.end(), compareIsbn);

    for (auto e : sv)
        cout << e.isbn() << endl;
}

// 10.13
bool getlength(const string &s)
{
    return s.size() > 4 ? true : false;
}

void f3(vector<string> &s)
{
    partition(s.begin(), s.end(), getlength);
    for (auto e : s)
        cout << e << endl;
}


int main()
{
    vector<string> words = {"I", "just", "want", "to", "play", "alone", "ok", "h", "play"};
    // f1(words);
    // for (auto e : words)
    //     cout << e << " ";

    f3(words);

    return 0;
}