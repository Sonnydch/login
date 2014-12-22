//loginSystem.h
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#include<conio.h>
class UserInfo{//�û���Ϣ��
public:
	UserInfo();//ȱʡ���캯��
	UserInfo(string id, string pw);//���ع��캯��
	~UserInfo();//��������
	string id()const;//��ȡ����û���id
	UserInfo *get_this();//��ȡָ������û��ڵ��ָ��
	void set_myPassword(string newpass);//���ø��û�������
	void set_myId(string newid);//���ø��û����˺�id
	string get_myPassword();//ȡ�ø��û�������
	void read(istream &in);//��ȡ���������Դ��ļ��У�Ҳ��������
	void write(ostream &out);//�������
	bool operator==(const UserInfo & user)const;//˫�Ⱥ�����
	bool operator<(const UserInfo & user)const;//С�ں�����
	bool operator>(const UserInfo & user)const;//���ں�����
	friend ostream & operator<<(ostream & out, UserInfo &user);//������Ԫ������������������������
	friend istream & operator>>(istream & in, UserInfo & user);//������Ԫ�������������������������
private:
	string myId,
		myPassword;
}; 

class Tree;
class TreeNode{//���нڵ���
public:
	TreeNode(UserInfo value);//���캯�����������Ϊһ������ΪUserInfo��ֵ
	UserInfo *getData();//��ȡָ��ýڵ��ָ��
	UserInfo data;//������һ��UserInfo�������
	int height;//�ڵ�ĸ߶�
	TreeNode * leftPtr;//�ڵ����ָ��
	TreeNode * rightPtr;//�ڵ����ָ��
};
class Tree//��ΪAVL����ƽ����
{
public:
	Tree();//Ĭ�Ϲ��캯��
	~Tree();//Ĭ����������
	TreeNode * treeSearch(UserInfo value);//������������ֵ��������ָ���ֵ��ָ�룬��������޸�ֵ������һ����ָ��
	void outputTree();//����ش�ӡ������ͼ��
	void insertTreeNode(UserInfo);//������ֵ
	void inOrederTraversal(ostream & out);//���������ӡ��
	void deleteValue(UserInfo);//ɾ���ڵ�
private:
	bool found;//�����ɾ���������Ƿ���ڴ��˻�������
	//�����ĸ�����Ϊ����ڵ�����ת��������ά������ƽ��
	void turnRight(TreeNode * &);//��������������ı�ýڵ��ָ������Ϊ���ã���ͬ
	void turnLeft(TreeNode* &);//��������
	void leftAndRight(TreeNode* &);//������������
	void rightAndLeft(TreeNode* &);//������������
	//ɾ���ڵ��������������
	void  deleteHelper1(TreeNode* &, UserInfo);
	UserInfo deleteHelper2(TreeNode* &);//���ص���һ��UserInfo���͵�ֵ��deleteHelper1����Ҫ�õ�
	int high(TreeNode*);	//�����ڵ�߶ȵĺ���
	int max(int s1, int s2);//���ؽڵ�߶Ƚϴ�ֵ�ĺ���
	//Ϊʵ�ֵݹ�ԭ����Ӧ�Ĺ��ߺ���
	void outputTreeHelper(TreeNode *, int);//���ݶ���������ĺ����ӡ��
	void destroyHelper(TreeNode *);//Ĭ�Ϲ��캯���ĸ�������
	TreeNode * searchHelper(TreeNode *, UserInfo);//��ѯ�����ĸ�������
	TreeNode * rootTreeNode;//���ĸ��ڵ�
	void insertHelper(TreeNode * &, UserInfo);//���뺯���ĸ�������
	void inHelper(ostream & out,TreeNode*);//���������������ĸ�������
};
class Menu{
public :
	Menu();//Ĭ�Ϲ��캯��
	~Menu();//Ĭ����������
	void set_mode_set_menu();//�����˵������趨�˵�ѡ��
	int get_menu();//��ȡ��ǰ�˵�ѡ��
	bool get_quit();//��ȡ�����Ƿ��˳�����Ĳ�������ֵ
	void set_userFile(string s);//�����趨�洢�û���Ϣ���ļ�����Ĭ��Ϊ���캯���ж����usersInfo.txt
	string get_userFile();//ȡ�ô洢�û���Ϣ���ļ���
	void check_from_file();//���ļ��ж�ȡ�û���Ϣ����ȷ���Ƿ���ڸ��û���������֤�ɹ��ɽ����޸�����ҳ�棬������ʾ��ע��
	void register_into_file_tree();//ע����棬��ʾ�û�ע�ᣬ������Ϣ�����ļ�
	void delete_from_file_tree();//ɾ�����棬���û���Ϣ���ļ���ɾ��
	void show_all_account();//��������Ա���棬���պ����ƽ������ӡ������
	void update_password(TreeNode * temp);//�޸��������
private:
	Tree userTree;//�����洢�û���Ϣ��һ����
	UserInfo user;//��Ҫ�õ�����ʱ�洢�û���Ϣ�ı���
	string mode;//��¼��������Ĳ˵�ѡ��
	bool quit;//��¼�Ƿ��˳�����
	int menu;//��¼�˵���ѡ��
	string userFile;//��ȡ�洢�û���½�˺�������Ϣ���ļ���,����ʱʹ�� usersInfo.txt ÿ���˻� �������������س�
};