#include <iostream>
#include <string>
#include <cctype>
using std::string;

/*
//3.9 合法
int main()
{
    string s;
    std::cout << s[0] << std::endl;
}
*/

/*
//3.11 合法，c应该是const char&
int main()
{
    const string s = "rock u!";
    for (auto &c:s)
    std::cout << c << std::endl;
}
*/

int main()
{
    string input = "I am a lazy boy!OH,NO!HELP!:)";
    string result;
    for (auto c : input)
    {
        if (ispunct(c))
            continue;
        result += c;
    }
    std::cout << result << std::endl;
    return 0;
}