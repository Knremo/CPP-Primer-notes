# 1. 预处理编程
顶格写

单独的一个“#”也是一个预处理指令，叫“空指令”，可以当作特别的预处理空行。而“#”与后面的指令之间也可以有空格，从而实现缩进，方便排版

可以让 GCC 使用“-E”选项，略过后面的编译链接，只输出预处理后的源码
```bash
g++ test03.cpp -E -o a.cxx    #输出预处理后的源码
```

# 2. 包含头文件
为了防止代码被重复包含，通常要加上“Include Guard”，也就是用 “#ifndef/#define/#endif” 来保护整个头文件，像下面这样：
```c++
#ifndef _XXX_H_INCLUDED_
#define _XXX_H_INCLUDED_

...    // 头文件内容

#endif // _XXX_H_INCLUDED_
```

编写一些代码片段，存进“*.inc”文件里，然后有选择地加载
```c++
// calc_values.inc
static uint32_t  calc_table[] = {  // 非常大的一个数组，有几十行
    0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
    0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
    0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
    0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
    ...                          
};

static uint32_t  calc_table[] = {
#  include "calc_values.inc"        // 非常大的一个数组，细节被隐藏
};
```

# 3. 宏定义
对于一些调用频繁的小代码片段来说，用宏来封装的效果比 inline 关键字要更好
```c++
#define ngx_tolower(c)      ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
#define ngx_toupper(c)      ((c >= 'a' && c <= 'z') ? (c & ~0x20) : c)

#define ngx_memzero(buf, n)       (void) memset(buf, 0, n)
```

宏是没有作用域概念的，永远是全局生效。所以，对于一些用来简化代码、起临时作用的宏，最好是用完后尽快用“#undef”取消定义
```c++
#define CUBE(a) (a) * (a) * (a)  // 定义一个简单的求立方的宏

cout << CUBE(10) << endl;        // 使用宏简化代码
cout << CUBE(15) << endl;        // 使用宏简化代码

#undef CUBE                      // 使用完毕后立即取消定义
```

# 4. 条件编译
条件编译有两个要点，一个是条件指令“#if”，另一个是后面的“判断依据”

通常编译环境都会有一些预定义宏，比如 CPU 支持的特殊指令集、操作系统 / 编译器 / 程序库的版本、语言特性等，使用它们就可以早于运行阶段，提前在预处理阶段做出各种优化，产生出最适合当前系统的源码

`__cplusplus`: 它标记了 C++ 语言的版本号
```c++
#ifdef __cplusplus                      // 定义了这个宏就是在用C++编译
    extern "C" {                        // 函数按照C的方式去处理
#endif
    void a_c_function(int a);
#ifdef __cplusplus                      // 检查是否是C++编译
    }                                   // extern "C" 结束
#endif

#if __cplusplus >= 201402                // 检查C++标准的版本号
    cout << "c++14 or later" << endl;    // 201402就是C++14
#elif __cplusplus >= 201103              // 检查C++标准的版本号
    cout << "c++11 or before" << endl;   // 201103是C++11
#else   // __cplusplus < 201103          // 199711是C++98
#   error "c++ is too old"               // 太低则预处理报错
#endif  // __cplusplus >= 201402         // 预处理语句结束
```

源文件信息的 `FILE` `LINE` `DATE`

以及一些语言特性测试宏，比如 `__cpp_decltype` `__cpp_decltype_auto` `__cpp_lib_make_unique` 等

GCC 可以使用一条简单的命令查看：
```bash
g++ -E -dM - < /dev/null

#define __GNUC__ 5
#define __unix__ 1
#define __x86_64__ 1
#define __UINT64_MAX__ 0xffffffffffffffffUL
...
```
基于它们，你就可以更精细地根据具体的语言、编译器、系统特性来改变源码，有，就用新特性:
```c++
#if defined(__cpp_decltype_auto)        //检查是否支持decltype(auto)
    cout << "decltype(auto) enable" << endl;
#else
    cout << "decltype(auto) disable" << endl;
#endif  //__cpp_decltype_auto

#if __GNUC__ <= 4
    cout << "gcc is too old" << endl;
#else   // __GNUC__ > 4
    cout << "gcc is good enough" << endl;
#endif  // __GNUC__ <= 4

#if defined(__SSE4_2__) && defined(__x86_64)
    cout << "we can do more optimization" << endl;
#endif  // defined(__SSE4_2__) && defined(__x86_64)
```

显式启用或者禁用大段代码:
```c++
#if 0          // 0即禁用下面的代码，1则是启用
  ...          // 任意的代码
#endif         // 预处理结束

#if 1          // 1启用代码，用来强调下面代码的必要性
  ...          // 任意的代码
#endif         // 预处理结束
```