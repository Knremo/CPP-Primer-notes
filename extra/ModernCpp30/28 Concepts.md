C++20 

我们只需要事先定义了 Integer 和 String 的概念，我们就可以写出下面这样的代码：
```c++
template <Integer N>
N half(N n)
{
    return n/2;
}
template <String S>
S half(S s)
{
    s.resize(s.size() / 2);
    return s;
}
```

# 1. Concepts 简史
从基本概念上来讲，“概念”就是一组对模板参数的约束条件

到了 2017 年 7 月，“概念”就正式并入 C++20 草案了

# 2. 基本的 Concepts
