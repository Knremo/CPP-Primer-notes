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
## 11.3 关联容器操作
```c++
set<string>::value_type v1; // string
set<string>::key_type v2; // string
map<string, int>::value_type v3; // pair<const string, int>
map<string, int>::key_type v4; // string
map<string, int>::mapped_type v5; // int
```
### 11.3.1 关联容器迭代器
```c++
auto map_it = word_count.begin();
// *map_it pair<>
cout << map_it->first; // first const
++map_it->second;
```
#### set的迭代器是const的
不能修改

#### 遍历关联容器
```c++
auto map_it = word_count.cbegin();
while (map_it != word_count.cend())
{
    ...
    ++map_it;
}
```

#### 关联容器和算法
使用find成员而不是泛型find

### 11.3.2 添加元素
set
```c++
vector<int> ivec = {2, 4, 6, 8, 2, 4, 6, 8};
set<int> set2;
set2.insert(ivec.cbegin(), ivec.cend());
set2.insert({1, 3, 5, 7, 1, 3, 5, 7}); // 只会插入不重复的元素

map
```c++
word_count.insert({word, 1});
word_count.insert(make_pair(word, 1));
word_count.insert(pair<string, size_t>(word, 1));
word_count.insert(map<string, size_t>::vlaue_type(word, 1));

c.emplace(args)
```
#### 检测insert的返回值
返回一个pair，first迭代器指向给定关键字的元素，second成员是bool指出是否插入成功
```c++
auto ret = word_count.insert({word, 1});
if (!ret.second)
    ++ret.first->second;

// or
while (cin >> word)
    ++word_count.insert({word, 0}).first->second;
```
### 11.3.3 删除元素
```c++
c.erase(k) //k关键字，返回删除的数量
c.erase(p) // p迭代器，返回p之后元素的迭代器
c.erase(b, e) // 一对迭代器，返回e
```

### 11.3.4 map的下标操作
只有map，unordered_map
```c++
c[k]
c.at(k)
```
map下标操作获得一个mapped_type对象(int)，解引用一个map迭代器时得到一个value_type对象(pair)

### 11.3.5 访问元素
```c++
//下标和at操作只适用于非const的map和unordered_map
c.find(k)
c.count(k)
c.lower_bound(k) //返回第一个关键字不小于k的元素的迭代器
c.upper_bound(k) //大于
c.equal_range(k) //返回一个迭代器pair，表示关键字等于k的元素的范围，k不存在等于c.end()
```
#### 在multimap,multiset中查找元素
相同关键字在容器中会相邻存储
```c++
string search_item("A");
auto entries = authors.count(search_item);
auto iter = authors.find(search_item);
while (entries)
{
    cout << iter->second << endl;
    ++iter;
    --entries;
}
```
or
```c++
for (auto beg = authors.lower_bound(search_item),
          end = authors.upper_bound(search_item);
     beg != end; ++beg)
    cout << beg->second << endl;
```
or
```c++
for (auto pos = authors.equal_range(search_item);
     pos.first != pos.second; ++pos.first)
    cout << pos.first->second << endl;
```
### 11.3.6 一个单词转换的map
```c++
map<string, string> buildMap(ifstream &map_file)
{
    map<string, string> trans_map;
    string key;
    string value;
    while (map_file >> key && getline(map_file, value))
        if (value.size() > 1)
            trans_map[key] = value.substr(1); // 去除前面的空格
        else
            throw runtime_error("no rule for " + key);
    return trans_map;
}

const string& transform(const string &s, const map<string, string> &m)
{
    auto map_it = m.find(s);
    if (map_it != m.cend())
        return map_it->second;
    else
        return s;
}

void word_transform(ifstream &map_file, ifstream &input)
{
    auto trans_map = buildMap(map_file);
    string text;
    while (getline(input, text))
    {
        istringstream stream(text);
        string word;
        bool firstword = true;
        while (stream >> word)
        {
            if (firstword)
                firstword = false;
            else
                cout << " ";
            cout << transform(word, trans_map);
        }
        cout << endl;
    }
}
```

## 11.4 无序容器
哈希函数

find,insert...

管理桶
```c++
//桶接口
c.bucket_count() // 正在使用的桶的数目
c.max_bucket_count() // 容器能容纳的最多的桶的数量
c.bucket_size(n) // 第n个桶中有多少个元素
c.bucket(k) // 关键字为k的元素在哪个桶中
//桶迭代
local_iterator // 访问桶中元素的迭代器类型
const_local_iterator
c.begin(n),c.end(n) //
c.cbegin(n),c.cend(n)
//哈希策略
c.load_factor() // 每个桶的平均元素数量，返回float值
c.max_load_factor() // 
c.rehash(n) // 重组存储，使得bucket_count>=n,且bucket_count>size/max_load_factor
c.reserve(n) // 重组存储，使得c可以保存n个元素且不必rehash
```

默认使用关键字类型的==运算符来比较元素，使用hash<key_type>类型的对象来生成每个元素的哈希值

自定义关键字类型
```c++
size_t hashser(const Sales_data &sd)
{
    return hash<string>() (sd.isbn());
}
bool eqOp(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() == rhs.isbn();
}
using SD_multiset = unordered_multiset<Sales_data, decltype(hasher) *, decltype(eqOp) *>;
SD_multiset bookstore(42, hasher, eqOp);
```