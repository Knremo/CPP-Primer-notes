#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

struct PersonInfo
{
    string name;
    vector<string> phones;
};

vector<PersonInfo> read2vec(const string &file)
{
    string line, word;
    vector<PersonInfo> people;

    ifstream in(file);
    if (in)
    {
        istringstream record;

        while (getline(in, line))
        {
            //cout << line << endl;
            record.str(line);
            //cout << record.eof();
            PersonInfo info;
            record >> info.name;
            while (record >> word)
                info.phones.push_back(word);
            people.push_back(info);
            record.clear();
        }
        return people;
    }
    return people;
}

bool valid(const string &phone)
{
    string::size_type size = phone.size();
    //cout << size << endl;
    if (size != 7 && size != 4)
    {        
        //cout << 3 << endl;
        return false;
    }
    else
    {
        if (size == 7 && phone[0] == '1')
            return true;
        if (size == 4 && phone[0] == '5')
            return true;
        return false;
    }
}

string format(const string &phone)
{
    return phone;
}

void printinfo(const vector<PersonInfo> &vp)
{
    for (const auto &e : vp)
    {
        ostringstream formatted, badNums;
        for (const auto &nums : e.phones)
        {
            if (!valid(nums))
                badNums << " " << nums;
            else
                formatted << " " << format(nums);
        }
        if (badNums.str().empty())
            cout << e.name << " " << formatted.str() << endl;
        else
            cerr << "input error: " << e.name << " invalid number(s) " << badNums.str() << endl;
    }
}

int main()
{
    printinfo(read2vec("info.txt"));

    cout << valid("12");
    return 0;
}