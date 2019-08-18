#include <iostream>
#include <string>

using namespace std;

//6.43

//6.44
inline bool isShorter1(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

//6.45

//6.46
constexpr bool isShorter2(const string &s1, const string &s2)
{
    
    return s1.size() < s2.size();

}
//不可以啊

int main()
{
    cout << isShorter2("asd", "asdf") << endl;

    return 0;
}