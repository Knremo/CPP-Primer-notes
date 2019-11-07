#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::placeholders;

//10.22
bool check_size(const string &s, string::size_type sz)
{
    return s.size() <= sz;
}
void biggies(vector<string> &words, vector<string>::size_type sz)
{
    auto wc = count_if(words.begin(), words.end(),bind(check_size, _1, sz));
    cout << wc << endl;
}

//10.23

//10.24
void f3(const vector<int> iv, const string &s)
{
    auto wc = find_if(iv.begin(), iv.end(), bind(check_size, s, _1));
    cout << *wc << endl;
}

//10.25
void bind_biggies(vector<string> &words, vector<string>::size_type sz)
{
    auto wc = partition(words.begin(), words.end(),
                        bind(check_size, _1, sz)); 

    auto count = wc - words.begin();
    cout << count << " ";

    for_each(words.begin(), wc,
             [](const string &s){cout << s << " ";});
    cout << endl;
}

int main()
{
    vector<string> vs = {"I", "wanna", "bee", "free"};
    biggies(vs, 6);

    vector<int>  vi = {1, 2, 3, 4, 5};
    f3(vi, "help");

    bind_biggies(vs, 3);
    return 0;
}