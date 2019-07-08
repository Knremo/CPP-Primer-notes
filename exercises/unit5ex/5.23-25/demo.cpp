#include <iostream>
#include <stdexcept>

using namespace std;

//5.23
void f1()
{
    int i1, i2;
    while (cin >> i1 >> i2)
    {
        cout << static_cast<double>(i1) / i2 << endl;
    }
}

//5.24
void f2()
{
    int i1, i2;
    while (cin >> i1 >> i2)
    {
        if (i2 == 0)
            throw runtime_error("Divided by zero.");
        cout << static_cast<double>(i1) / i2 << endl;
    }
}
/*
terminate called after throwing an instance of 'std::runtime_error'   
  what():  Divided by zero.
 */

//5.25
void f3()
{
    int i1, i2;
    while (cin >> i1 >> i2)
    {
        try {
            if (i2 == 0)
            throw runtime_error("Divided by zero.");
            cout << static_cast<double>(i1) / i2 << endl;
        } catch (runtime_error err) {
            cout << err.what() << endl 
                 << "Try Again? Enter Y or N" << endl;
        
        char c;
        cin >> c;
        if (!cin || c =='n')
            break;
        }
    }
}

int main()
{
    f3();

    return 0;
}