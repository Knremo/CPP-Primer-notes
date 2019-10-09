#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cctype>
#include <cstring>

using namespace std;

vector<string> preParse(char *str) //对中缀表达式进行预处理，分离出每个token
{
    vector<string> tokens;
    int len = strlen(str);
    char *p = (char *)malloc((len + 1) * sizeof(char)); //注意不要用 char *p = (char *)malloc(sizeof(str))来申请空间

    int i = 0, j = 0;
    while (i < len) //去除表达式中的空格
    {
        if (str[i] == ' ')
        {
            i++;
            continue;
        }

        p[j++] = str[i++];
    }
    p[j] = '\0';
    j = 0;
    len = strlen(p);
    while (j < len)
    {
        char temp[2];
        string token;
        switch (p[j])
        {
            case '+':
            case '-':
            case '*':
            case '/':
            case '(':
            case ')':
            {
                temp[0] = p[j];
                temp[1] = '\0';
                token = temp;
                tokens.push_back(token);
                break;
            }
            // case '-':
            // {
            //     if (p[j - 1] == ')' || isdigit(p[j - 1])) //作为减号使用
            //     {
            //         temp[0] = p[j];
            //         temp[1] = '\0';
            //         token = temp;
            //         tokens.push_back(token);
            //     }
            //     else //作为负号使用
            //     {
            //         temp[0] = '#';
            //         temp[1] = '\0';
            //         token = temp;
            //         tokens.push_back(token);
            //     }
            //     break;
            // }
            default: //是数字
            {
                i = j;
                while (isdigit(p[i]) && i < len)
                {
                    i++;
                }
                char *opd = (char *)malloc(i - j + 1);
                strncpy(opd, p + j, i - j);
                opd[i - j] = '\0';
                token = opd;
                tokens.push_back(token);
                j = i - 1;
                free(opd);
                break;
            }
        }
        j++;
    }
    free(p);
    return tokens;
}

int main()
{
    string s = "(((a+b)*c)/(d+c))?(b+c)";

    stack<char> st;
    int i = 0;
    while (i < s.size())
    {
        st.push(s[i]);
        if (s[i] == ')')
        {
            while (st.top() != '(')
            {
                st.pop();
            }
            st.pop();
            st.push('*');
        }
        ++i;
    }
    while (!st.empty())
    {
        cout << st.top() << endl;
        st.pop();
    }

    return 0;
}
