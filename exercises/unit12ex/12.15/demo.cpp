#include <memory>
#include <iostream>

using namespace std;

struct destination; // 正在连接什么
struct connection
{
    
};  // 使用连接所需的信息
connection connect(destination*); // 打开连接
void disconnect(connection); // 关闭给定的连接

void f(destination &d)
{
    connection c = connect(&d);
    shared_ptr<connection> p(&c, [](connection *p){disconnect(*p);});
    //当f退出时，connection会被正确关闭
}