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

