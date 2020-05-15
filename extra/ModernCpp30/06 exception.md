# 1. 使用异常
矩阵操作，分配内存，构造，销毁清理，矩阵乘法
```c++
class matrix {
    friend matrix operator*(const matrix&, const matrix&);
public:
    matrix(size_t nrows, size_t ncols)
    {
        data_ = new float[nrows * ncols];
        nrows_ = nrows;
        ncols_ = ncols;
    }
    ~matrix()
    {
        delete[] data_;
    }
private:
    float* data_;
    size_t nrows_;
    size_t ncols_;
};

matrix operator*(const matrix& lhs, const matrix& rhs)
{
    if (lhs.ncols != rhs.nrows) {
        throw std::runtime_error("matrix sizes mismatch");
    }
    matrix result(lhs.nrows, rhs.ncols);
    // do multiplication
    return result;
}

// usage
matrix c = a * b;
```
异常安全的代码，可以没有任何 try 和 catch

**异常安全**是指当异常发生时，既不会发生资源泄露，系统也不会处于一个不一致的状态

可能会出现错误/异常的地方：
* 内存分配， new 出错，一般会得到异常 bad_alloc, 在 catch 捕捉到这个异常之前，所有栈上的对象会被全部析构，资源全部自动清理
* 矩阵尺寸不合适，得到一个异常，c 不会被构造
* 乘法函数内部内存分配失败，result 不会构造，也没有 c
* a, b 是本地变量，析构会自动释放空间

# 2. 异常的问题
如果一个函数声明了不会抛出异常、结果却抛出了异常，C++ 运行时会调用 std::terminate 来终止应用程序

1. 写异常安全的代码，尤其在模板里。可能的话，提供强异常安全保证 ，在任何第三方代码发生异常的情况下，不改变对象的内容，也不产生任何资源泄漏。
2. 如果你的代码可能抛出异常的话，在文档里明确声明可能发生的异常类型和发生条件。确保使用你的代码的人，能在不检查你的实现的情况，了解需要准备处理哪些异常。
3. 对于肯定不会抛出异常的代码，将其标为 noexcept。注意类的特殊成员（构造函数、析构函数、赋值函数等）会自动成为 noexcept，如果它们调用的代码都是 noexcept 的话。所以，像 swap 这样的成员函数应当尽可能标成 noexcept。

# 3. 使用异常的理由
在能使用 [] 运算符的地方，C++ 的标准容器也提供了 at 成员函数，能够在下标不存在的时候抛出异常

```c++
vector<int> v{1, 2, 3};

try {
    v.at(3);
} 
catch (const out_of_range& e) {
    cerr << e.what() << endl;
}
```

**强异常保证**: 一旦异常发生，现场会恢复到调用函数之前的状态，容器的内容不会发生改变，也没有任何资源泄漏