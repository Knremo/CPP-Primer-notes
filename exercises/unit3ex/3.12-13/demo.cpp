#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;

int main()
{
    vector<vector<int>> ivec;
    //vector<string> svec = ivec; //x
    vector<string> svec(10, "null");

    // 3.13
    vector<string> v6{10};
    vector<string> v7{10, "hi"};

    std::cout << v6.size() << std::endl; //10
}
