#include <iostream>

using namespace std;

//5.18
void f1()
{
    do
    {
        int v1, v2;
        cout << "Please enter two numbers to sum:";
        if (cin >> v1 >> v2)
            cout << "Sum is: " << v1 + v2 << endl;
    } while (cin);

}

int main()
{
    f1();

    return 0;
}