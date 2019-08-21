#include <iostream>
#include <string>

using namespace std;

//7.4
struct Person{
    string name = "My name is not defined.";
    string address = "My address is not defined.";

    string getName() const {return name;}
    string getAdd() const {return address;}
};

//7.5

int main()
{
    Person p;
    cout << p.getAdd() << endl;
}