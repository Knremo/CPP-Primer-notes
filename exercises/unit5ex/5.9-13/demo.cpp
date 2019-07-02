#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

//5.9
void f1()
{
    unsigned aCnt = 0;
    char ch;
    while (cin >> ch)
    {
        if (ch == 'a')
        {
            aCnt++;
            continue;
        }
    }
}

//5.10
void f2()
{
    unsigned aCnt = 0;
    char ch;
    while (cin >> ch)
    {
        switch (tolower(ch))
        {
        case 'a':
            aCnt++;
            break;
        
        default:
            break;
        }
    }
}

//5.11

//5.12

//5.13
char next_next()
{
    return 'c';
}
int get_value()
{
    return 1;
}

void f3()
{
    unsigned aCnt = 0, eCnt = 0, iouCnt = 0;
    char ch = next_next();
    switch (ch)
    {
        case 'a': aCnt++;break;
        case 'e': eCnt++;break;
        default: iouCnt++;break;
    }

    int ix = 0;
    vector<int> ivec;
    unsigned index = get_value();
    switch (ch)
    {
    case 1:
        ix = get_value();
        ivec[ix] = index;
        break;
    default:
        ix = ivec.size() - 1;
        ivec[ix] = index;
        break;
    }

    unsigned evenCnt = 0, oddCnt = 0;
    int digit = get_value() % 10;
    switch (digit)
    {
    case 1:case 3:case 5:case 7:case 9:
        oddCnt++;
        break;

    case 2:case 4:case 6:case 8:case 10:
        evenCnt++;
        break;
    default:
        break;
    }

    const unsigned ival = 512, jval = 1024, kval = 4096;
    unsigned bufsize;
    unsigned swt = get_value();
    switch (swt)
    {
    case ival:
        bufsize = ival * sizeof(int);
        break;
    
    default:
        break;
    
}