# 17.1 tuple 类型
C++11

```c++
#include <tuple>

tuple<T1, T2, ..., Tn> t;
tuple<T1, T2, ..., Tn> t(v1, v2, ..., vn);
make_tuple(v1, v2, ..., vn);

t1 == t2
t1 != t2

t1 < t2

get<i>(t) // 返回t的第i个数据成员的引用，如果t是一个左值，结果是左值引用，否则是右值引用

tuple_size<tupleType>::value // 类模板，成员的数量

tuple_element<i, tupleType>::type // 指定成员的类型
```
## 17.1.1 定义和初始化tuple

## 17.1.2 使用tuple返回多个值

# 17.2 bitset 类型
## 17.2.1 定义和初始化
```c++
bitset<n> b; // b有n位，每一位为0.
bitset<n> b(u); // b 是 unsigned long long 值的低 n 位的拷贝

bitset<n> b(s, pos, m, zero, one); // b是string s从pos开始m个字符的拷贝，s只能包含字符zero或one。如果s包含任何其他字符，构造函数会抛出invalid_argument异常。字符在b中分别保存为zero和one。pos默认为0，m默认为string::npos,zero默认'0',one默认'1'

bitset<n> b(cp, pos, m, zero, one); //cp指向的字符数组中拷贝字符，如未提供m，则cp必须只想一个c风格字符串；如果提供m，则从cp开始必须至少有m个zero或one字符

// unsigned init
bitset<13> bitvec1(0xbeef); // 1111011101111 高位被丢弃
bitset<128> bitvec3(~0ULL);

// string init
bitset<32> bitvec4("1101") // 000..01101

string str("11111110101011111011");
bitset<32> bitvec5(str, 5, 4);
bitset<32> bitvec6(str, str.size()-4); //最后4个字符
```(
# 17.2.2 bitset 操作
```c++
b.any() // b中是否存在置位的二进制位
b.all() // b中所有位都置位
b.none() // b中不存在置位的二进制位
b.count() // b中置位的位数
b.size()
b.test(pos) // pos置位返回true
b.set(pos,v) // v默认true
b.set() // 所有位置位
b.reset(pos)
b.reset()
b.flip(pos)
b.flip()
b[pos]
b.to_ulong()
b.to_ullong()
b.to_string(zero,one)
os << b
is >> b
```
使用 biset
```c++
bool status;
unsigned long quizA = 0;
quizA |= 1UL << 27; // 第27个学生通过
status = qiuzA & (1UL << 27); // 检验27是否通过
quizA &= ~(1UL << 27); // 27未通过
//bitset
bitset<30> quizB;
quizB.set(27);
status = quizB[27];
quizB.reset(27);
```

# 17.3 正则表达式
```c++
regex
regex_match // 将一个字符序列与一个正则表达式匹配,整个匹配返回true
regex_search // 寻找第一个与正则表达式匹配的子序列
regex_replace // 使用给定格式替换一个正则表达式
regex_iterator // 调用regex_search来遍历一个string中所有匹配的子串
smatch // 容器类，保存在string中搜索的结果
ssub_match // string中匹配的子表达式的结果

//regex_search,regex_match 的参数
(seq, m, r, mft) // m是smatch对象保存匹配结果，mft可选
```
## 17.3.1 使用
```c++
// 查找不在字符c之后的字符串ei
string pattern("[^c]ei"); // 不是c的字符后面接ei
// 前后匹配零个或多个字母
pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
regex r(pattern);
smatch result;
string test_str = "receipt freind theif receive";
if (regex_search(test_str, result, r)) // 找到一个就会停止
    cout << result.str() << endl;
```
regex对象
```c++
regex r(re)
regex r(re, f)
 // re可以是一个string，表示字符范围的迭代器对，字符数组指针，字符数组指针和计数器，花括号包围的字符列表，f标志
 r1 = re // 替换
 r1.assign(re,f) // =
 r.make_count() // r中子表达式的数目
 r.flags()

 //f, regex_constants::syntax_option_type
 icase // 忽略大小写
 nosubs // 不保存匹配的子表达式
 optimize // 执行速度优先与构造速度
 ECMAScript // 使用 ECMA-262指定的语法
 basic // 使用POSIX基本的正则表达式语法
 extended // 使用POSIX扩展的正则表达式语法
 awk // 使用POSIX版本的awk语言的语法
 grep
 egrep
 ```
**匹配文件名**
```c++
// cpp cxx cc
regex r("[[:alnum:]]+\\.(cpp|cxx|cc)$", regex::icase);
smatch results;
string filename;
while (cin >> filename)
    if (regex_search(filename, results, r))
        cout <<results.str() << endl;
```
**错误**
运行时解析

regex_error
```c++
// 漏掉右括号
try {
    regex r("[[:alnum:]+\\.(cpp|cxx|cc)$", regex::icase);
} catch (regex_error e) {
    cout << e.what() << "\ncode: " << e.code() << endl;
}

//
regex_error(error_brack):
The expression contained mismatched [ and ].
code: 4
```
**regex 类型和输入序列**
string - regex, smatch, ssub_match, sregex_iterator
const char* - regex, cmatch, csub_match, cregex_iterator
wstring - wregex, wsmatch, wssub_match, wsregex_iterator
const wchar_t* wregex, wcmatch, wcsub_match, wcregex_iterator

## 17.3.2 匹配与regex迭代器类型
```c++
sregex_iterator it(b,e,r);
sregex_iterator end; // 尾后迭代器
*it
it->
++it
it++
it1 == it2
it1 != it2
```
使用
```c++
// 查找不在字符c之后的字符串ei
string pattern("[^c]ei"); // 不是c的字符后面接ei
// 前后匹配零个或多个字母
pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
regex r(pattern, regex::icase);
string test_str = "receipt freind theif receive";
for (sregex_iterator it(test_str.begin(), test_str.end(), r), end_it; it != end_it; ++it)
    cout << it->str() << endl;
```
**prefix 和 suffix**
```c++

for (sregex_iterator it(test_str.begin(), test_str.end(), r), end_it; it != end_it; ++it) {
    auto pos = it->prefix().length();
    pos = pos > 40 ? pos - 40 : 0; // 只要40个字符
    cout << it->prefix().str().substr(pos)
         << "\n\t\t >>>" << it->str() << " <<<\n"
         << it->suffix().str().substr(0,40) << endl;
}
```
**smatch 操作**
```c++
m.ready() // 如果通过regex_search regex_match设置了m，返回true
m.size() // 子表达式的数目
m.empty()
m.prefix()
m.suffix()
m.format(...)
// n 默认 0，且必须小于 m.size()
m.length(n) // 第n个匹配的子表达式的大小
m.position(n) // 距离序列开始的距离
m.str(n) //
m[n] // 第n个子表达式的ssub_match对象
m.begin(), m.end()
m.cbegin(), m.cend()
```

## 17.3.3 使用子表达式
用括号包裹的模式 `([[:alnum:]]+)`

```c++
if (regex_search(filename, results, r))
    cout << results.str(1) << endl;
//foo.cpp
// str(0): foo.cpp
// str(1): foo
// str(2): cpp
```
**子表达式用于数据验证**
ECMAScript ：
* \{d} 表示单个数字 \{d}{n} n个数字的序列
* 在方括号中的字符集合表示匹配这些字符中任意一个 [-. ]
* ? 可选，\{d}{3}[-. ]?\{d}{4} 可选的- . 空格
* \[\] 转义
* C++ 中\是特殊字符，所以用 \\{d}{3} 表示 \{d}{3}

```c++
string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
regex r(phone);
smatch m;
string s;
while (getline(cin, s)) {
    for (sregex_iterator it(s.begin(), s.end(),r), end_it;
        it != end_it; ++it)
        if (valid(*it))
            cout << "valid: " << it->str() << endl;
        else
            cout << "not valid: " << it->str() << endl;>
}

bool valid(const smatch& m)
{
    if (m[1].matched)
        return m[3].matched && (m[4].matched == 0 || m[4].str() == " ");
    else
        return !m[3].matched && m[4].str() == m[6].str();
}
```
子匹配操作
```c++
matched // 是否匹配
first, second // 指向匹配序列首元素和尾后位置的迭代器
length()
str()
s = ssub // s=ssub.str()
```

## 17.3.4 使用 regex_replace
```c++
m.format(dest, fmt, mft)
m.format(fmt, mft)
//使用格式字符串fmt生成格式化输出，mft是可选的flag
//使用dest的写入迭代器位置，第二个返回一个string
regex_replace(dest, seq, r, fmt, mft)
regex_replace(seq, r, fmt, mft)
//遍历seq，用regex_search查找与regex对象r匹配的子串

string fmt = "$2.$5.$7" //$子表达式索引

regex r(phone);
string number = "(908) 555-1800";
cout << regex_replace(number, r, fmt);
//
//908.555.1800
```
**用来控制匹配和格式的标志**
```c++
using std::regex_constants::format_no_copy;
//
match_defaut //==format_default
match_not_bol //不将首字符作为行首处理
match_not_eol //不将尾字符作为行尾处理
...

string fmt2 = "$2.$5.$7 ";
cout << regex_replace("my (908) 555-1800"s, r, fmt2, format_no_copy);
//
//908.555.1800 // 不输出输入序列中未匹配的部分
```

# 17.4 随机数
## 17.4.1 随机数引擎和分布
**随机数引擎**，调用运算符返回一个随机unsigned整数
```c++
Engine e;
Engine e(s); // 整型值s作为种子
e.seed(s) // 使用种子重置引擎状态
e.min()
e.max()

Engine::result_type
e.discard(u) // 将引擎推进u步

default_random_engine // 编译器默认引擎
```
**分布**
```c++
uniform_int_distribution<unsigned> u(0,9);
// [0,9]均匀分布
default_random_engine e;
for (size_t i=0; i < 10; ++i)
    cout << u(e);
// 分布对象使用引擎参数生成随机数，并将其映射到指定的分布
```
**随机数序列**
正确方法，static
```c++
vector<unsigned> good_randVec()
{
    static default_random_engine e;
    static uniform_int_distribution<unsigned> u(0,9);
    vector<unsigned> ret;
    for (size_t i = 0; i < 100; ++i)
        ret.push_back(u(e));
    return ret;
}
```
**种子**
```c++
default_random_engine e1;
default_random_engine e2(2147483646);
default_random_engine e3;
e3.seed(32767);

#include <ctime>
default_random_engine e1(time(0)); // 秒级生成
```
## 17.4.2 其他随机数分布
**随机实数**
```c++
default_random_engine e;
uniform_real_distribution<double> u(0, 1);
u(e);

u.min()
u.max()
u.reset()
```
**默认类型**
```c++
uniform_real_distribution<> u(0,1); // 默认生成 double
```
**非均匀分布**
```c++
default_random_engine e;
normal_distribution<> n(4,1.5); //均值4，标准差1.5
n(e);
```
**bernoulli_distribution类**
返回true的概率默认0.5
```c++
default_random_engine e;
bernoulli_distribution b;
b(e);
// 0.55
bernoulli_distribution b(.55);
```

# 17.5 IO库再探
## 17.5.1 格式化输入与输出
布尔值的格式 boolalpha/noboolalpha

整型值的进制 hex oct dec // 浮点值不受影响

指出进制 showbase/noshowbase

大写十六进制数字母 uppercase/nouppercase

浮点数格式 scientific/fixed

打印精度 cout.precision()/cout.precision(12)/setprecision(12)

打印小数点 showpoint/noshowpoint

补白 setfill('#')/setw(12)/left/right

控制输入格式 cin>>noskipws

## 17.5.2 未格式化的输入输出操作
**单字节操作**

is.get(ch), os.put(ch)

is.get() //返回int

退回字符
* is.putback(ch) // 退回流中读取的最后一个值，接受一个参数必须与最后读取的值相同，返回is
* is.unget() // 输入流向后移动，返回is
* is.peek() // 将下一个字节作为int返回，但不从流中删除它

检测文件尾
```c++
int ch;
while ((ch=cin.get()) != EOF)
    cout.put(ch);
```

**多字节操作**
```c++
is.get(sink, size, delim)
// 读取最多size个字节到字符数组sink中，遇到delim停止，delim留在流中
is.getline(sink, size, delim) // 读取并丢弃delim
is.read(sink, size) // 返回is
is.gcount() //上一个读取操作的字节数，退回过为0
os.write(source, size) // 返回os
is.ignore(size, delim) // 读取并忽略最多size个字符，包括delim
```

## 17.5.3 流随机访问
适用于 fstream sstream


