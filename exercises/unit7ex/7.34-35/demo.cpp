//7.34

#include <string>
using namespace std;

//7/35
typedef string Type;
Type initVal();
class Exercise
{
public:
    typedef double Type;
    Type setVal(Type);
    Type initVal();
private:
    int val;
};
//外层Type
//Type Exercise::setVal(Type parm)
Exercise::Type Exercise::setVal(Type parm)
{
    val = parm + initVal();
    return val;
}