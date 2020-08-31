# 1. JSON
JSON for Modern C++
```bash
git clone git@github.com:nlohmann/json.git    # git clone
wget https://github.com/nlohmann/json/releases/download/v3.7.3/json.hpp  # wget 
```

```cpp
using json_t = nlohmann::json;

json_t j;                                   // JSON对象

j["age"] = 23;                              // "age":23
j["name"] = "spiderman";                    // "name":"spiderman"
j["gear"]["suits"] = "2099";                // "gear":{"suits":"2099"}
j["jobs"] = {"superhero"};                  // "jobs":["superhero"]  

vector<int> v = {1,2,3};                   // vector容器
j["numbers"] = v;                          // "numbers":[1,2,3]

map<string, int> m =                       // map容器
    {{"one",1}, {"two", 2}};               // 初始化列表 
j["kv"] = m;                               // "kv":{"one":1,"two":2}
```
用成员函数 dump() 就可以序列化，得到它的 JSON 文本形式
```cpp
cout << j.dump() << endl;         // 序列化，无缩进
cout << j.dump(2) << endl;        // 序列化，有缩进，2个空格
```
反序列化功能只要调用静态成员函数 parse() 
```cpp
string str = R"({                // JSON文本，原始字符串
    "name": "peter",
    "age" : 23,
    "married" : true
})";

auto j = json_t::parse(str);    // 从字符串反序列化
assert(j["age"] == 23);        // 验证序列化是否正确
assert(j["name"] == "peter");
```
使用异常来处理解析时可能发生的错误，如果你不能保证 JSON 数据的完整性，就要使用 try-catch 来保护代码:
```cpp
auto txt = "bad:data"s;        // 不是正确的JSON数据

try                             // try保护代码
{
    auto j = json_t::parse(txt);// 从字符串反序列化
}
catch(std::exception& e)        // 捕获异常
{
    cout << e.what() << endl;
}
```

# 2. MessagePack
二进制

msgpack-c

调用 pack() 函数序列化为 MessagePack 格式：
```cpp
vector<int> v = {1,2,3,4,5};              // vector容器

msgpack::sbuffer sbuf;                    // 输出缓冲区
msgpack::pack(sbuf, v);                   // 序列化
```
必须同时传递序列化的输出目标和被序列化的对象

输出目标 sbuffer 是个简单的缓冲区，和vector<char>很像，也可以用 `data()` 和 `size()` 方法获取内部的数据和长度

可以选择另外的 zbuffer、fbuffer, 它们是压缩输出和文件输出

MessagePack **反序列化**，要用到函数 unpack() 和两个核心类：object_handle 和 object

函数 unpack() 反序列化数据，得到的是一个 object_handle，再调用 get()，就是 object

这个 object 是 MessagePack 对数据的封装，不能直接使用，必须知道数据的原始类型，才能转换还原
```cpp
auto handle = msgpack::unpack(          // 反序列化
            sbuf.data(), sbuf.size());  // 输入二进制数据
auto obj = handle.get();                // 得到反序列化对象

vector<int> v2;                       // vector容器
obj.convert(v2);                      // 转换反序列化的数据

assert(std::equal(                    // 算法比较两个容器
      begin(v), end(v), begin(v2)));
```

## packer
提供了一个 packer 类，可以实现串联的序列化操作
```cpp
msgpack::sbuffer sbuf;                         // 输出缓冲区
msgpack::packer<decltype(sbuf)> packer(sbuf);  // 专门的序列化对象

packer.pack(10).pack("monado"s)                // 连续序列化多个数据
      .pack(vector<int>{1,2,3});
      
for(decltype(sbuf.size()) offset = 0;          // 初始偏移量是0
    offset != sbuf.size();){                   // 直至反序列化结束

    auto handle = msgpack::unpack(            // 反序列化
            sbuf.data(), sbuf.size(), offset);  // 输入二进制数据和偏移量
    auto obj = handle.get();                  // 得到反序列化对象
}
```
## MSGPACK_DEFINE
把它放进你的类定义里，就可以像标准类型一样被 MessagePack 处理
```cpp
class Book final                       // 自定义类
{
public:
    int         id;
    string      title;
    set<string> tags;
public:
    MSGPACK_DEFINE(id, title, tags);   // 实现序列化功能的宏
};  

Book book1 = {1, "1984", {"a","b"}};  // 自定义类

msgpack::sbuffer sbuf;                    // 输出缓冲区
msgpack::pack(sbuf, book1);              // 序列化

auto obj = msgpack::unpack(              // 反序列化
      sbuf.data(), sbuf.size()).get();   // 得到反序列化对象

Book book2;
obj.convert(book2);                      // 转换反序列化的数据

assert(book2.id == book1.id);
assert(book2.tags.size() == 2);
cout << book2.title << endl;
```

捕获异常：
```cpp
auto txt = ""s;                      // 空数据
try                                  // try保护代码
{
    auto handle = msgpack::unpack(   // 反序列化
        txt.data(), txt.size());
}
catch(std::exception& e)            // 捕获异常
{
    cout << e.what() << endl;
}
```

# 3. ProtoBuffer
```bash
apt-get install protobuf-compiler
apt-get install libprotobuf-dev

g++ protobuf.cpp -std=c++14 -lprotobuf -o a.out
```
PB 的另一个特点是数据有“**模式**”（schema），必须要先写一个 IDL（Interface Description Language）文件，在里面定义好数据结构，只有预先定义了的数据结构，才能被序列化和反序列化
```
syntax = "proto2";                    // 使用第2版

package sample;                        // 定义名字空间

message Vendor                        // 定义消息
{
    required uint32     id      = 1;  // required表示必须字段
    required string     name    = 2;  // 有int32/string等基本类型
    required bool       valid   = 3;  // 需要指定字段的序号，序列化时用
    optional string     tel     = 4;  // optional字段可以没有
}
```
再用 protoc 工具生成对应的 C++ 源码，然后把源码文件加入自己的项目中，就可以使用了：
```
protoc --cpp_out=. sample.proto       // 生成C++代码
```

PB 的用法：
```cpp
using vendor_t = sample::Vendor;        // 类型别名

vendor_t v;                             // 声明一个PB对象
assert(!v.IsInitialized());            // required等字段未初始化

v.set_id(1);                            // 设置每个字段的值    
v.set_name("sony");
v.set_valid(true);

assert(v.IsInitialized());             // required等字段都设置了，数据完整
assert(v.has_id() && v.id() == 1); 
assert(v.has_name() && v.name() == "sony");
assert(v.has_valid() && v.valid());

cout << v.DebugString() << endl;       // 输出调试字符串

string enc;
v.SerializeToString(&enc);              // 序列化到字符串 

vendor_t v2; 
assert(!v2.IsInitialized());
v2.ParseFromString(enc);               // 反序列化
```