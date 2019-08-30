#include <string>
#include <iostream>
#include <vector>

class Account
{
public:
    void calculate() { amount += amount * interestRate; }
    static double rate() { return interestRate; }
    static void rate(double);
private:
    std::string owner;
    double amount;
    static double interestRate;
    static constexpr double initRate() { return 1.0; }
    static constexpr int period = 30;
    double daily_tbl[period];
};

void Account::rate(double newRate)
{
    interestRate = newRate;
}

double Account::interestRate = initRate();


int main()
{
    Account a,b;
    std::cout << a.rate() << std::endl;
    Account::rate(2.3);
    std::cout << a.rate() << std::endl;
}