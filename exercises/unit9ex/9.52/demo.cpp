#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main()
{
    string expression = "3 * (5+ ( 56 - 6) )/10";
    stack<char, string> stk;

    for (size_t i = expression.size(); i > 0; --i)
    {
        stk.push(expression[i-1]);
    }
    cout << stk.top() << endl;

    while (!stk.empty())
    {
        
    }
}
