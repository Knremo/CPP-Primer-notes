# 1. string
begin, end, empty, size, swap

+, +=, find, rfind, getline, c_str, stoi, to_string

不在接口中使用 `const char*`

# 2. vector
begin, end, front, back, [], data, capacity, reserve, resize, pop_back, push_back, insert, erase (同 string)

emplace, emplace_back

如果元素类型没有提供一个保证不抛异常的移动构造函数，vector 通常会使用拷贝构造函数，因此，对于拷贝代价较高的自定义元素类型，应当定义移动构造函数并标记 noexcept，或只在容器中放置对象的智能指针