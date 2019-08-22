#include <iostream>
#include <string>

using namespace std;

//istream &read(istream &is, Person &p);

//7.15
struct Person{
    string name = "Undefined";
    string address = "Undefined";

    //构造函数
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

int main()
{
    Person p1, p2("Bob", "America"), p3("Lihua"), p4(cin);
    
    print(cout, p1);
    print(cout, p2);
    print(cout, p3);
    print(cout, p4);
    return 0;
}