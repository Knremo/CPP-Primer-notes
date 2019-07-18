#include <iostream>
#include <string>

using namespace std;

//6.25
int main(int argc, char *argv[])
{
    if (argc != 3)
        return 1;

    string s;
    s = argv[1] + s + argv[2];

    cout << s << endl;

    return 0;
}
