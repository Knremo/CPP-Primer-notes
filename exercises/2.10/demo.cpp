#include <iostream>

// 2.9
std::string global_str; //空string
int global_int; //0
int main()
{
    //std::cin >> int input_value;  //xxxxx
    //int i = { 3.14 };   //xxxxx
    //double salary = wage = 9999.99;  //xxxx
    int i = 3.14;
    int local_int; //undefined
    std::string local_str; //空
    std::cout << global_int << std::endl;
}