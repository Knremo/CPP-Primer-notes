#include <iostream>
#include <cstring>

using namespace std;

//3.37
void f1()
{
    const char ca[] = {'h', 'e','l','l','o'};
    const char *cp = ca;
    while(*cp)
    {
        cout << *cp << endl;
        ++cp;
    }
}

//3.38

//3.39
void f2()
{
    string s1 = "hello", s2 = "hello";

    if (s1 == s2)
    cout << 1 << endl;
}

void f3()
{
    char s1[] = "hello", s2[] = "world";
    int r = strcmp(s1, s2);
    cout << r;
}

//3.40
void f4()
{
    char s1[] = "hello", s2[] = "world";
    char s3[20];

    strcpy(s3, s1);
    strcat(s3, s2);

    cout << s3;
}

int main()
{
    f4();

    return 0;
}