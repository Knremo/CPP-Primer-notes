#include <iostream>
#include <string>

using namespace std;

//6.40

//6.41

//6.42

string make_plural(size_t ctr, const string &word,
                   const string &ending = "s")
{
    return (ctr > 1) ? word + ending : word;
}

int main(int argc, char *argv[])
{
    cout << "两单词的单数形式：" << make_plural(1, "success", "es") << "  " << make_plural(1, "failure") << endl;
    cout << "两单词的复数形式：" << make_plural(2, "success", "es") << "  " << make_plural(2, "failure") << endl;
    return 0; //代表执行成功
}
