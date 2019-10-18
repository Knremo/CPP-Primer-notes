#include <iostream>
#include <vector>

using namespace std;

//10.6
void f1()
{
    vector<int> iv = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    fill_n(iv.begin(), iv.size(), 0);

    for (auto e : iv)
        cout << e << endl;
}

int main()
{
    f1();

    return 0;
}
