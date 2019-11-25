#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

void elimDups(list<string> &words)
{
    words.sort();
    words.unique();
}

int main()
{
    list<string> words = {"I", "just", "want", "to", "play", "alone", "ok", "I", "play"};
    elimDups(words);
    for (auto e:words)
        cout << e << endl;

    return 0;
}