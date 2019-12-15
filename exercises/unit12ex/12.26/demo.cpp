#include <memory>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    allocator<string> alloc;
    auto const p = alloc.allocate(10);
    string ss;
    auto q = p;
    while (cin >> ss && q != p + 10)
        alloc.construct(q++, ss);

    while (q != p)
        alloc.destroy(--q);

    alloc.deallocate(p, 10);

    return 0;
}