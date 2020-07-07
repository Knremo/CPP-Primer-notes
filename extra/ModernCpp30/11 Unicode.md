# 1. 历史
ASCII

代码页（code page）:

ISO646, ISO8859

GB2312 最早的中文字符集标准 1980年 6763个常用汉字

我们平时会用到编码 GB2312，其实更正确的名字是 EUC-CN，它是一种与 ASCII 兼容的编码方式。它用单字节表示 ASCII 字符而用双字节表示 GB2312 中的字符；由于 GB2312 中本身也含有 ASCII 中包含的字符，在使用中逐渐就形成了“半角”和“全角”的区别

GBK 是中文版 Windows 使用的标准编码方式

# 2. Unicode
Unicode 的编码点是从 0x0 到 0x10FFFF，一共 1,114,112 个位置。一般用“U+”后面跟 16 进制的数值来表示一个 Unicode 字符

## Unicode 字符的常见编码方式有：
* UTF-32: 32bit ,是编码点的直接映射
* UTF-16: 对于从 U+0000 到 U+FFFF 的字符，使用 16 比特的直接映射；对于大于 U+FFFF 的字符，使用 32 比特的特殊映射关系——在 Unicode 的 16 比特编码点中 0xD800–0xDFFF 是一段空隙，使得这种变长编码成为可能。在一个 UTF-16 的序列中，如果看到内容是 0xD800–0xDBFF，那这就是 32 比特编码的前 16 比特；如果看到内容是 0xDC00–0xDFFF，那这是 32 比特编码的后 16 比特；如果内容在 0xD800–0xDFFF 之外，那就是一个 16 比特的映射。
* UTF-8: 1 到 4 字节的变长编码。在一个合法的 UTF-8 的序列中，如果看到一个字节的最高位是 0，那就是一个单字节的 Unicode 字符；如果一个字节的最高两比特是 10，那这是一个 Unicode 字符在编码后的后续字节；否则，这就是一个 Unicode 字符在编码后的首字节，且最高位开始连续 1 的个数表示了这个字符按 UTF-8 的方式编码有几个字节。 

### UTF-16 对大于 U+FFFF 的算法：
1. 从代码点 U 中减去 0x10000，得到 U'，这样 U+10000～U+10FFFF 就变成了 0x00000～0x0FFFF。 
2. 用 20 位二进制数表示 U'， U'=yyyyyyyyyyxxxxxxxxxx 
3. 将前 10 位和后 10 位用 W1 和 W2 表示，W1=110110yyyyyyyyyy，W2=110111xxxxxxxxxx，则 W1 = D800～DBFF，W2 = DC00～DFFF。

## BOM
* 如果文件开头是 0x00 00 FE FF，那这是大头在前的 UTF-32 编码；
* 否则如果文件开头是 0xFF FE 00 00，那这是小头在前的 UTF-32 编码；
* 否则如果文件开头是 0xFE FF，那这是大头在前的 UTF-16 编码；
* 否则如果文件开头是 0xFF FE，那这是小头在前的 UTF-16 编码（注意，这条规则和第二条的顺序不能相反）；
* 否则如果文件开头是 0xEF BB BF，那这是 UTF-8 编码；
* 否则，编码方式使用其他算法来确定。

# 3. C++ 中的 Unicode 字符类型
* C++98 char 和 wchar_t, char 单字节，wchar_t 长度不确定，Windows 上是双字节，只能代表 UTF-16， 而在 Unix 上一般是四字节，可以代表 UTF-32
* C++11 char16_t, char32_t 两个独立的字符类型，代表 UTF-16 和 UTF-32
* C++20 char8_t, 区分可能使用传统编码的窄字符类型和 UTF-8
* string，wstring, u16string, u32string, u8string
* 窄字符字面量("hi"), 宽字符字面量(L"hi"), UTF-8, UTF-16, UTF-32 字面量(u8"hi", u"hi", U"hi")
* Unicode 换码序列，(U"\u6C49\u0001F600")

UTF32 到其他两种 UTF 编码的转换：
```c++
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

const char32_t unicode_max = 0x10FFFF;

void to_utf_16(char32_t ch, u16string& result)
{
    if (ch > unicode_max) {
        throw runtime_error("invalid code point");
    }
    if (ch < 0x10000) {
        result +=char16_t(ch);
    } else {
        char16_t first = 0xD800 | ((ch - 0x10000) >> 10);
        char16_t second = 0xDC00 | (ch & 0x3FF);
        result += first;
        result += second;
    }
}

void to_utf_8(char32_t ch, string& result)
{
    if (ch < 0x80) { // 单字节
        result += ch; 
    } else if (ch < 0x800) { // 
        result += 0xC0 | (ch >> 6);
        result += 0x80 | (ch & 0x3F);
    } else if (ch < 0x10000) {
        result += 0xE0 | (ch >> 12); 
        result += 0x80 | ((ch >> 6) & 0x3F); 
        result += 0x80 | (ch & 0x3F); 
    } else { 
        result += 0xF0 | (ch >> 18); 
        result += 0x80 | ((ch >> 12) & 0x3F); 
        result += 0x80 | ((ch >> 6) & 0x3F); 
        result += 0x80 | (ch & 0x3F);
    }
}

int main(){  
    char32_t str[] = U" \u6C49\U0001F600";
    u16string u16str;
    string u8str;
    for (auto ch : str) {    
        if (ch == 0) {      
            break;
        }    
        to_utf_16(ch, u16str); 
        to_utf_8(ch, u8str);
    }
    cout << hex << setfill('0');
    for (char16_t ch : u16str) { 
        cout << setw(4) << unsigned(ch) << ' ';
    }
    cout << endl;
    for (unsigned char ch : u8str) {
        cout << setw(2) << unsigned(ch) << ' ';
    }
    cout << endl;
}
```

## 平台区别
### Unix
linux, macOS  UTF-8

一般直接使用 char[] 和 string 来代表 UTF-8 字符串，包括输入、输出和文件名，非常简单

### Windows
一直用 char 表示传统编码（如，英文 Windows 上是 Windows-1252，简体中文 Windows 上是 GBK），用 wchar_t 表示 UTF-16

微软的编译器会把源代码里窄字符串字面量中的非 ASCII 字符转换成传统编码
```c++
#include <stdio.h>

template <typename T>
void dump(const T& str)
{
    for (char ch : str) {
        printf("%.2x", static_cast<unsigned char>(ch));
    }
    putchar('\n')
}

int main()
{
    char str[] = "你好";
    char u8str[] = u8"你好";
    dump(str);
    dump(u8str);
}
```
结果：
> c4 e3 ba c3 00 // GBK
> e4 bd a0 e5 a5 bd 00 // UTF-8

## 编程支持
### Windows API
`#include <windows.h>`
 MultiByteToWideChar()，从某个编码转到 UTF-16
 Windows 也提供了反向的 WideCharToMultiByte()，从 UTF-16 转到某个编码

### iconv
Unix 下最常用的底层编码转换接口是 iconv，提供 iconv_open、iconv_close 和 iconv 三个函数。这同样是 C 接口，实践中应该封装一下

### ICU4C
ICU 是一个完整的 Unicode 支持库，提供大量的方法，ICU4C 是其 C/C++ 的版本。ICU 有专门的字符串类型，内码是 UTF-16，但可以直接用于 IO streams 的输出。下面的程序应该在所有平台上都有同样的输出（但在 Windows 上要求当前系统传统编码能支持待输出的字符）：
```c++
#include <iostream>
#include <string>
#include <unicode/unistr.h>
#include <unicode/ustream.h>

using namespace std;
using icu::UnicodeString;

int main()
{
  auto str = UnicodeString::fromUTF8(
    u8"你好");
  cout << str << endl;
  string u8str;
  str.toUTF8String(u8str);
  cout << "In UTF-8 it is "
       << u8str.size() << " bytes"
       << endl;
}
```