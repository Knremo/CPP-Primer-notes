每个进程里可以有一个或多个线程:
* 每个进程有自己的独立地址空间，不与其他进程分享；一个进程里可以有多个线程，彼此共享同一个地址空间。
* 堆内存、文件、套接字等资源都归进程管理，同一个进程里的多个线程可以共享使用。每个进程占用的内存和其他资源，会在进程退出或被杀死时返回给操作系统。
* 并发应用开发可以用多进程或多线程的方式。
  * 多线程由于可以共享资源，效率较高；
  * 反之，多进程（默认）不共享地址空间和资源，开发较为麻烦，在需要共享数据时效率也较低。但多进程安全性较好，在某一个进程出问题时，其他进程一般不受影响；而在多线程的情况下，一个线程执行了非法操作会导致整个进程退出

# 1. 基于 thread 的多线程开发
```c++
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex output_lock;

void func(const char* name)
{
    this_thread::sleep_for(100ms);
    lock_guard<mutex> guard{output_lock};
    cout << "I am thread " << name << '\n';
}

int main()
{
    thread t1{func, "A"}; // 起一个线程
    thread t2{func, "B"};
    t1.join(); // 
    t2.join();
}
```
* thread 的构造函数的第一个参数是函数（对象），后面跟的是这个函数所需的参数。
* thread 要求在析构之前要么 join（阻塞直到线程退出），要么 detach（放弃对线程的管理），否则程序会异常退出。
* sleep_for 是 this_thread 名空间下的一个自由函数，表示当前线程休眠指定的时间。
* 如果没有 output_lock 的同步，输出通常会交错到一起。


thread 不能在析构时自动 join 有点不那么自然，封装一下:
```c++
class scoped_thread {
public:
    template <typename... Arg>
    scoped_thread(Arg&&... arg): thread_(std::forward<Arg>(arg)...) {}
    scoped_thread(scoped_thread&& other): thread_(std::move(other.thread_)) {}
    scoped_thread(const scoped_thread&) = delete; // thread 不能拷贝，但可以移动
    ~scoped_thread()
    {
        if (thread_.joinable())
            thread_.join();
    }

private:
    thread thread_;
};
```
只有 joinable（已经 join 的、已经 detach 的或者空的线程对象都不满足 joinable）的 thread 才可以对其调用 join 成员函数，否则会引发异常。

# 2. mutex
**互斥量**的基本语义是，一个互斥量只能被一个线程锁定，用来保护某个代码块在同一时间只能被一个线程执行

mutex 只可默认构造，不可拷贝（或移动），不可赋值，主要提供的方法是：
* lock：锁定，锁已经被其他线程获得时则阻塞执行
* try_lock：尝试锁定，获得锁返回 true，在锁被其他线程获得时返回 false
* unlock：解除锁定（只允许在已获得锁时调用）

C++ 标准库还提供了：
* recursive_mutex 递归互斥量
* timed_mutex：允许锁定超时的互斥量
* recursive_timed_mutex：允许锁定超时的递归互斥量
* shared_mutex：允许共享和独占两种获得方式的互斥量
* shared_timed_mutex：允许共享和独占两种获得方式的、允许锁定超时的互斥量


`<mutex>` 头文件中也定义了锁的 RAII 包装类，如我们上面用过的 `lock_guard`

为了避免手动加锁、解锁的麻烦，以及在有异常或出错返回时发生漏解锁，我们一般应当使用 `lock_guard`，而不是手工调用互斥量的 lock 和 unlock 方法

C++ 里另外还有 `unique_lock`（C++11）和 `scoped_lock`（C++17），提供了更多的功能