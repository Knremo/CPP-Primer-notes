# 1. string
begin, end, empty, size, swap

+, +=, find, rfind, getline, c_str, stoi, to_string

不在接口中使用 `const char*`

# 2. vector
begin, end, front, back, [], data, capacity, reserve, resize, pop_back, push_back, insert, erase (同 string)

emplace, emplace_back

如果元素类型没有提供一个保证不抛异常的移动构造函数，vector 通常会使用拷贝构造函数，因此，对于拷贝代价较高的自定义元素类型，应当定义移动构造函数并标记 noexcept，或只在容器中放置对象的智能指针

# 3. deque
double-ended queue 双端队列

可以从尾部和头部自由添加和删除

提供：push_front, emplace_front, pop_front

不提供：data, capacity, reserve

内存布局：有一个连续索引存储，部分连续，可以下标

# 4. list
双向链表，O(1) 复杂度的任意位置的插入和删除

提供：push_front, emplace_front, pop_front

不提供：data, capacity, reserve

遍历性能比 vector 和 deque 低

因为某些标准算法在 list 上会导致问题，list 提供了成员函数作为替代，包括下面几个：

merge, remove, remove_if, reverse, sort, unique

# 5. forward_list
单向链表

insert_after

# 6. 容器适配器
容器适配器 container adaptor

## queue FIFO

queue 缺省用 deque 来实现，跟 deque 相比：
* 没有 []
* 没有 begin, end
* emplace, push, pop

## stack

后进先出 LIFO

stack 缺省用 deque 来实现，跟 deque 相比：
* 没有 []
* 没有 begin, end
* back 成了 top, 没有 front
* emplace, push, pop

