# 11 关联容器
```c++
#include <map>
#include <set>
//按关键字有序保存元素
map
set
multimap
multiset
//无序集合
unordered_map
unordered_set
unordered_multimap
unordered_multiset
```
## 11.1 使用关联容器
```c++
map<string, size_t> word_count;
set<string> exclude = {"The", "But"};
string word;
while (cin >> word)
    if (exclude.find(word) == exclude.end())
        ++word_count[word];
```
## 11.2 定义关联容器
### 11.2.1 定义关联容器
```c++
map<string, size_t> word_count;
set<string> exclude = {"the"};
map<string, string> authors = {{"a", "b"}};
```
### 11.2.2 关键字类型的要求
有<, 严格弱序

自己定义关键字类型
```c++
bool compareIsbn(const Sale_data &lhs, const Sale_data &rhs) 
{
    return lhs.isbn() < rhs.isbn();
}

multiset<Sales_data, decltype(compareIsbn) *> bookstore(compareIsbn);
//set<Sale_data, bool (*)(const Sale_data&, const Sale_data&)> s(compareIsbn);
```
### 11.2.3 pair类型
utility头文件

生成特定类型的模板

```c++
pair<string, string> anon;
pair<string, string> author = {"James", "Joyce"};

//数据成员public
w.first, w.second

//pair上的操作
pair<T1, T2> p;
pair<T1, T2> p(v1, v2);
pair<T1, T2> p = {v1, v2};

make_pair(v1, v2); // 返回一个pair

p1 < > <= >= p2

p1 == p2
p1 != p2
```

#### 创建pair对象的函数
```c++
pair<string, int> process(vector<string> &v)
{
    if (!v.empty())
        return {v.back(), v.back().size()};
    else
        return pair<string, int>();
}
```