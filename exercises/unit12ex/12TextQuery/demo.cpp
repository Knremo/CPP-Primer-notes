#include "class/class.h"

int main()
{
    ifstream file("../file.txt");
    TextQuery tq(file);
    cout << "Start Successfully." << endl;
    while (true)
    {
        cout << "word to query:";
        string s;
        if (!(cin >> s) || s == "q")
            break;
        print(cout, tq.query(s)) << endl;
    }

    return 0;
}