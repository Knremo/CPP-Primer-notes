#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
using namespace std;

void f1()
{
    unordered_map<string, size_t> word_count;
    set<string> exclude = {"The", "But"};
    string word;
    while (cin >> word)
        if (exclude.find(word) == exclude.end())
            ++word_count[word];

    for (auto e:word_count)
        cout << e.first << " " << e.second << endl;
}

unordered_map<string, string> buildMap(ifstream &map_file)
{
    unordered_map<string, string> trans_map;
    string key;
    string value;
    while (map_file >> key && getline(map_file, value))
        if (value.size() > 1)
            trans_map[key] = value.substr(1); // 去除前面的空格
        else
            throw runtime_error("no rule for " + key);
    return trans_map;
}

const string& transform(const string &s, const unordered_map<string, string> &m)
{
    auto map_it = m.find(s);
    if (map_it != m.cend())
        return map_it->second;
    else
        return s;
}

void word_transform(ifstream &map_file, ifstream &input)
{
    auto trans_map = buildMap(map_file);
    string text;
    while (getline(input, text))
    {
        istringstream stream(text);
        string word;
        bool firstword = true;
        while (stream >> word)
        {
            if (firstword)
                firstword = false;
            else
                cout << " ";
            cout << transform(word, trans_map);
        }
        cout << endl;
    }
}

int main()
{
    //f1();

    ifstream words_map("words_map.txt");
    ifstream words_data("words_data.txt");
    word_transform(words_map, words_data);

    return 0;
}