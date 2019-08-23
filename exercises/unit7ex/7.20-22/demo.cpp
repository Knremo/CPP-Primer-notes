#include <iostream>
#include <string>

using namespace std;

//7.22
class Person{
private:
    string name = "Undefined";
    string address = "Undefined";

public:
    //构造函数
    friend istream &read(istream &is, Person &p);
    friend ostream &print(ostream &os, const Person &p);
    Person() = default;
    Person(const string &name, const string &address): name(name), address(address) {}
    Person(const string &name): name(name) {}
    Person(istream &);

    string getName() const {return name;}
    string getAdd() const {return address;}
};

istream &read(istream &is, Person &p)
{
    is >> p.name >> p.address;
    return is;
}

Person::Person(istream &is)
{
    read(is, *this);
}

ostream &print(ostream &os, const Person &p)
{
    os << p.name << " " << p.address << endl;
    return os;
}