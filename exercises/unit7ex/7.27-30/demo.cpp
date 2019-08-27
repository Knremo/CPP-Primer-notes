#include <string>
#include <iostream>

class Screen
{
public:
    using pos = std::string::size_type;

    Screen() = default;
    Screen(pos ht, pos wd): height(ht), width(wd), contents(ht * wd, ' ') {}
    Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht * wd, c) {}
    
    Screen &move(pos r, pos c)
    {
        pos row = r * width;
        cursor = row + c;
        return *this;
    }
    
    char get() const {return contents[cursor];}
    char get(pos ht, pos wd) const
    {
        pos row = ht * width;
        return contents[row + wd];
    }

    Screen &set(char c)
    {
        contents[cursor] = c;
        return *this;
    }
    Screen &set(pos r, pos col, char ch)
    {
        contents[r * width + col] = ch;
        return *this;
    }

    Screen &display(std::ostream &os)
    {
        do_display(os);
        return *this;
    }
    const Screen &display(std::ostream &os) const
    {
        do_display(os);
        return *this;
    }
private:
    pos height = 0, width = 0;
    pos cursor = 0;
    std::string contents;

    void do_display(std::ostream &os) const {os << contents;}
};

int main()
{
    // 7.27
    Screen myScreen(5, 5, 'X');
    myScreen.move(4, 0).set('#').display(std::cout);
    std::cout << "\n";
    myScreen.display(std::cout);
    std::cout << "\n";

    const Screen constScreen(4, 4, '-');
    constScreen.display(std::cout);

    //7.28
    //第2个display不会有改变的字符

    //7.29

    //7.30
    return 0;
}
