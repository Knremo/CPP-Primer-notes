# 1. 智能指针
C++ 里也是有垃圾回收的，不过不是 Java、Go 那种严格意义上的垃圾回收，而是广义上的垃圾回收，这就是**构造 / 析构函数**和 **RAII 惯用法**（Resource Acquisition Is Initialization）

# 2. unique_ptr
```cpp
unique_ptr<int> ptr1(new int(10));      // int智能指针
assert(*ptr1 == 10);                     // 可以使用*取内容
assert(ptr1 != nullptr);                // 可以判断是否为空指针

unique_ptr<string> ptr2(new string("hello"));  // string智能指针
assert(*ptr2 == "hello");                // 可以使用*取内容
assert(ptr2->size() == 5);               // 可以使用->调用成员函数
```
没有定义加减运算符，不能随意移动指针地址

**不要忘记初始化**
```cpp
unique_ptr<int> ptr3;                // 未初始化智能指针
*ptr3 = 42 ;                         // 错误！操作了空指针
```
可以调用工厂函数 `make_unique()`
```cpp
auto ptr3 = make_unique<int>(42);               // 工厂函数创建智能指针
assert(ptr3 && *ptr3 == 42);

auto ptr4 = make_unique<string>("god of war");  // 工厂函数创建智能指针
assert(!ptr4->empty());
```
`make_unique()` 要求 C++14, 如果使用 C++11,一个简化版的 `make_unique()`：
```cpp
template <class T, class... Args>
std::unique_ptr<T> my_make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
```
unique_ptr 不是线程安全的

## 2.1 unique_ptr 的所有权
唯一，禁用拷贝赋值

move
```cpp
auto ptr1 = make_unique<int>(42);    // 工厂函数创建智能指针
assert(ptr1 && *ptr1 == 42);         // 此时智能指针有效

auto ptr2 = std::move(ptr1);         // 使用move()转移所有权
assert(!ptr1 && ptr2);               // ptr1变成了空指针
```

# 3. shared_ptr
```cpp
shared_ptr<int> ptr1(new int(10));     // int智能指针
shared_ptr<string> ptr2(new string("hello"));  // string智能指针

auto ptr3 = make_shared<int>(42);  // 工厂函数创建智能指针
auto ptr4 = make_shared<string>("zelda");  // 工厂函数创建智
```
可拷贝赋值
```cpp
auto ptr1 = make_shared<int>(42);    // 工厂函数创建智能指针
assert(ptr1 && ptr1.unique() );     // 此时智能指针有效且唯一

auto ptr2 = ptr1;                  // 直接拷贝赋值，不需要使用move()
assert(ptr1 && ptr2);              // 此时两个智能指针均有效

assert(ptr1 == ptr2);             // shared_ptr可以直接比较

// 两个智能指针均不唯一，且引用计数为2
assert(!ptr1.unique() && ptr1.use_count() == 2); 
assert(!ptr2.unique() && ptr2.use_count() == 2); 
```
## 3.2 shared_ptr 注意事项
**循环引用**，把 shared_ptr 作为类成员的时候最容易出现，典型例子**链表节点**
```cpp
class Node final
{
public:
    using this_type     = Node;
    using shared_type   = std::shared_ptr<this_type>;
public:
    shared_type     next;      // 使用智能指针来指向下一个节点
};

auto n1 = make_shared<Node>();   // 工厂函数创建智能指针
auto n2 = make_shared<Node>();   // 工厂函数创建智能指针

assert(n1.use_count() == 1);    // 引用计数为1
assert(n2.use_count() == 1);

n1->next = n2;                 // 两个节点互指，形成了循环引用
n2->next = n1;

assert(n1.use_count() == 2);    // 引用计数为2
assert(n2.use_count() == 2);    // 无法减到0，无法销毁，导致内存泄漏
```
引用计数无法减到 0

# 4. weak_ptr
只观察指针，不会增加引用计数

可以调用 lock()，获取 shared_ptr

```cpp
class Node final
{
public:
    using this_type     = Node;

    // 注意这里，别名改用weak_ptr
    using shared_type   = std::weak_ptr<this_type>;
public:
    shared_type     next;    // 因为用了别名，所以代码不需要改动
};

auto n1 = make_shared<Node>();  // 工厂函数创建智能指针
auto n2 = make_shared<Node>();  // 工厂函数创建智能指针

n1->next = n2;             // 两个节点互指，形成了循环引用
n2->next = n1;

assert(n1.use_count() == 1);    // 因为使用了weak_ptr，引用计数为1
assert(n2.use_count() == 1);   // 打破循环引用，不会导致内存泄漏

if (!n1->next.expired()) {     // 检查指针是否有效
    auto ptr = n1->next.lock();  // lock()获取shared_ptr
    assert(ptr == n2);
}
```

