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