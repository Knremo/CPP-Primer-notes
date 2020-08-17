# 1. 异常的用法
C++ 已经为异常设计了一个配套的异常类型体系，定义在 `<stdexcept>`
```
exception
    bad_alloc
    runtime_error
        range_error
        overflow_error
    logic_error
        invalid_argument
        length_error
    bad_cast
```

可以从 runtime_error 派生出自己的异常类：
```c++
class my_exception: public std::runtime_error
{
public:
    using this_type = my_exception;
    using super_type = std::runtime_error;
public:
    my_exception(const char* msg): super_type(msg) {}
    my_exception() = default;
    ~my_exception() = default;
private:
    int code = 0;
};
```

抛异常的函数不会有返回值，应该用“属性”做编译阶段优化：
```cpp
[[noreturn]]
void raise(const char* msg)
{
    throw my_exception(msg);
}
```

C++ 允许编写多个catch 块，捕获不同的异常。但是，**异常只能按照 catch 块在代码里的顺序依次匹配，而不会去找最佳匹配**

catch 入口参数也应当使用 `const&` ,避免拷贝：
```c++
try
{
    raise("error occured")
}
catch (const exception& e)
{
    cout << e.what() << endl;
}
```

**function-try**:
```cpp
void some_function()
try
{
    ...
}
catch(...)
{
    ...
}
```

# 2. 谨慎使用异常
应当使用异常的判断准则：
1. 不允许被忽略的错误
2. 极少数情况下才会发生的错误
3. 严重影响正常流程，很难恢复到正常状态的错误
4. 无法本地处理，必须穿透调用栈，传递到上层才能被处理的错误

比如构造函数，读写文件

而 socket 通信，还是检查错误码重试比较好

# 3. 保证不抛出异常
noexcept ，编译器可以对函数做优化，不去加那些栈展开的额外代码，消除异常处理的成本

常用的 `noexcept` 相当于 `noexcept(true)`