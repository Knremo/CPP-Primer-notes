#include <iostream>
#include <string>

using namespace std;

//7.9
struct Person{
    string name = "My name is not defined.";
    string address = "My address is not defined.";

    string getName() const {return name;}
    string getAdd() const {return address;}
};

istream &read(istream &is, Person &p)
{
    is >> p.name >> p.address;
    return is;
}

ostream &print(ostream &os, const Person &p)
{
    os << p.name << " " << p.address << endl;
    return os;
}

int main()
{
    Person p1, p2;
    read(read(cin, p1), p2);
    print(print(cout, p1), p2);

    return 0;
}