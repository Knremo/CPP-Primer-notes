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