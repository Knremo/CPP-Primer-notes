#include <iostream>
#include <string>
#include <set>

using namespace std;

class Folder;

class Message
{
    friend class Folder;
    friend void swap(Message&, Message&); // swap交换后处理指针指向新的
    friend void swap(Folder&, Folder&);
public:
    explicit Message(const string &str = ""):
        contents(str) { }
    Message(const Message&); // 将新的Message加入原有的所有Folder
    Message& operator=(const Message&); // 销毁原来的，拷贝数据，再把this添加到每个Folder
    ~Message(); // remove_from_Folders();

    void save(Folder&); // 将一个Folder加入到Message的指针set，然后把this添加到那个Folder的set
    void remove(Folder&); // 互相删除

    void info();
private:
    string contents;
    set<Folder*> folders;  // 包含此Message的Folder

    void add_to_Folders(const Message&); // 把this添加到m的folders中的每个
    void remove_from_Folders(); // 每个Folder删除该Message
};

class Folder
{
    friend void swap(Folder&, Folder&);
    friend class Message;
public:
    Folder(const string &str = "DEFAULT"):
        title(str) { }
    Folder(const Folder&);
    Folder& operator=(const Folder&);
    ~Folder();

    void addMsg(Message*);
    void remMsg(Message*);

    void info();
private:
    string title;
    set<Message*> messages;

    void remove_from_messages();
    void add_to_messages();
};

void Message::save(Folder &f)
{
    folders.insert(&f); // Folder添加到set
    f.addMsg(this); // Message添加到f
}
void Message::remove(Folder &f)
{
    folders.erase(&f); // 从set删除指定Folder指针
    f.remMsg(this); // 从Folder删除this
}
void Message::add_to_Folders(const Message &m) // 把this添加到m的folders中的每个
{
    for (auto f : m.folders)
        f->addMsg(this);
}
Message::Message(const Message &m):
    contents(m.contents), folders(m.folders)
{
    add_to_Folders(m);
}
void Message::remove_from_Folders() // 每个Folder删除该Message
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
    for (auto f : lhs.folders) //指针从原来的Folder删除
        f->remMsg(&lhs);
    for (auto f : rhs.folders) //指针从原来的Folder删除
        f->remMsg(&rhs);
    swap(lhs.folders, rhs.folders); // 交换数据成员
    swap(lhs.contents, rhs.contents);
    for (auto f : lhs.folders) // 重新添加指针
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}
void Message::info()
{
    cout << "* " << contents << " : " << endl;
    cout << " -" << " folders: ";
    for (auto f : folders)
        cout << f->title << " ";
}





void Folder::addMsg(Message *m)
{
    messages.insert(m);
}
void Folder::remMsg(Message *m)
{
    messages.erase(m);
}
Folder::Folder(const Folder &f):
    title(f.title), messages(f.messages)
{
    add_to_messages();
}
Folder& Folder::operator=(const Folder& rhs)
{
    remove_from_messages();
    title = rhs.title;
    messages = rhs.messages;
    add_to_messages();
    return *this;
}
void Folder::remove_from_messages()
{
    for (auto m : messages)
        m->remove(*this);    
}
void Folder::add_to_messages()
{
    for (auto m : messages)
        m->save(*this);    
}
Folder::~Folder()
{
    remove_from_messages();
}
void swap(Folder& lhs, Folder& rhs)
{
    using std::swap;
    for (auto m : lhs.messages)
        m->folders.erase(&lhs);
    for (auto m : rhs.messages)
        m->folders.erase(&rhs);
    swap(lhs.title, rhs.title);
    swap(lhs.messages, rhs.messages);
    for (auto m : lhs.messages)
        m->folders.insert(&lhs);
    for (auto m : rhs.messages)
        m->folders.insert(&rhs);
}
void Folder::info()
{
    cout << "******* Folder: " << title 
         << " *******" << endl;
    for (auto m : messages)
        cout << m->contents << "--> " << m->folders.size() << endl;
}

void test()
{
    Message* pm1 = new Message("m1");
    Message* pm2 = new Message("m2");
    Message* pm3 = new Message("m3");
    Folder f1("f1"), f2("f2");

    pm1->save(f1);
    pm2->save(f1);
    pm2->save(f2);
    pm3->save(f2);

    f1.info();
    f2.info();

    pm2->info();

    delete pm1, pm2, pm3;
}

int main()
{
    test();

    return 0;
}

//快乐！