# 1. 调用者负责管理内存，接口负责生成
C 的惯用做法
```c++
MyObj obj;
ec = initialize(&obj);
```

# 2. 借口负责对象的堆上生成和内存管理
接口提供生成和销毁对象的函数，对象在堆上维护，然后由调用者通过调用 delete 来释放
```c++
matrix* add(const matrix* lhs, const matrix* rhs, error_code_t* ec);
void deinitialize(matrix** mat);

error_code_t ec;
matrix* temp = nullptr;
temp = add(a, b, &ec);
if(!temp) goto end;
end:
    if (temp)
        deinitialize(&temp);
```


