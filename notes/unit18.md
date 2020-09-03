# 18.1 异常处理
## 18.1.1 抛出异常
一旦程序开始执行异常处理代码，则沿着调用链创建的对象将被销毁

**栈展开**
对象的析构函数会被自动调用

析构函数不应该抛出不能被它自身处理的异常

**异常对象**

## 18.1.2 捕获异常
**重新抛出**
```c++
catch (my_error &eObj) { 
    eObj.status = errCodes::severeErr; // 修改了异常对象
    throw;
} catch (other_error eObj) {
    eObj.status = errCodes::badErr; // 修改了副本
    throw;
}
```
**捕获所有异常**
```c++
void manip() {
    try {
        // ...
    }
    catch (...) {
        // ...
        throw;
    }
}
```

## 18.1.3 try与构造函数
构造函数体内的catch无法处理构造函数初始值列表抛出的异常

**函数try语句块**
```c++
template <typename T>
Blob<T>::Blob(std::initializer_list<T> il) try :
    data(std::make_shared<std::vector<T>>(il)) {
        
} catch(const std::bad_alloc &e) { handle_out_of_memory(e); }
```
**异常说明的实参**
```c++
void recoup(int) noexcept(true); // 不会抛出异常
```

**noexcept**
一个一元运算符

函数指针及该指针所指的函数必须具有一致的异常说明

一个虚函数承诺不抛异常，则派生的虚函数必须同样

## 18.1.5 异常类层次
```
exception
    bad_cast
    bad_alloc
    runtime_error
        overflow_error
        underflow_error
        range_error
    logic_error
        domain_error
        invalid_argument
        out_of_range
        length_error
```
**自定义异常类**
```c++
class out_of_stock: public std::runtime_error {
public:
    explicit out_of_stock(const std::string &s):
        std::runtime_error(s) {}
};
class isbn_mismatch: public std::logic_error {
public:
    explicit isbn_mismatch(const std::string &s):
        std::logic_error(s) {}
    isbn_mismatch(const std::string &s, const std::string &lhs, const std::string &rhs):
        std::logic_error(s), left(lhs), right(rhs) {}
    const std::string left, right;
};

Sales_data::operator+=(const Sales_data& rhs)
{
    if (isbn() != rhs.isbn())
        throw isbn_mismatch("wrong isbns", isbn(), rhs.isbn());
    ...
}
```
# 18.2 命名空间
命名空间可以是不连续的

外部定义

模板特例化在命名空间声明后可以外部定义

全局命名空间 ::member

嵌套的命名空间

内联命名空间

未命名的命名空间

## 18.2.2 使用命名空间成员
命名空间别名 `namespace primer = cplusplus_primer`

写 `std::move`

## 18.2.4 重载与命名空间
using

# 18.3 多重继承与虚继承
