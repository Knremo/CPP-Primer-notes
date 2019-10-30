#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//10.14
auto f = [](int a, int b) { return a + b; };

//10.15
void f2(int a)
{
    auto r = [a](int b) { return a + b; };
    cout << r(5);
}

//10.16

//10.17
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

void f3(vector<Sales_data> &sv)
{
    stable_sort(sv.begin(), sv.end(), 
                [](const Sales_data &s1, const Sales_data &s2){return s1.isbn().size() < s2.isbn().size();});

    for (auto e : sv)
        cout << e.isbn() << endl;
}

//10.18
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
void biggies(vector<string> &words, vector<string>::size_type sz)
{
    //elimDups(words);
    //stable_sort(words.begin(), words.end(), isShorter);
    auto wc = partition(words.begin(), words.end(),
         [sz](const string &a){ return a.size() >= sz; }); 
    // find_if第三个参数是一个一元谓词，不能同时接受string和sz
    // 返回第一个使谓词返回非0值得的元素的迭代器

    // 计算满足的个数
    auto count = wc - words.begin();
    cout << count << endl;

    // for_each算法
    for_each(words.begin(), wc,
             [](const string &s){cout << s << " ";});
    cout << endl;
}

//10.19
void stable_biggies(vector<string> &words, vector<string>::size_type sz)
{
    for_each(words.begin(), words.end(),
             [](const string &s){cout << s << " ";});
    cout << endl;
    //elimDups(words);
    //stable_sort(words.begin(), words.end(), isShorter);
    auto wc = stable_partition(words.begin(), words.end(),
         [sz](const string &a){ return a.size() >= sz; }); 
    // find_if第三个参数是一个一元谓词，不能同时接受string和sz
    // 返回第一个使谓词返回非0值得的元素的迭代器

    // 计算满足的个数
    auto count = wc - words.begin();
    cout << count << endl;

    // for_each算法
    for_each(words.begin(), wc,
             [](const string &s){cout << s << " ";});
    cout << endl;
}

int main()
{
    cout << f(1, 2);

    f2(1);
    f3(sv);
    vector<string> vv = {"May", "the", "force", "be", "with", "you"};
    //biggies(vv, 3);
    stable_biggies(vv, 3);
}