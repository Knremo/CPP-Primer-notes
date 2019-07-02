#include <iostream>

using namespace std;

int main()
{
    int sum = 0, val = 1;

    while (val <= 10)
        sum += val, ++val;

    cout << "Sum of 1 to 10 inclusive is " << sum << endl;

    return 0;
}