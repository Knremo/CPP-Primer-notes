# libcurl
easy: 同步调用
multi: 异步调用

使用 libcurl 收发 HTTP 数据的基本步骤有 4 个：
1. 使用 curl_easy_init() 创建一个句柄，类型是 CURL*。但我们完全没有必要关心句柄的类型，直接用 auto 推导就行。
2. 使用 curl_easy_setopt() 设置请求的各种参数，比如请求方法、URL、header/body 数据、超时、回调函数等。这是最关键的操作。
3. 使用 curl_easy_perform() 发送数据，返回的数据会由回调函数处理。
4. 使用 curl_easy_cleanup() 清理句柄相关的资源，结束会话。
```cpp
#include <curl/curl.h>
auto curl = curl_easy_init();
assert(curl);
curl_easy_setopt(curl, CURLOPT_URL, "http://nginx.org");
auto res = curl_easy_perform(curl);
if (res != CURLE_OK) {
    cout << curl_easy_strerror(res) << endl;
}

curl_easy_cleanup(curl);
```
没有设置回调函数，所以 libcurl 会使用内部的默认回调，把得到的 HTTP 响应数据输出到标准流

因为 libcurl 是 C 语言实现的，所以回调函数必须是函数指针.**无捕获的 lambda 表达式可以显式转换成一个函数指针**

```cpp
size_t write_callback(char*, size_t, size_t, void*); // 回调函数原型

curl_easy_setopt(curl, CURLOPT_WRITTEFUNCTION, 
    (decltype(&write_callback))
    [](char *ptr, size_t size, size_t nmemb, void *userdata)
    {
        cout << "size = " << size * nmemb << endl;
        return size * nmemb;
    });
```

# cpr
一句话就能发送 HTTP 请求：
```cpp
#include <cpr/cpr.h>                            // 包含头文件

auto res = cpr::Get(                           // GET请求    
           cpr::Url{"http://openresty.org"}   // 传递URL
);

cout << res.elapsed << endl;            // 请求耗费的时间

cout << res.url << endl;               // 请求的URL
cout << res.status_code << endl;       // 响应的状态码
cout << res.text.length() << endl;     // 响应的body数据

for(auto& x : res.header) {            // 响应的头字段
    cout << x.first << "=>"            // 类似map的结构
         << x.second << endl;
}
```
HTTP 协议的概念都被实现为相应的函数或者类，内部再转化为 libcurl 操作，主要的有：
* GET/HEAD/POST 等请求方法，使用同名的 Get/Head/Post 函数；
* URL 使用 Url 类，它其实是 string 的别名；
* URL 参数使用 Parameters 类，KV 结构，近似 map；
* 请求头字段使用 Header 类，它其实是 map 的别名，使用定制的函数实现了大小写无关比较；
* Cookie 使用 Cookies 类，也是 KV 结构，近似 map；
* 请求体使用 Body 类；
* 超时设置使用 Timeout 类

```cpp
const auto url = "http://openresty.org"s;  // 访问的URL

auto res1 = cpr::Head(                    // 发送HEAD请求
            cpr::Url{url}                 // 传递URL
);

auto res2 = cpr::Get(                     // 发送GET请求
            cpr::Url{url},               // 传递URL
            cpr::Parameters{             // 传递URL参数
                {"a", "1"}, {"b", "2"}}
);

auto res3 = cpr::Post(                  // 发送POST请求
            cpr::Url{url},             // 传递URL
            cpr::Header{                // 定制请求头字段
              {"x", "xxx"},{"expect",""}},
            cpr::Body{"post data"},    // 传递body数据
            cpr::Timeout{200ms}       // 超时时间
);
```
cpr 也支持异步处理:
```cpp
auto f = cpr::GetAsync(                    // 异步发送GET请求
            cpr::Url{"http://openresty.org"}
);

auto res = f.get();                       // 等待响应结果
cout << res.elapsed << endl;              // 请求耗费的时间
```

# ZMQ
 5 种模式：
 * 原生模式（RAW），没有消息队列功能，相当于底层 Socket 的简单封装；
 * 结对模式（PAIR），两个端点一对一通信；
 * 请求响应模式（REQ-REP），也是两个端点一对一通信，但请求必须有响应；
 * 发布订阅模式（PUB-SUB），一对多通信，一个端点发布消息，多个端点接收处理；
 * 管道模式（PUSH-PULL），或者叫流水线，可以一对多，也可以多对一。

在 ZMQ 里有两个基本的类。
* 第一个是 context_t，它是 ZMQ 的运行环境。使用 ZMQ 的任何功能前，必须要先创建它。
* 第二个是 socket_t，表示 ZMQ 的套接字，需要指定刚才说的那 5 种工作模式。注意它与原生 Socket 没有任何关系，只是借用了名字来方便理解。
```cpp
const auto thread_num = 1;              // 并发线程数

zmq::context_t context(thread_num);     // ZMQ环境变量

auto make_sock = [&](auto mode)        // 定义一个lambda表达式
{
    return zmq::socket_t(context, mode); // 创建ZMQ套接字
};
```
* TCP 通信地址的形式是“tcp://…”，指定 IP 地址和端口号；
* 进程内通信地址的形式是“inproc://…”，指定一个本地可访问的路径；
* 进程间通信地址的形式是“ipc://…”，也是一个本地可访问的路径。

```cpp
const auto addr = "ipc:///dev/shm/zmq.sock"s;  // 通信地址

auto receiver = [=]()                     // lambda表达式接收数据
{
    auto sock = make_sock(ZMQ_PULL);      // 创建ZMQ套接字，拉数据

    sock.bind(addr);                     // 绑定套接字
    assert(sock.connected());

    zmq::message_t msg;
    sock.recv(&msg);                      // 接收消息

    string s = {msg.data<char>(), msg.size()};
    cout << s << endl;
};

auto sender = [=]()                     // lambda表达式发送数据
{
    auto sock = make_sock(ZMQ_PUSH);     // 创建ZMQ套接字，推数据

    sock.connect(addr);                  // 连接到对端
    assert(sock.connected());

    string s = "hello zmq";
    sock.send(s.data(), s.size());       // 发送消息
};
```
* **ZMQ 环境的线程数**。它的默认值是 1，太小了，适当增大一些就可以提高 ZMQ 的并发处理能力。我一般用的是 4~6，具体设置为多少最好还是通过性能测试来验证下。
* **收发消息时的本地缓存数量**，ZMQ 的术语叫 High Water Mark。如果收发的数据过多，数量超过 HWM，ZMQ 要么阻塞，要么丢弃消息。
```cpp
sock.setsockopt(ZMQ_RCVHWM, 1000);     // 接收消息最多缓存1000条
sock.setsockopt(ZMQ_SNDHWM, 100);      // 发送消息最多缓存100条
```