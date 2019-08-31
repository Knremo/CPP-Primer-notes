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


