#include <iostream>
#include <string>
#include <cctype>
using std::string;


//3.9 合法
void f1()
{
    string s;
    std::cout << s[0] << std::endl;
}

// 3.10
int f2()
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

//3.11 合法，c应该是const char&
void f3()
{
    const string s = "rock u!";
    for (auto &c:s)
    std::cout << c << std::endl;
}

int main()
{
    f2();
    return 0;
}