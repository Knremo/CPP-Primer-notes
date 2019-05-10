#include <iostream>
#include <string>
#include <cctype>
using std::string;

int main()
{
    string input("123456");
    std::cout << input << std::endl;
    /*
    string::size_type index(0);
    while(index < input.size())
    {
        input[index] = 'X';
        ++index;
    }
*/

    for (string::size_type i = 0; i < input.size(); i++)
    {
        input[i] = 'X';
    }

    std::cout << input << std::endl;
    return 0;
}