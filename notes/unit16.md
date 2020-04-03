# 16 模板与泛型编程

## 16.1 定义模板
### 16.1.1 函数模板
```c++
template <typename T>
int compare(const T &v1, const T &v2)
{
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}
```
#### 实例化函数模板
编译器使用实参的类型来确定绑定到模板参数T的类型
```c++
cout << compare(1, 0) << endl;  // int
```
#### 模板类型参数
必须使用关键字class，typename，含义相同
```c++
template <typename T, class U> clac(const T&, const U&);
```
#### 非类型模板参数
模板实例化时，非类型参数被一个用户提供的或编译器推断的值所代替

这些值必须是常量表达式

```c++
template<unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M])
{
    return strcmp(p1, p2);
}

compare("hi", "mom")
// int compare(const char (&p1)[3], const char (&p2)[4])
```

#### inline和constexpr
```c++
template <typename T> inline T min(const T&, const T&);
```
#### 编写类型无关的代码
函数参数 const&

仅使用<比较运算
#### 模板编译
模板函数和类模板成员函数的定义通常放在头文件

### 16.1.2 类模板
不能推断模板参数类型

#### 定义类模板
```c++
template <typename T> class Blob {
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;

    Blob();
    Blob(std::initializer_list<T> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const T &t) { data->push_back(t); }
    void push_back(T &&t) { data->push_back(std::move(t)); }
    void pop_back();
    T& back();
    T& operator[](size_type i);
private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i, const std::string &msg) const;
};
template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}
template <typename T>
T& Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}
template <typename T>
T& Blob<T>::operator[](size_type i)
{
    check(i, "subscript out of range");
    return (*data)[i];
}
template <typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

template <typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) {  }

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)) {  }
```
#### 实例化类模板
`Blob<int> ia;`

#### 类模板的成员函数
定义在类模板之外的成员函数必须以关键字template开始

#### 类模板成员函数的实例化
一个类模板的成员函数只有当程序用到它时才进行实例化

#### 在类模板内简化模板类名的使用
```c++
template <typename T>
class BlobPtr {
public:
    BlobPtr() : curr(0) {}
    BlobPtr(Blob<T> &a, size_t sz = 0): wptr(a.data), curr(sz) {}
    T& operator*() const
        { auto p = check(curr, "dereference past end");
          return (*p)[curr]; }
    BlobPtr& operator++();
    BlobPtr& operator--(); // == BlobPtr<T>
private:
    std::shared_ptr<std::vector<T>> check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;
};
```
在一个类模板的作用域内，直接使用模板名而不必制定模板实参

#### 类模板和友元
一对一友好关系，对应实例及其友元的友好关系
```c++
template <typename> class BlobPtr;
template <typename> class Blob;
template <typename T>
bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T> class Blob {
    friend class BlobPtr<T>;
    friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
    // ...
};

Blob<char> ca; // BlobPtr<char>和operator==<char>是友元
```

也可以将另一个模板的每个实例都声明为自己的友元
```c++
template <typename T> class Pal;
class C {
    friend class Pal<C>; // 用类C实例化的Pal是C的一个友元，需要前置声明
    template <typename T> friend class Pal2; // Pal2的所有实例都是C的友元，无需前置声明
};
template <typename T> class C2 {
    friend class Pal<T>; // 一对一
    template <typename X> friend class Pal2; // Pal2的所有实例都是C2每个实例的友元，无需前置声明
    friend class Pal3;
};
```

令模板自己的类型参数成为友元
```c++
template <typename Type> class Bar {
    friend Type;
    // ...
};
```

#### 模板类型别名
```c++
template <typename T> using twin = pair<T, T>;
twin<string> authors;
```
#### 类模板的static成员
```c++
template <typename T> class Foo {
public:
    static std::size_t count() { return ctr; }
private:
    static std::size_t ctr;
};
template <typename T>
size_t Foo<T>::ctr = 0;

Foo<int> fi;
auto ct = Foo<int>::count();
ct = fi.count();
```

### 16.1.3 模板参数
#### 模板声明
声明中的模板参数不必与定义中相同

#### 使用类的类型成员
编译器对 `T::size_type * p` ，是定义一个名为p的变量还是将一个名为size_type的static数据成员与p相乘

希望通知编译器一个名字表示类型时，必须使用typename
```c++
template <typename T>
typename T::value_type top(const T& c)
{
    if (!c.empty())
        return c.back();
    else
        return typename T::value_type();
}
```

#### 默认模板实参
```c++
template <typename T, typename F = less<T>>
int compare(const T &v1, const T &v2, F f = F())
{
    if (f(v1, v2)) return -1;
    if (f(v2, v1)) return 1;
    return 0;
}
```

#### 模板默认实参与类模板
如果一个类模板为其所有模板参数都提供了默认实参且我们希望使用这些默认实参，就必须在模板名之后跟一个空尖括号对

### 16.1.4 成员模板
#### 普通类的成员模板
```c++
class DebugDelete {
public:
    DebugDelete(std::ostream &s = std::cerr): os(s) {}
    template <typename T> void operator()(T *p) const
    {
        os << "deleting unique_ptr" << std::endl;
        delete p;
    }
private:
    std::ostream &os;
};

double* p = new double;
DebugDelete d;
d(p);
int* ip = new int;
DebugDelete()(ip);

// 重载删除器
unique_ptr<int, DebugDelete> p(new int, DebugDelete());
```
#### 类模板的成员模板
```c++
template <typename T> class Blob {
    template <typename It> Blob(It b, It e);
    // ...
};

template <typename T>
template <typename It>
    Blob<T>::Blob(It b, It e): data(std::make_shared<std::vector<T>>(b, e)) {}
```

### 16.1.5 控制实例化
在多个文件中实例化相同的模板的额外开销可能非常严重

**显式实例化**

```c++
// a.cpp
extern template class Blob<string>;
extern template int compare(const int&, const int&);
//extern 不会在本文件生成实例化代码，程序在其他位置有该实例的一个非extern声明

Blob<string> sa1, sa2; // 实例化在其他位置
Blob<int> al = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // Blob<int> 及其接受initializer_list的构造函数在本文件中实例化
Blob<int> a2(a1); //拷贝构造函数在本文件中实例化
int i = compare(a1[0], a2[0]); // 实例化出现在其他位置

// b.cpp
template int compare(const int&, const int&); // 实例化在这个文件中
template class Blob<string>;
```

实例化定义会实例化所有成员，在一个类模板的实例化定义中，所用类型必须能用于模板的所有成员函数

### 16.1.6 效率与灵活性

## 16.2 模板实参推断
### 16.2.1 类型转换与模板类型参数
将实参传递给带模板类型的函数实参时，能够自动应用的类型转换只有const转换及数组或函数到指针的转换

#### 使用相同模板参数类型的函数形参
必须是相同类型

#### 正常类型转换应用于普通函数实参
```c++
template <typename T> ostream &print(ostream &os, const T &obj)
{
    return os << obj;
}

ofstream f("output");
print(f, 10); // 将f转换为ostream&
```

### 16.2.2 函数模板显式实参
#### 指定显式模板实参
```c++
template <typename T1, typename T2, typename T3>
T1 sum(T2, T3);

auto val3 = sum<long long>(i, lng); // T1 是显式指定的，T2 T3是从函数实参类型推断而来
```
显式模板实参按由左至右的顺序与对应的模板参数匹配

#### 正常类型转换应用于显式指定的实参
模板类型参数已经显式指定了的函数实参，进行正常类型转换
```c++
long lng;
compare<long>(lng, 1024);  // compare(long, long)
compare<int>(lng, 1024); // compare(int, int)
```

### 16.2.3 尾置返回类型与类型转换
不需要用户显式指定返回类型
```c++
template <typename It>
auto fcn(It beg, It end) -> decltype(*beg)
{
    // ...
    return *beg;
}
```
解引用运算符返回一个左值，通过 decltype 推断的类型为 beg 的类型的引用

#### 进行类型转换的标准库模板类
返回一个值的拷贝而非引用
```c++
#include <type_traits>

template <typename It>
auto fcn2(It beg, It end) -> typename remove_reference<decltype(*beg)>::type
{
    // ...
    return *beg;
}
```

### 16.2.4 函数指针和实参推断
```c++
template <typename T> int compare(const T&, const T&);
int (*pf1)(const int&, const int&) = compare;
// pf1 中参数的类型决定了T的模板实参的类型

// 无法确定时，显式指出
void func(int(*)(const string&, const string&));
void func(int(*)(const int&, const int&));

func(compare<int>);
```

### 16.2.5 模板实参推断和引用
