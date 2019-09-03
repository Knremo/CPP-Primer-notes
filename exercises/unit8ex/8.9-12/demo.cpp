#include <iostream>
using namespace std;
#include <sstream>
#include <fstream>
#include <vector>

//8.9
istream &readfromstream(istream &is)
{
    string s;
    while (!is.eof())
    {
        is >> s;
        cout << s;
    }
    is.clear();
    return is;
}

//8.10
void readfromfile(const string &file)
{
    ifstream infile(file);
    if(infile)
    {
        vector<string> vs;
        string s;
        while (getline(infile, s))
            vs.push_back(s);
        infile.close();

        for (auto i : vs)
        {
            istringstream is(i);
            string temp;
            while (is >> temp)
                cout << temp << endl;
        }
    }
}

//8.11
struct PersonInfo
{
    string name;
    vector<string> phones;
};

vector<PersonInfo> f3()
{
    string line, word;
    vector<PersonInfo> people;

    ifstream in("info.txt");
    if (in)
    {
        istringstream record;

        while (getline(in, line))
        {
            cout << line << endl;
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

int main()
{
    // string s = "This is what I said.";
    // istringstream ss(s);
    // readfromstream(ss);

    // readfromfile("file.txt");

    vector<PersonInfo> p = f3();
    cout << p.size() << endl;

    for (auto i : p)
    {    
        cout << i.name << " ";
        for (auto &j : i.phones)
            cout << j << " ";
        cout<< endl;
    }

    return 0;
}