#include <iostream>
#include <string>
#include <set>

using namespace std;

class Message;  //<需要先声明，才能在Folder中使用
class Folder
{
	Folder(){};
	~Folder();
	void addMsg(Message *);
	void remMsg(Message *);
private:
	set<Message *> messages;
	void remove_Fldr_form_Messages();

};
class Message
{
public:
	Message (const string &str = ""):contents(str){};   //<复制构造函数，初始化列表
	Message (const Message &); //<构造函数
	Message &operator= (const Message &); //<赋值操作符
	~Message();

	void save(Folder &);
	void remove(Folder &);
	void addFldr(Folder *);
	void remFldr(Folder *);
private:
	string contents;
	set<Folder *> folders;
	void put_Msg_in_Folders(const set<Folder *> &rhs);//自身Message的一个副本添加到指向给定Message的各Folder中
	void remove_Msg_from_Folders();//从folders成员的每个Folder中删除指向这个Message的指针

};
void Message::save(Folder &f)
{
	folders.insert(&f);//<更新message对应目录
	f.addMsg(this);    //<增加目录中对应的此条目录
}
void Message::remove(Folder &f)
{
	folders.erase(&f); //<删除此消息对应的这个目录 ，folders是这条消息对应的目录集合
	f.remMsg(this);    //<删除这个目录中对应的此条内容
}
void Message::addFldr(Folder *f)
{
	folders.insert(f);
}
void Message::remFldr(Folder *f)
{
	folders.erase(f);
}
void Message::put_Msg_in_Folders(const set<Folder *> &rhs)
{
	for (set<Folder *>::const_iterator beg = rhs.begin(); beg != rhs.end(); ++beg)
	{
		(*beg)->addMsg(this); //<在对应的目录中加入这条消息
	}
}
void Message::remove_Msg_from_Folders() //<在对饮目录中删除这条消息
{
	for (set<Folder *>::const_iterator beg = folders.begin(); beg != folders.end(); ++beg)
	{
		(*beg)->remMsg(this);
	}
}
/************************************************************************/
/* 赋值时需删除左操作数,并在撤销左操作数的成员之后,
将右操作数的成员赋值给左操作数的相应成员。
如果对象是相同的,则撤销左操作数的成员也将撤销右操作数的成员!                                                                     */
/************************************************************************/
Message& Message::operator=(const Message &rhs)
{
	if (&rhs != this)
	{
		remove_Msg_from_Folders();
		contents = rhs.contents;
		folders = rhs.folders;
		put_Msg_in_Folders(rhs.folders);
	}
	return * this;
}

/************************************************************************/
/* 系统自动调用string析构函数释放contents,
自动调用set析构函数清除用于保存folders成员的内存,
因此,Message析构函数唯一要做的是调用remove_Msg_from_Folders                                                                     */
/************************************************************************/
Message:: ~Message()
{
	remove_Msg_from_Folders();
}

//------------------------------------------------------------------------------------------
Folder::~Folder()
{
	remove_Fldr_form_Messages();
}
void Folder::addMsg(Message *rhs)
{
	messages.insert(rhs);
}
void Folder::remMsg(Message *rhs)
{
	messages.erase(rhs);
}
void Folder::remove_Fldr_form_Messages()  
{  
	for (std::set<Message *>::const_iterator beg = messages.begin();  
		beg != messages.end(); ++beg)  
	{  
		(*beg) -> remFldr(this);  
	}  
}  