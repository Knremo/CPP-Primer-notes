#include <iostream>
#include <string>
#include <cctype>
using std::string;

int main()
{
    string input("sdasdsdsdasdwww   sfsfs\v  sdsdsbbb");
    std::cout << input << std::endl;
    for (char &str : input)
    {
        if (isalnum(str))
        {
            str = 'X';
        }
    }
    std::cout << input << std::endl;
    return 0;
}
// 没有变化