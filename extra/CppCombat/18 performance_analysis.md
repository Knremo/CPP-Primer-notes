运行阶段能做、应该做的事情主要有三件：调试（Debug）、测试（Test）和性能分析（Performance Profiling）

# top
一个是按“M”，看内存占用（RES/MEM），另一个是按“P”，看 CPU 占用，这两个都会从大到小自动排序，方便你找出最耗费资源的进程

**pstack 和 strace**

pstack 可以打印出进程的调用栈信息，有点像是给正在运行的进程拍了个快照，你能看到某个时刻的进程里调用的函数和关系，对进程的运行有个初步的印象

pstack 显示的只是进程的一个“静态截面”，信息量还是有点少，而 strace 可以显示出进程的正在运行的系统调用，实时查看进程与系统内核交换了哪些信息

**perf**

`perf top -K -p xxx` 按 CPU 使用率排序，只看用户空间的调用

# Google Performance Tools
```
apt-get install google-perftools
apt-get install libgoogle-perftools-dev
```
gperftools 的性能分析工具有 CPUProfiler 和 HeapProfiler 两种，用来分析 CPU 和内存

它的用法也比较简单，只需要在源码里添加三个函数：
* ProfilerStart()，开始性能分析，把数据存入指定的文件里；
* ProfilerRegisterThread()，允许对线程做性能分析；
* ProfilerStop()，停止性能分析。

只要把想做性能分析的代码“夹”在这三个函数之间就行，运行起来后，gperftools 就会自动产生分析数据

为了写起来方便，我用 shared_ptr 实现一个自动管理功能。这里利用了 void* 和空指针，可以在智能指针析构的时候执行任意代码（简单的 RAII 惯用法）：
```cpp
auto make_cpu_profiler =            // lambda表达式启动性能分析
[](const string& filename)          // 传入性能分析的数据文件名
{
  ProfilerStart(filename.c_str());  // 启动性能分析
  ProfilerRegisterThread();         // 对线程做性能分析

  return std::shared_ptr<void>(     // 返回智能指针
    nullptr,                        // 空指针，只用来占位
    [](void*){                      // 删除函数执行停止动作
        ProfilerStop();             // 停止性能分析
    }   
  );  
};
```
测试正则表达式处理文本的性能：
```cpp
auto cp = make_cpu_profiler("case1.perf");     // 启动性能分析
auto str = "neir:automata"s;

for(int i = 0; i < 1000; i++) {               // 循环一千次
  auto reg  = make_regex(R"(^(\w+)\:(\w+)$)");// 正则表达式对象
  auto what = make_match();

  assert(regex_match(str, what, reg));        // 正则匹配
}
```
case1.perf 里面就是 gperftools 的分析数据，但它是二进制的，不能直接查看，如果想要获得可读的信息，还需要另外一个工具脚本 pprof

pprof 脚本并不含在 apt-get 的安装包里，所以，你还要从GitHub上下载源码，然后用“--text”选项，就可以输出文本形式的分析报告：
```
git clone git@github.com:gperftools/gperftools.git

pprof --text ./a.out case1.perf > case1.txt

Total: 72 samples
  4   5.6%   5.6%   4   5.6% __gnu_cxx::__normal_iterator::base
  4   5.6%  11.1%   4   5.6% _init
  4   5.6%  16.7%   4   5.6% std::vector::begin
  3   4.2%  20.8%   4   5.6% __gnu_cxx::operator-
  3   4.2%  25.0%   5   6.9% std::__distance
  2   2.8%  27.8%   2   2.8% __GI___strnlen
  2   2.8%  30.6%   6   8.3% __GI___strxfrm_l
  2   2.8%  33.3%   3   4.2% __dynamic_cast
  2   2.8%  36.1%   2   2.8% __memset_sse2
  2   2.8%  38.9%   2   2.8% operator new[]
```
pprof 也能输出图形化的分析报告，支持有向图和火焰图，需要你提前安装 Graphviz 和 FlameGraph：
```
pprof --svg ./a.out case1.perf > case1.svg

pprof --collapsed ./a.out case1.perf > case1.cbt
flamegraph.pl case1.cbt > flame.svg
flamegraph.pl --invert --color aqua case1.cbt > icicle.svg
```

# valgrind

# fsanitize=address
GCC/Clang 内置了Google开发的Sanitizer工具，编译时使用 `fsanitize=address` 就可以检查可能存在的内存泄漏

