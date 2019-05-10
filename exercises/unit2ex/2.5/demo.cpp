#include <typeinfo>
#include <iostream>

int main()
{
    std::cout << "'a' --> " << typeid('a').name() << "(char)"
              << " " << sizeof('a') << " bytes." << std::endl;
    std::cout << "L'a' --> " << typeid(L'a').name() << "(wchar_t)"
              << " " << sizeof(L'a') << " bytes." << std::endl;
    std::cout << "\"a\" --> " << typeid("a").name() << "(char array 2x1)"
              << " " << sizeof("a") << " bytes." << std::endl;
    std::cout << "L\"a\" --> " << typeid(L"a").name() << "(wchar_t array 2x1)"
              << " " << sizeof(L"a") << " bytes." << std::endl;

    std::cout << "u'a' --> " << typeid(u'a').name() << "(char16_t)"
              << " " << sizeof(u'a') << " bytes." << std::endl;
    std::cout << "u\"a\" --> " << typeid(u"a").name() << "(char16_t array 2x1)"
              << " " << sizeof(u"a") << " bytes." << std::endl;
    std::cout << "u\"想你\" --> " << typeid(u"想你").name() << "(char16_t array 3x1)"
              << " " << sizeof(u"想你") << " bytes." << std::endl;

    std::cout << "U'a' --> " << typeid(U'a').name() << "(char32_t)"
              << " " << sizeof(U'a') << " bytes." << std::endl;
    std::cout << "U\"a\" --> " << typeid(U"a").name() << "(char32_t array 2x1)"
              << " " << sizeof(U"a") << " bytes." << std::endl;
    std::cout << "U\"煎熬\" --> " << typeid(U"煎熬").name() << "(char32_t array 3x1)"
              << " " << sizeof(U"煎熬") << " bytes." << std::endl;

    std::cout << "u8\"a\" --> " << typeid(u8"a").name() << "(char array 2x1)"
              << " " << sizeof(u8"a") << " bytes." << std::endl;
    std::cout << "u8\"我的\" --> " << typeid(u8"我的").name() << "(char array 7x1)"
              << " " << sizeof(u8"我的") << " bytes." << std::endl;

    std::cout << "\"\u5929\u624d\" --> " << typeid("\u5929\u624d").name() << "(char array 7x1)"
              << " " << sizeof("\u5929\u624d") << " bytes." << std::endl;

    std::cout << "10 --> " << typeid(10).name() << "(int)"
              << " " << sizeof(10) << " bytes." << std::endl;
    std::cout << "10u --> " << typeid(10u).name() << "(unsigned int)"
              << " " << sizeof(10u) << " bytes." << std::endl;
    std::cout << "10uL --> " << typeid(10uL).name() << "(unsigned long)"
              << " " << sizeof(10uL) << " bytes." << std::endl;
    std::cout << "012 --> " << typeid(012).name() << "(int)"
              << " " << sizeof(012) << " bytes." << std::endl;
    std::cout << "0xC --> " << typeid(0xC).name() << "(int)"
              << " " << sizeof(0xC) << " bytes." << std::endl;

    long l = 12345;
    long long ll = 12345;
    short s = 10;
    std::cout << "long --> " << typeid(l).name() << "(long)"
              << " " << sizeof(l) << " bytes." << std::endl;
    std::cout << "long long --> " << typeid(ll).name() << "(long long)"
              << " " << sizeof(ll) << " bytes." << std::endl;
    std::cout << "short --> " << typeid(s).name() << "(short)"
              << " " << sizeof(s) << " bytes." << std::endl;

    std::cout << "3.14 --> " << typeid(3.14).name() << "(double)"
              << " " << sizeof(3.14) << " bytes." << std::endl;
    std::cout << "3.14F --> " << typeid(3.14F).name() << "(float)"
              << " " << sizeof(3.14F) << " bytes." << std::endl;
    std::cout << "3.14L --> " << typeid(3.14L).name() << "(long double)"
              << " " << sizeof(3.14L) << " bytes." << std::endl;
    
    char i[3][4];
    std::cout << typeid(i).name() << std::endl;

    std::cout << "\145?\012E" << std::endl; //2.7

    std::cout << "2\tM\n133\tWDADA" << std::endl; //2.8
}
