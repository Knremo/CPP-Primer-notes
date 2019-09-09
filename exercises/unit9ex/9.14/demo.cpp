#include <list>
#include <vector>
#include <string>

using namespace std;

int main()
{
    char c[] = "Save me!";
    list<char*> lst = {c};

    vector<string> vs;
    vs.assign(lst.begin(), lst.end());

    return 0;
}