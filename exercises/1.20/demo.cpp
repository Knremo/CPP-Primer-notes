#include "Sales_item.h"

int main()
{
    Sales_item val;
    while(std::cin >> val)
    {
        std::cout << val << std::endl;
    }
    return 0;
}
//PowerShell command:
//Get-Content .\book_sales|.\demo.exe