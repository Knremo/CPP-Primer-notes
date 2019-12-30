#include <iostream>
#include <string>
#include <set>

using namespace std;

class Folder;

class Message
{
    friend class Folder;
    friend void swap(Message&, Message&);
public:
    explicit Message(const string &str = ""):
        contents(str) { }
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();

    void save(Folder&);
    void remove(Folder&);
private:
    string contents;
    set<Folder*> folders;  // 包含此Message的Folder

    void add_to_Folders(const Message&);
    void remove_from_Folders();
};

class Folder
{
public:
    Folder() { }

    void addMsg(const Message*);
    void remMsg(const Message*);
private:
    set<Message*> messages;
};

void Message::save(Folder &f)
{
    folders.insert(&f); // Folder添加到set
    f.addMsg(this); // Message添加到f
}
void Message::remove(Folder &f)
{
    folders.erase(&f); // 
    f.remMsg(this);
}
void Message::add_to_Folders(const Message &m)
{
    for (auto f : m.folders)
        f->addMsg(this);
}
Message::Message(const Message &m):
    contents(m.contents), folders(m.folders)
{
    add_to_Folders(m);
}
void Message::remove_from_Folders()
{
    for (auto f : folders)
        f->remMsg(this);
}
Message::~Message()
{
    remove_from_Folders();
}
Message& Message::operator=(const Message &rhs)
{
    remove_from_Folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(rhs);
    return *this;
}
void swap(Message &lhs, Message &rhs)
{
    using std::swap;
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}

