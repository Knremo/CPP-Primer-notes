#include <memory>
#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>
#include <iostream>
//12.1
class StrBlob
{
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    explicit StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const std::string &t) {data->push_back(t);}
    void pop_back();
    std::string& front();
    std::string& back();
private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const;
};
//构造函数
StrBlob::StrBlob(): data(std::make_shared<std::vector<std::string>>()) {}
StrBlob::StrBlob(std::initializer_list<std::string> il): data(std::make_shared<std::vector<std::string>>(il)) {}
//元素访问检查
void StrBlob::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}
std::string& StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}
std::string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}
void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    return data->pop_back();
}
void f1()
{
    StrBlob b1;
    StrBlob b2({"a", "an", "the"});
    b1 = b2;
    b2.push_back("about");

    std::cout << b1.size() << " " << b2.size();
}

// 12.2
/*
std::string& StrBlob::front() const
{
    check(0, "front on empty StrBlob");
    return data->front();
}
std::string& StrcBlob::back() const
{
    check(0, "back on empty StrBlob");
    return data->back();
}
*/

//12.3
//no

//

//12.5
//不能StrBlob b2 = {"a", "an", "the"};
//只能StrBlob b2({"a", "an", "the"});

int main()
{
    f1();

    return 0;
}