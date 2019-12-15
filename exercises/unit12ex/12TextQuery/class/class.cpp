#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

class QueryResult;
string ModifyWord(const string &);

class TextQuery
{
public:
    using line_no = vector<string>::size_type;
    TextQuery(ifstream&);
    QueryResult query(const string&) const;
private:
    shared_ptr<vector<string>> file;
    map<string, shared_ptr<set<line_no>>> wm;
};

class QueryResult
{
    friend ostream& print(ostream&, const QueryResult&);
public:
    using line_no = vector<string>::size_type;
    QueryResult(string s,
                shared_ptr<set<line_no>> p,
                shared_ptr<vector<string>> f):
        sought(s), lines(p), file(f) { }
private:
    string sought;
    shared_ptr<set<line_no>> lines;
    shared_ptr<vector<string>> file;
};

string modifyWord(string &word)
{
    auto &e = word.back();
    if (ispunct(e))
        word.erase(word.end() - 1);
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    return word;
}

TextQuery::TextQuery(ifstream &is): file(new vector<string>)
{
    string text;
    cout << "t1" << endl;
    while (getline(is, text))
    {
        cout << text << endl;
        file->push_back(text); //每一行存入vector
        int n = file->size() - 1; //行号减一当作下标
        istringstream line(text);
        string word;
        while (line >> word) //把word存入map
        {
            word = modifyWord(word); //大小写转换去除标点
            auto &lines = wm[word]; //指向set
            if (!lines) //第一次遇到这个单词时这个指针为空
                lines.reset(new set<line_no>); //分配一个新的set
            lines->insert(n); //插入一个行号
        }
    }
}

QueryResult TextQuery::query(const string &sought) const
{
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

string make_plural(size_t s, const string word, const string p)
{
    if (s > 1)
        return word + p;
    return word; 
}

ostream &print(ostream &os, const QueryResult &qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " "
       << make_plural(qr.lines->size(), "time", "s") << endl;
    
    for (auto num : *qr.lines)
        os << "\t(line " << num + 1 << ") "
           << *(qr.file->begin() + num) << endl;
    return os;
}

