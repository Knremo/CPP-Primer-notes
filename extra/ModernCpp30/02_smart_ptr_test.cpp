#include <utility> //std::swap
#include <cstdio>

class shared_count {
public:
    shared_count(): count_(1) {}
    void add_count()
    {
        ++count_;
    }
    long reduce_count()
    {
        return --count_;
    }
    long get_count() const
    {
        return count_;
    }
private:
    long count_;
};

template <typename T>
class smart_ptr {
public:
    template <typename U>
    friend class smart_ptr; // 模板的各个实例之间没有 friend 关系，不能互相访问私有成员 ptr_

    // 构造函数，如果传入的指针不为空则构造 shared_count() 对象
    explicit smart_ptr(T* ptr = nullptr): ptr_(ptr)
    {
        if (ptr) {
            shared_count_ = new shared_count();
        }
    }
    // 析构函数，ptr_ 不为空，且计数器减一之后为0，则 delete
    ~smart_ptr()
    {
        if (ptr_ && !shared_count_->reduce_count()) { // 会减一的
            delete ptr_;
            delete shared_count_;
        }
    }
    // 拷贝构造函数，只能用于相同模板参数的对象
    smart_ptr(const smart_ptr& other)
    {
        ptr_ = other.ptr_;
        if (ptr_) {
            other.shared_count_->add_count();
            shared_count_ = other.shared_count_;
        }
    }
    // 拷贝构造函数，同上，但是可以用于不同模板参数的对象 
    // 例如 smart_ptr<circle> ptr1; smart_ptr<shape> ptr2{ptr1};
    // 不能把 smart_ptr<circle> 转换为 smart_ptr<triangle>,因为 ptr_ = other.ptr_; 这一句，可以将
    // circle* 转为 shape*，但不能转为 triangle*
    // 定义这个功能与上面的相同，但不定义上面的非模板拷贝构造函数，编译器会合成拷贝构造函数，出错
    template <typename U>
    smart_ptr(const smart_ptr<U>& other) noexcept
    {
        ptr_ = other.ptr_;
        if (ptr_) {
            other.shared_count_->add_count(); // 增加计数器
            shared_count_ = other.shared_count_;
        }
    }
    // 移动构造函数
    template <typename U>
    smart_ptr(smart_ptr<U>&& other) noexcept
    {
        ptr_ = other.ptr_;
        if (ptr_) {
            shared_count_ = other.shared_count_;
            other.ptr_ = nullptr;
        }
    }
    template <typename U>
    smart_ptr(const smart_ptr<U>& other, T* ptr) noexcept
    {
        ptr_ = ptr;
        if (ptr_) {
            other.shared_count_->add_count();
            shared_count_ = other.shared_count_;
        }
    }
    // 赋值构造函数
    // 拷贝传参时调用拷贝构造函数，计数器已经加1，直接和临时对象交换
    smart_ptr& operator=(smart_ptr rhs) noexcept
    {
        rhs.swap(*this);
        return *this;
    }

    // 返回私有成员 ptr_
    T* get() const noexcept
    {
        return ptr_;
    }
    // 返回引用计数值
    long use_count() const noexcept
    {
        if (ptr_) {
            return shared_count_->get_count();
        } else {
            return 0;
        }
    }
    void swap(smart_ptr& rhs) noexcept
    {
        using std::swap;
        swap(ptr_, rhs.ptr_);
        swap(shared_count_, rhs.shared_count_);
    }

    T& operator*() const noexcept { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }
    operator bool() const noexcept { return ptr_; }

private:
    T* ptr_;
    shared_count* shared_count_;
};

class shape {
public:
    virtual ~shape() {}
};

class circle: public shape {
public:
    ~circle() { puts("~circle()"); }
};

template <typename T>
void swap(smart_ptr<T>& lhs, smart_ptr<T>& rhs) noexcept
{
    lhs.swap(rhs);
}

template <typename T, typename U>
smart_ptr<T> static_pointer_cast(const smart_ptr<U>& other) noexcept
{
    T* ptr = static_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}
template <typename T, typename U>
smart_ptr<T> dynamic_pointer_cast(const smart_ptr<U>& other) noexcept
{
    T* ptr = dynamic_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}
template <typename T, typename U>
smart_ptr<T> reinterpret_pointer_cast(const smart_ptr<U>& other) noexcept
{
    T* ptr = reinterpret_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}
template <typename T, typename U>
smart_ptr<T> const_pointer_cast(const smart_ptr<U>& other) noexcept
{
    T* ptr = const_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}
int main()
{
    smart_ptr<circle> ptr1{new circle()};
    printf("use count of ptr1 is %ld\n", ptr1.use_count());
    smart_ptr<shape> ptr2;
    printf("use count of ptr2 is %ld\n", ptr2.use_count());
    //ptr2 = std::move(ptr1); 
    ptr2 = ptr1;
    printf("use count of ptr2 is now %ld\n", ptr2.use_count());
    if (ptr1) {
        puts("ptr1 is not empty");
    } else {
        puts("ptr1 is empty");
    }

    smart_ptr<circle> ptr3 = static_pointer_cast<circle>(ptr2);
    printf("use count of ptr3 id %ld\n", ptr3.use_count());

    return 0;
}