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

