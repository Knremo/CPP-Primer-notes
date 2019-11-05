#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//10.20
void biggies(vector<string> &words, vector<string>::size_type sz)
{
    auto wc = count_if(words.begin(), words.end(),
         [sz](const string &a){ return a.size() >= sz; }); 

    cout << wc << endl;
}

//10.21
void f2()
{
    int i = 4;
    auto f = [&i]() -> bool {while(i != 0){--i;} return true;};
    cout << f() << " " << i << endl;
}

int main()
{
    vector<string> vs = {"I", "wanna", "be", "free"};
    biggies(vs, 3);

    f2();
    return 0;
}