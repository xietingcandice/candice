#include <iostream>
#include <string>
#include <set>

using namespace std;

class Message;  //<��Ҫ��������������Folder��ʹ��
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
	Message (const string &str = ""):contents(str){};   //<���ƹ��캯������ʼ���б�
	Message (const Message &); //<���캯��
	Message &operator= (const Message &); //<��ֵ������
	~Message();

	void save(Folder &);
	void remove(Folder &);
	void addFldr(Folder *);
	void remFldr(Folder *);
private:
	string contents;
	set<Folder *> folders;
	void put_Msg_in_Folders(const set<Folder *> &rhs);//����Message��һ��������ӵ�ָ�����Message�ĸ�Folder��
	void remove_Msg_from_Folders();//��folders��Ա��ÿ��Folder��ɾ��ָ�����Message��ָ��

};
void Message::save(Folder &f)
{
	folders.insert(&f);//<����message��ӦĿ¼
	f.addMsg(this);    //<����Ŀ¼�ж�Ӧ�Ĵ���Ŀ¼
}
void Message::remove(Folder &f)
{
	folders.erase(&f); //<ɾ������Ϣ��Ӧ�����Ŀ¼ ��folders��������Ϣ��Ӧ��Ŀ¼����
	f.remMsg(this);    //<ɾ�����Ŀ¼�ж�Ӧ�Ĵ�������
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
		(*beg)->addMsg(this); //<�ڶ�Ӧ��Ŀ¼�м���������Ϣ
	}
}
void Message::remove_Msg_from_Folders() //<�ڶ���Ŀ¼��ɾ��������Ϣ
{
	for (set<Folder *>::const_iterator beg = folders.begin(); beg != folders.end(); ++beg)
	{
		(*beg)->remMsg(this);
	}
}
/************************************************************************/
/* ��ֵʱ��ɾ���������,���ڳ�����������ĳ�Ա֮��,
���Ҳ������ĳ�Ա��ֵ�������������Ӧ��Ա��
�����������ͬ��,������������ĳ�ԱҲ�������Ҳ������ĳ�Ա!                                                                     */
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
/* ϵͳ�Զ�����string���������ͷ�contents,
�Զ�����set��������������ڱ���folders��Ա���ڴ�,
���,Message��������ΨһҪ�����ǵ���remove_Msg_from_Folders                                                                     */
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