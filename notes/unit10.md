# 10.1 概述
```c++
auto result = find(vec.cbegin(), vec.cend(), val);
```

# 10.2 初识泛型算法
## 10.2.1 只读算法
find,count,

accumulate
```c++
#include <numeric>

int sum = accumulate(vec.cbegin(), vec.cend(), 0);
// 求和（迭代器范围，和的初值）
// int double long string
```

equal
```c++
equal(roster1.cbegin(), roster1.end(), roster2.cbegin());
// true or false
```
## 10.2.2 写容器元素的算法
### fill
```c++
fill(vec.begin(), vec.end(), 0);
```
### fill_n
```c++
fill_n(vec.begin(), vec.size(), 0);
```
### back_inserter
```c++
#include <iterator>

vector<int> vec;

auto it = back_inserter(vec); //返回一个迭代器
*it = 42;

fill_n(back_inserter(vec), 10, 0);
```
### 拷贝算法
内置数组的拷贝
```c++
int a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int a2[sizeof(a1)/sizeof(*a1)]; //a2与a1大小相同

auto ret = copy(begin(a1), end(a1), a2); //返回目的位置末尾的迭代器，a2至少要有a1的长度
```

replace
```c++
replace(ilst.begin(), ilst.end(), 0, 42);

//不改变原序列
replace_copy(ilst.begin(), ilst.end(), back_inserter(ivec), 0, 42);
```
## 10.2.3 重排容器元素的算法
```c++
sort(words.begin(), words.end());
auto end_unique = unique(words.begin(), words.end());
words.erase(end_unique, words.end());
```
# 10.3 定制操作
## 10.3.1 向算法传递函数
谓词
```c++
bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

sort(words.begin(), words.end(), isShorter);
```
相同长度按字典排序
```c++
stable_sort(words.begin(), words.end(), isShorter);
```
## 10.3.2 lambda表达式
```c++
[capture list](parameter list) -> return type { function body }

auto f = [] { return 42; }

cout << f();

// 传递参数
stable_sort(words.begin(), words.end(), 
            [](const string &a, const string &b)
              { return a.size() < b.size(); });

// 使用捕获列表
[sz](const string &a){ return a.size() >= sz; }
```
```c++
void biggies(vector<string> &words, vector<string>::size_type sz)
{
    elimDups(words);
    stable_sort(words.begin(), words.end(), isShorter);
    auto wc = find_if(words.begin(), words.end(),
         [sz](const string &a){ return a.size() >= sz; }); 
    // find_if第三个参数是一个一元谓词，不能同时接受string和sz
    // 返回第一个使谓词返回非0值得的元素的迭代器

    // 计算满足的个数
    auto count = words.end() - wc;
    cout << count << " " << make_plural(count, "word", "s")
         << " of length " << sz << " or longer" << endl;

    // for_each算法
    for_each(wc, words.end(), 
             [](const string &s){cout << s << " ";});
    cout << endl;
}
```
stable_partition

## 10.3.3 lambda捕获和返回
### 值捕获
变量在lambda创建时拷贝，修改不影响lambda
```c++
size_t v1 = 42;
auto f = [v1]{return v1;};
v1 = 0;
auto j = f();
```
### 引用捕获
```c++
void biggies(vector<string> &words,
             vector<string>::size_type sz,
             ostream &os = cout, char c = ' ')
{
    ...

    for_each(words.begin(), words.end(),
             [&os, c](const string &s){ os << s << c; });
}
```
### 隐式捕获
编译器推断捕获列表，&引用方式，=值捕获
```c++
wc = find_if(words.begin(), words.end(),
             [=](const string &s){return s.size() >= sz;});

// 混合使用
void biggies(vector<string> &words,
             vector<string>::size_type sz,
             ostream &os = cout, char c = ' ')
{
    ...
    // os隐式捕获，引用方式，c显式捕获，值方式
    for_each(words.begin(), words.end(),
             [&, c](const string &s){ os << s << c; });
    // os显式捕获，引用方式，c隐式捕获，值方式
    for_each(words.begin(), words.end(),
             [=, &os](const string &s){ os << s << c; });
}
```
### 可变lambda
改变一个被捕获的变量的值
```c++
size_t v1 = 42;
auto f = [v1]() mutable {return ++v1;};
```
引用捕获的变量是否可修改依赖于是否const

### 指定lambda返回类型
如果一个lambda包含return之外的任何语句，假定返回void

定义返回类型
```c++
transform(vi.begin(), vi.end(), vi.begin(),
          [](int i) -> int
          {if (i < 0) return -i; else return i;});
```
## 10.3.4 参数绑定
### 标准库bind函数
```c++
#include <functional>

auto newCallable = bind(callable, arg_list);
```
check_size
```c++
bool check_size(const string &s, string::size_type sz)
{
    return s.size() >= sz;
}
auto wc = find_if(words.begin(), words.end(),
                  bind(check_size, _1, sz));
```
### placeholders
_n定义在placeholders命名空间

`using std::placeholders::_1;`

`using namespace std::placeholders;`

### bind的参数
```c++
//f 有5个参数
auto g = bind(f, a, b, _2, c, _1);
//g 是2个参数
//g(X, Y) == f(a, b, Y, c, X)
```
### 用bind重排参数顺序

### 绑定引用参数
```c++
ostream &print(ostream &os, const string &s, char c)
{
    return os << s << c;
}

for_each(words.begin(), words.end(), bind(print, ref(os), _1, ' '));
// ref返回一个对象，包含给定的引用，此对象是可拷贝的
// ref，cref定义在头文件functional
```
# 10.4 在探迭代器
iterator头文件
## 10.4.1 插入迭代器
```c++
auto it = inserter(c, iter);
*it = val;

// lst = {1,2,3,4}
copy(lst.cbegin(), lst.cend(), front_inserter(lst2)); //lst2 = {4,3,2,1}
copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin())); //lst3 = {1,2,3,4}

inserter(c, iter)
front_inserter(iter)
back_inserter(iter)
```
## 10.4.2 iostream迭代器
### istream_iterator操作
```c++
istream_iterator<int> in_iter(cin);
istream_iterator<int> eof; // 尾后迭代器
while (in_iter != eof)
{
    vec.push_back(*in_iter++);
}

//
istream_iterator<int> in_iter(cin), eof;
vector<int> vec(in_iter, eof);
```
### 使用算法操作流迭代器
```c++
istream_iterator<int> in(cin), eof;
cout << accumulate(in, eof, 0) << endl;
```
### 允许懒惰求值

### ostream_iterator操作
```c++
ostream_iterator<int> out_iter(cout, " ");
for (auto e : vec)
    *out_iter++ = e; //或 out_iter = e;
cout << endl;

copy(vec.begin(), vec.end(), out_iter);
cout << endl;
```
### 使用流迭代器处理类类型
```c++
istream_iterator<Sales_item> item_iter(cin), eof;
ostream_iterator<Sales_item> out_iter(cout, "\n");

Sales_item sum = *item_iter++;
while (item_iter != eof)
{
    if (item_iter->isbn() == sum.isbn())
        sum += *item_iter++;
    else 
    {
        out_iter = sum;
        sum = *item_iter++;
    }
}
out_iter = sum;
```
## 10.4.3 反向迭代器
除了forward_list，流迭代器,其他容器都支持

打印最后一个单词
```c++
auto rcomma = find(line.crbegin(), line.crend(), ',');
cout << string(rcomma.base(), line.cend()) << endl;
```