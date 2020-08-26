# Python
Python 本身就有 C 接口，可以用 C 语言编写扩展模块，把一些低效耗时的功能改用 C 实现，有的时候，会把整体性能提升几倍甚至几十倍

## pybind11
在 C++ 和 Python 之间自由转换，任意翻译两者的语言要素，比如把 C++ 的 vector 转换为 Python 的列表，把 Python 的元组转换为 C++ 的 tuple，既可以在 C++ 里调用 Python 脚本，也可以在 Python 里调用 C++ 的函数、类

只要用一个宏“PYBIND11_MODULE”，再给它两个参数，Python 模块名和 C++ 实例对象名，就可以了
```cpp
#include <pybind11/pybind11.h>

PYBIND11_MODULE(pydemo, m) // 定义Python模块pydemo
{
    // 模块的说明文档
    m.doc() = "pybind11 demo doc";
}
```
可以用 g++ 把它编译成在 Python 里调用的模块了，不过编译命令比较复杂：
```bash
g++ pybind.cpp\ #编译的源文件
    -std=c++11 -shared -fPIC\ #编译成动态库
    `python3 -m pybind11 --includes`\ #获得包含路径
    -o pydemo`python3-config --extension-suffix` #生成的动态库名字
```
第四行最关键，是生成的动态库名字，前面必须是**源码里的模块名**，而后面那部分则是 Python 要求的后缀名，否则 Python 运行时会找不到模块

导入：
```python
import pydemo
help(pydemo)
```

导入 C++ 函数：
```cpp
namespace py = pybind11;               // 名字空间别名，简化代码

PYBIND11_MODULE(pydemo, m)             // 定义Python模块pydemo
{
  m.def("info",                        // 定义Python函数
    []()                              // 定义一个lambda表达式
    {
      py::print("c++ version =", __cplusplus);  // pybind11自己的打印函数
      py::print("gcc version =", __VERSION__);
      py::print("libstdc++   =", __GLIBCXX__);
    }
  );  

  m.def("add",                       // 定义Python函数
    [](int a, int b)                 // 有参数的lambda表达式
    {
      return a + b;
    }
  );  
}                                     // Python模块定义结束

//python
import pydemo
pydemo.info()
x = pydemo.add(1,2)
```

pybind11 也支持函数的参数、返回值使用标准容器，会自动转换成 Python 里的 list、dict，不过你需要额外再包含一个“stl.h”的头文件
```cpp
#include <pybind11/stl.h>              // 转换标准容器必须的头文件

PYBIND11_MODULE(pydemo, m)             // 定义Python模块pydemo
{
  m.def("use_str",                     // 定义Python函数
    [](const string& str)              // 入参是string
    {
        py::print(str);
        return str + "!!";            // 返回string
    }
  );  

  m.def("use_tuple",                  // 定义Python函数
    [](tuple<int, int, string> x)     // 入参是tuple
    {
        get<0>(x)++;
        get<1>(x)++;
        get<2>(x)+= "??";
        return x;                     // 返回元组
    }
  );  

  m.def("use_list",                   // 定义Python函数
    [](const vector<int>& v)          // 入参是vector
    {
        auto vv = v;
        py::print("input :", vv);
        vv.push_back(100);
        return vv;                    // 返回列表       
    }
  );
}
```
C++ 里的类也能够等价地转换到 Python 里面调用，这要用到一个特别的模板类 class_
```cpp
class Point final
{
public:
    Point() = default;
    Point(int a)；
public:
    int get() const;
    void set(int a);
};

py::class_<Point>(m, "Point")           // 定义Python类
    .def(py::init())                    // 导出构造函数
    .def(py::init<int>())               // 导出构造函数
    .def("get", &Point::get)            // 导出成员函数
    .def("set", &Point::set)            // 导出成员函数
    ;
```
对于一般的成员函数来说，定义的方式和普通函数一样，只是你必须加上取地址操作符“&”，把它写成函数指针的形式。而构造函数则比较特殊，必须调用 init() 函数来表示，如果有参数，还需要在 init() 函数的模板参数列表里写清楚

# Lua
和 Python 一样，Lua 也有 C 接口用来编写扩展模块，但因为它比较小众，所以 C++ 项目不是很多。现在我用的是 LuaBridge，虽然它没有用到太多的 C++11 新特性，但也足够好

LuaJIT。它内置了一个 ffi 库（Foreign Function Interface），能够在 Lua 脚本里直接声明接口函数、直接调用，不需要任何的注册动作，更加简单方便。而且这种做法还越过了 Lua 传统的栈操作，速度也更快。

使用 ffi 唯一要注意的是，它只能识别纯 C 接口，不认识 C++，所以，写 Lua 扩展模块的时候，内部可以用 C++，但对外的接口必须转换成纯 C 函数
```cpp
extern "C" {                // 使用纯C语言的对外接口
int num = 10; 
int my_add(int a, int b); 
}

int my_add(int a, int b)    // 一个简单的函数，供Lua调用
{
    return a + b;
}
```
然后就可以用 g++ 把它编译成动态库
```bash
g++ lua_shared.cpp -std=c++11 -shared -fPIC -o liblua_shared.so
```
在 Lua 脚本里，你首先要用 ffi.cdef 声明要调用的接口，再用 ffi.load 加载动态库，这样就会把动态库所有的接口都引进 Lua，然后就能随便使用了：
```lua
local ffi = require "ffi"            -- 加载ffi库
local ffi_load = ffi.load            -- 函数别名
local ffi_cdef = ffi.cdef

ffi_cdef[[                           // 声明C接口
int num;
int my_add(int a, int b);
]]

local shared = ffi_load("./liblua_shared.so")    -- 加载动态库 

print(shared.num)                                -- 调用C接口
local x = shared.my_add(1, 2)                    -- 调用C接口
```

在 C++ 里嵌入 Lua，首先要调用函数 luaL_newstate()，创建出一个 Lua 虚拟机，所有的 Lua 功能都要在它上面执行

因为 Lua 是用 C 语言写的，Lua 虚拟机用完之后必须要用函数 lua_close() 关闭，所以最好用 RAII 技术写一个类来自动管理
```cpp
auto make_luavm = []()              // lambda表达式创建虚拟机
{
    std::shared_ptr<lua_State> vm(  // 智能指针
        luaL_newstate(), lua_close  // 创建虚拟机对象，设置删除函数
        );
    luaL_openlibs(vm.get());        // 打开Lua基本库

    return vm; 
};
#define L vm.get()                  // 获取原始指针，宏定义方便使用
```
只能用函数 getGlobal() 看到全局变量，所以，如果想在 C++ 里调用 Lua 功能，就一定不能加“local”修饰
```cpp
auto vm = make_luavm();                  // 创建Lua虚拟机
auto package = getGlobal(L, "package");  // 获取内置的package模块

string path  = package["path"];          // 默认的lua脚本搜索路径
string cpath = package["cpath"];         // 默认的动态库搜索路径
```
可以调用 luaL_dostring() 和 luaL_dofile() 这两个函数，直接执行 Lua 代码片段或者外部的脚本文件
```cpp
luaL_dostring(L, "print('hello lua')");  // 执行Lua代码片段
luaL_dofile(L, "./embedded.lua");        // 执行外部的脚本文件
```
另外一种方式：提前在脚本里写好一些函数，加载后在 C++ 里逐个调用
```cpp
string chunk = R"(                    -- Lua代码片段
    function say(s)                   -- Lua函数1
        print(s)
    end
    function add(a, b)                -- Lua函数2
        return a + b
    end
)";

luaL_dostring(L, chunk.c_str());      // 执行Lua代码片段

auto f1 = getGlobal(L, "say");        // 获得Lua函数
f1("say something");                  // 执行Lua函数

auto f2 = getGlobal(L, "add");        // 获得Lua函数
auto v = f2(10, 20);                  // 执行Lua函数
```