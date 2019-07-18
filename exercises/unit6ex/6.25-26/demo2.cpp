#include <iostream>

using namespace std;

//6.26
int main(int argc, char *argv[])
{
    for (size_t i = 1; i != argc; ++i)
    {
        cout << argv[i] << endl;
    }

    return 0;
}