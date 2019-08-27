#include <string>
#include <iostream>
#include <vector>

class Window_mgr
{
public:
    using ScreenIndex = std::vector<Screen>::size_type;

    void clear(ScreenIndex);
private:
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};

class Screen
{
    friend void Window_mgr::clear(ScreenIndex);
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

    //7.33
    pos size() const
    {
        return height * width;
    }
private:
    pos height = 0, width = 0;
    pos cursor = 0;
    std::string contents;

    void do_display(std::ostream &os) const {os << contents;}
};

void Window_mgr::clear(ScreenIndex i)
{
    Screen &s = screens[i];
    s.contents = std::string(s.height * s.width, ' ');
}