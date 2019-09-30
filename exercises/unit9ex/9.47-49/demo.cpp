#include <string>
#include <iostream>
#include <fstream>

using namespace std;

//9.47
void findnum1(const string &s)
{
    string nums = "0123456789";
    string::size_type pos = 0;
    while ((pos = s.find_first_of(nums, pos)) != string::npos)
    {
        cout << "find number at index: " << pos << " with value: " << s[pos] << endl;
        ++pos;
    }
}

void findnum2(const string &s)
{
    string nums = "qwertyuiopasdfghjklzxcvbnm ";
    string::size_type pos = 0;
    while ((pos = s.find_first_not_of(nums, pos)) != string::npos)
    {
        cout << "find number at index: " << pos << " with value: " << s[pos] << endl;
        ++pos;
    }
}

//9.49
void printvolcabulary(const string &file)
{
    ifstream in(file);
    string temp;
    string upchar = "tidfhjklb", downchar = "ypqgj";

    while (in >> temp)
    {
        auto pos = temp.find_first_of(upchar+downchar);
        if(pos == string::npos)
            cout << temp << endl;
    }

    in.close();
}

int main()
{
    findnum2("s1d34fs4rr84");

    //9.48
    string numbers = "0123456789", name = "r2d2";
    cout << numbers.find(name) << endl;

    printvolcabulary("vocabulary.txt");
    return 0;
}