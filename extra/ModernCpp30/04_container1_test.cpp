#include <vector>
#include <iostream>
using namespace std;

class O1 {
public:
    O1() { ++n; cout << n << " O1()\n"; }
    O1(const O1& other)
    {
        n = other.n;
        cout << n << " O1(const O1&)\n";
    }
    O1(O1&& other) noexcept
    {
        n = other.n;
        cout << n << " O1(O1&&)\n";
    }
private:
    static size_t n;
};
O1::n = 1;

class O2 {
public:
    O2(size_t n) { cout << n << " O2()\n"; }
    O2(const O2&)
    {
        cout << " O2(const O2&)\n";
    }
    O2(O2&&)
    {
        cout << " O2(O2&&)\n";
    }
};

int main() 
{
    vector<O1> v1;
    v1.reserve(2);
    cout << v1.capacity() << endl;
    // v1.emplace_back();
    // v1.emplace_back();
    // v1.emplace_back();
    O1 o1();
    O1 o2();
    v1.push_back(o1);
    v1.push_back(o2);
    return 0;
}