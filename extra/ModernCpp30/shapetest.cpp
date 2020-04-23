#include <iostream>

enum class shape_type {
    circle,
    triangle,
    rectangle,
};

class shape {};
class circle : public shape {};
class triangle : public shape {};
class rectangle : public shape {};

shape* create_shape(shape_type type)
{
    switch (type) {
        case shape_type::circle:
            return new circle();
        case shape_type::triangle:
            return new triangle();
        case shape_type::rectangle:
            return new rectangle();
        default: return new circle();
    }
}

template <typename T>
class smart_ptr {
public:
    explicit smart_ptr(T* ptr=nullptr): ptr_(ptr) {}
    ~smart_ptr()
    {
        delete ptr_;
    }

    template <typename U>
    smart_ptr(smart_ptr<U>&& other)
    {
        ptr_ = other.release();
    }

    T* get() const { return ptr_; }

    smart_ptr(smart_ptr&& other)
    {
        ptr_ = other.release();
    }
    smart_ptr& operator=(smart_ptr rhs)
    {
        rhs.swap(*this); 
        return *this;
    }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    operator bool() const { return ptr_; }

    T* release()
    {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }
    void swap(smart_ptr& rhs)
    {
        using std::swap;
        swap(ptr_, rhs.ptr_);
    }
private:
    T* ptr_;
};

int main()
{
    smart_ptr<circle> ptr1{new circle()};
    smart_ptr<triangle> ptr2{std::move(ptr1)};
    
    return 0;
}