# 8.1 IO类
```
iostream头文件
istream, wistream从流读取数据
ostream, wostream向流写入数据
isotream, wiostream读写流

fstream
ifstream, wifstream从文件读取数据
ofstream, wofstream向文件写入数据
fstream, wfstream读写文件

sstream
istringstream, wistringstream从string读取数据
ostringstream, wostringstream向string写入数据
stringstream, wstringstream读写string
```
## 8.1.1 IO对象无拷贝或赋值
不能将形参或者返回类型设置为流类型

以引用方式传递和返回流，不能是const

## 8.1.2 条件状态
```
strm::iostate  //IO类型,表达条件状态

strm::badbit   //const std::ios_base::iostate, 指出流已崩溃
strm::failbit  //指出一个IO操作失败了
strm::eofbit   //流到达了文件结束
strm::goodbit  //流未处于错误状态  ==0

s.eof() //若s的eofbit置位，则返回true
s.fail()
s.bad()
s.good()

s.clear() //复位所有状态位，返回void
s.clear(flags) //
s.setstate(flags)
s.rdstate() //返回s条件状态，类型为strm::iostate
```
到达文件结束位置,eofbit和failbit都会被置位

badbit,failbit,eofbit任一置位,`cin >> word`就会失败

清楚标志位
```c++
auto old_state = cin.rdstate();
cin.clear();
process_input(cin);
cin.setstate(old_state);
```

复位failbit,badbit,保持eofbit
```c++
cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit) ;
```
## 8.1.3 管理输出缓冲

###刷新输出缓冲区
```c++
cout << "hi!" << endl; //输出hi和换行，刷新缓冲区
cout << "hi!" << flush; //只刷新
cout << "hi!" << ends; //一个空字符加刷新
```
### unitbuf操纵符
告诉流接下来每次写都刷新，nounitbuf重置
```c++
cout << unitbuf;
//
cout << nounitbuf;
```
### 关联输入和输出流
一个输入流被关联到一个输出流时，任何试图从输入流读取数据都会先刷新输出流

每个流最多同时关联到一个流，但多个流可以同时关联到同一个ostream

```c++
cin.tie();  //不带参数，返回指向关联流的指针，如果没有则返回空指针

cin.tie(&cout); //带参数，关联到流。cin与cout默认已关联

ostream *old_tie = cin.tie(nullptr);
cin.tie(&cerr);
cin.tie(old_tie);
```

# 8.2 文件输入输出
fstream
```c++
fstream fstrm; //创建一个未绑定的文件流
fstream fstrm(s); //创建打开s, s可以是string或C风格字符串指针
fstream fstrm(s, mode); //指定mode
fstrm.open(s) //打开并绑定，返回void
fstrm.close() //close
fstrm.is_open() //bool,是否成功打开尚未关闭
```
## 8.2.1 使用文件流对象
```c++
ifstream in(ifile);
ofstream out;
```
### open和close
```c++
ifstream in(ifile);
ofstream out;
out.open(ifile + ".copy");

if(out)
    ···
```



