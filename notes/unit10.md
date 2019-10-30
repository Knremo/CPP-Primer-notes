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
