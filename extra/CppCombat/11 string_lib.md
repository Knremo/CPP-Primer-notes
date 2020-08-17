# 1. string
```cpp
using string = std::basic_string<char>;  // string其实是一个类型别名
using wstring = std::basic_string<wchar_t>;
using u16string = std::basic_string<char16_t>;
using u32string = std::basic_string<char32_t>;
```

string 是一个功能比较全的字符串类：
```cpp
string str = "abc";

assert(str.length() == 3); 
assert(str < "xyz");
assert(str.substr(0, 1) == "a");
assert(str[1] == 'b');
assert(str.find("1") == string::npos);
assert(str + "d" == "abcd");
```

还有 `size(), begin(), end(), push_back()...`

## 1.1 字面量后缀
```cpp
using namespace std::literals::string_literals;  //必须打开名字空间
auto str = "std string"s;      // 后缀s，表示是标准字符串，直接类型推导
assert("time"s.size() == 4);   // 标准字符串可以直接调用成员函数
```

## 1.2 原始字符串
C++11
```cpp
auto str = R"(nier:automata)"; // 原始字符串： nier:automata
```
```cpp
auto str1 = R"(char""'')";    // 原样输出：char""''
auto str2 = R"(\r\n\t\")";    // 原样输出：\r\n\t\"
auto str3 = R"(\\\$)";        // 原样输出：\\\$
auto str4 = "\\\\\\$";         // 转义后输出：\\\$
```
想要在原始字符串里面写引号+圆括号，在圆括号的两边加上最多16个字符的“界定符”
```cpp
auto str5 = R"==(R"(xxx)")==" // R"(xxx)"
```

## 1.3 字符串转换函数
stoi(), stol(), stoll()

stof(), stod()

to_string()

## 1.4 string_view
内部只保存一个指针和长度，C++17

```cpp
class my_string_view final        // 简单的字符串视图类，示范实现
{
public:
    using this_type = my_string_view;     // 各种内部类型定义
    using string_type = std::string;
    using string_ref_type = const std::string&;

    using char_ptr_type = const char*;
    using size_type = size_t;
private:
    char_ptr_type ptr = nullptr;     // 字符串指针
    size_type len = 0;               // 字符串长度
public:
    my_string_view() = default;
   ~my_string_view() = default;

    my_string_view(string_ref_type str) noexcept
        : ptr(str.data()), len(str.length())
    {}
public:
    char_ptr_type data() const     // 常函数，返回字符串指针
    {
        return ptr;
    }

    size_type size() const        // 常函数，返回字符串长度
    {
        return len;
    }
};
```

# 2. 正则表达式
C++11 regex

C++ 正则表达式主要有两个类。
* regex：表示一个正则表达式，是 basic_regex 的特化形式；
* smatch：表示正则表达式的匹配结果，是 match_results 的特化形式。

C++ 正则匹配有三个算法，注意它们都是“只读”的，不会变动原字符串。
* regex_match()：完全匹配一个字符串；
* regex_search()：在字符串里查找一个正则匹配；
* regex_replace()：正则查找再做替换。

```cpp
auto make_regex = [](const auto& txt)    // 生产正则表达式
{
    return std::regex(txt);
};

auto make_match = []()                  // 生产正则匹配结果
{
    return std::smatch();
};

auto str = "neir:automata"s;          // 待匹配的字符串
auto reg = make_regex(R"(^(\w+)\:(\w+)$)");  // 原始字符串定义正则表达式
auto what = make_match();             // 准备获取匹配的结果

// 匹配,函数会返回 bool 值表示是否完全匹配正则。
// 如果匹配成功，结果存储在 what 里，可以像容器那样去访问，第 0 号元素是整个匹配串，其他的是子表达式匹配串
assert(regex_match(str, what, reg));  // 正则匹配

for(const auto& x : what) {          // for遍历匹配的子表达式
    cout << x << ',';
}

auto str = "god of war"s;             // 待匹配的字符串

auto reg  = make_regex(R"((\w+)\s(\w+))");    // 原始字符串定义正则表达式
auto what = make_match();          // 准备获取匹配的结果

auto found = regex_search(          // 正则查找，和匹配类似
                str, what, reg);

assert(found);                        // 断言找到匹配
assert(!what.empty());                // 断言有匹配结果
assert(what[1] == "god");              // 看第一个子表达式
assert(what[2] == "of");              // 看第二个子表达式

auto new_str = regex_replace(      // 正则替换，返回新字符串
    str,                           // 原字符串不改动
    make_regex(R"(\w+$)"),         // 就地生成正则表达式对象
    "peace"                        // 需要指定替换的文字
);

cout << new_str << endl;          // 输出god of peace
```

# 3. 其他
1. c++20 新增了 char8_t,专门表示UTF-8,相应也有 u8string, u8"str"
2. `c_str()` 和 `data()` 都返回 `const char*` 指针，但 `c_str()` 会在末尾添加 '\0'
3. Boost 里有一个工具 lexical_cast,可以在字符串和数字之间转换
4. 第三方正则表达式库，PCRE，Hyperscan，libsregex
   
