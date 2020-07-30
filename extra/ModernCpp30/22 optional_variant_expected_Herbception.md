# 1. optional
C++17

构造一个 optional<T> 对象有以下几种方法：
1. 不传递任何参数，或者使用特殊参数 std::nullopt（可以和 nullptr 类比），可以构造一个“空”的 optional 对象，里面不包含有效值。 
2. 第一个参数是 std::in_place，后面跟构造 T 所需的参数，可以在 optional 对象上直接构造出 T 的有效值。
3. 如果 T 类型支持拷贝构造或者移动构造的话，那在构造 optional<T> 时也可以传递一个 T 的左值或右值来将 T 对象拷贝或移动到 optional 中。

第 1 种情况，optional 对象里是没有值的，在布尔值上下文里，会得到 false

对于上面的第 2、3 两种情况，optional 对象里是有值的，在布尔值上下文里，会得到 true

在 optional 对象有值的情况下，你可以用 * 和 -> 运算符去解引用（没值的情况下，结果是未定义行为）

