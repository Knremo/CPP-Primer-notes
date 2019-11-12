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



int main()
{
    f1();

    return 0;
}