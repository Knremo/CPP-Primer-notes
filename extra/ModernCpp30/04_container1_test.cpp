#include <vector>
#include <iostream>
using namespace std;

class O1 {
public:
    O1() { cout << "O1()\n"; }
    O1(const O1&)
    {
        cout << "O1(const O1&)\n";
    }
    O1(O1&&)
    {
        cout << "O1(O1&&)\n";
    }
};

class O2 {
public:
    O2() { cout << "O2()\n"; }
    O2(const O2&)
    {
        cout << "O2(const O2&)\n";
    }
    O2(O2&&) noexcept
    {
        cout << "O2(O2&&)\n";
    }
};

int main() 
{
    vector<O1> v1;
    v1.reserve(2);
    cout << v1.capacity() << endl;
    v1.emplace_back();
    v1.emplace_back();
    v1.emplace_back();

    vector<O2> v2;
    v2.reserve(2);
    cout << v2.capacity() << endl;
    v2.emplace_back();
    v2.emplace_back();
    v2.emplace_back();

    return 0;
}