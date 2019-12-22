#include <iostream>
#include <string>

using namespace std;

//13.18
class Employee
{
public:
    Employee(const string &);
    Employee(const Employee&) = delete;
    Employee& operator=(const Employee&) = delete;
    ~Employee() = default;
private:
    static size_t count;
    string name;
    size_t sn;
};
size_t Employee::count = 0;
Employee::Employee(const string &n):
    name(n)
{
    sn = count;
    ++count;
}
//13.19
// delete

//13.20
//shared_ptr的引用计数为0时才会销毁

//13.21
//不需要吧，shared_ptr指向同一个内存也没关系
/*
class TextQuery
{
public:
    using line_no = vector<string>::size_type;
    TextQuery(ifstream&);
    QueryResult query(const string&) const;
private:
    shared_ptr<StrBlob> file;
    map<string, shared_ptr<set<line_no>>> wm;
};

class QueryResult
{
    friend ostream& print(ostream&, const QueryResult&);
public:
    using line_no = vector<string>::size_type;
    QueryResult(string s,
                shared_ptr<set<line_no>> p,
                shared_ptr<StrBlob> f):
        sought(s), lines(p), file(f) { }
    set<line_no>::iterator begin() { return lines->begin(); }
    set<line_no>::iterator end() { return lines->end(); }
    shared_ptr<shared_ptr<StrBlob>> get_file();
private:
    string sought;
    shared_ptr<set<line_no>> lines;
    shared_ptr<StrBlob> file;

};
*/
