#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cstring>

using namespace std;

vector<string> parseExpression(const string &original_expression)
{
    vector<string> tokens;
    tokens.reserve(original_expression.size());

    size_t i = 0;
    while (i < original_expression.size())
    {
        //cout << original_expression[i] << endl;

        if (original_expression[i] != ' ')
        {
            switch (original_expression[i])
            {
            case '+':
            case '-':
            case '*':
            case '/':
            case '(':
            case ')':
                /* code */
                tokens.push_back(string() + original_expression[i]);
                break;

            default:
                string digit(1, original_expression[i]);
                size_t j = i + 1;
                while (j < original_expression.size())
                {
                    if (isdigit(original_expression[j]))
                    {
                        digit.push_back(original_expression[j]);
                        ++j;
                    }
                    else
                        break;
                }
                tokens.push_back(digit);
                i += j - i - 1;
                break;
            }
        }
        ++i;
    }
    return tokens;
}

int getPriority(string s)
{
    if (s == "+" || s == "-")
        return 1;
    if (s == "*" || s == "/")
        return 2;
    if (s == "(" || s == ")")
        return 0;
    return 0;
}

void claculate(stack<int> &stk, string op)
{
    if (op == "+")
    {
        int r = stk.top();
        stk.pop();
        cout << stk.top() << " " << r << endl;
        r += stk.top();
        stk.pop();
        stk.push(r);
    }
    if (op == "-")
    {
        int r = stk.top();
        stk.pop();
        cout << stk.top() << " " << r << endl;
        r = stk.top() - r;
        stk.pop();
        stk.push(r);
    }
    if (op == "*")
    {
        int r = stk.top();
        stk.pop();
        cout << stk.top() << " " << r << endl;
        r = stk.top() * r;
        stk.pop();
        stk.push(r);
    }
    if (op == "/")
    {
        int r = stk.top();
        stk.pop();
        cout << stk.top() << " " << r << endl;
        r = stk.top() / r;
        stk.pop();
        stk.push(r);
    }
}

int calculateExpression(const string &s)
{
    stack<int> optNum;
    stack<string> optSyl;

    vector<string> tokens = parseExpression(s);

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        if (isdigit(tokens[i][0]))
        {
            optNum.push(stoi(tokens[i]));
        }
        else if (!optSyl.empty() && tokens[i] != ")" && tokens[i] != "(")
        {
            int tokenPriority = getPriority(tokens[i]);
            if (tokenPriority < getPriority(optSyl.top()))
            {
                int p = getPriority(optSyl.top());
                while (p > tokenPriority)
                {
                    cout << "Operator " << optSyl.top() << " with numbers ";
                    claculate(optNum, optSyl.top());
                    optSyl.pop();
                    if (optSyl.empty())
                        break;
                    p = getPriority(optSyl.top());
                }
                cout << "Next step." << endl;
                optSyl.push(tokens[i]);
            }
            else
            {
                optSyl.push(tokens[i]);
            }
        }
        else if (tokens[i] == ")")
        {
            while (optSyl.top() != "(")
            {
                cout << "Operator " << optSyl.top() << " with numbers ";
                claculate(optNum, optSyl.top());
                optSyl.pop();
            }
            optSyl.pop();
        }
        else
            optSyl.push(tokens[i]);
    }

    while (!optSyl.empty())
    {
        cout << "Operator " << optSyl.top() << " with numbers ";
        claculate(optNum, optSyl.top());
        optSyl.pop();
    }
    int result = optNum.top();
    optNum.pop();

    return result;
}

int main()
{
    string expression = "3 * (5+ ( 56 - 6) )/(10 - 2)";

    cout << calculateExpression(expression);

    return 0;

    // stack<char> stk;

    // for (auto e : expression)
    // {
    //     if (e != ' ')
    //     {
    //         stk.push(e);

    //         if (e == ')')
    //         {
    //             stk.pop();
    //             string calulated_expression;
    //             while (stk.top() != '(')
    //             {
    //                 calulated_expression.push_back(stk.top());
    //                 stk.pop();
    //             }
    //             stk.pop();
    //             cout << calulated_expression << endl;
    //             calculate(calulated_expression, stk);
    //         }
    //     }
    // }

    // while (!stk.empty())
    // {
    //     cout << stk.top();
    //     stk.pop();
    // }
}
