//loginSystem.h
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#include<conio.h>
class UserInfo{//用户信息类
public:
	UserInfo();//缺省构造函数
	UserInfo(string id, string pw);//重载构造函数
	~UserInfo();//析构函数
	string id()const;//获取这个用户的id
	UserInfo *get_this();//获取指向这个用户节点的指针
	void set_myPassword(string newpass);//设置该用户的密码
	void set_myId(string newid);//设置该用户的账号id
	string get_myPassword();//取得该用户的密码
	void read(istream &in);//读取函数，可以从文件中，也可以输入
	void write(ostream &out);//输出函数
	bool operator==(const UserInfo & user)const;//双等号重载
	bool operator<(const UserInfo & user)const;//小于号重载
	bool operator>(const UserInfo & user)const;//大于号重载
	friend ostream & operator<<(ostream & out, UserInfo &user);//声明友元函数对输出流运算符进行重载
	friend istream & operator>>(istream & in, UserInfo & user);//声明友元函数对输入流运算符进行重载
private:
	string myId,
		myPassword;
}; 

class Tree;
class TreeNode{//树中节点类
public:
	TreeNode(UserInfo value);//构造函数，传入参数为一个类型为UserInfo的值
	UserInfo *getData();//获取指向该节点的指针
	UserInfo data;//数据是一个UserInfo类的数据
	int height;//节点的高度
	TreeNode * leftPtr;//节点的左指针
	TreeNode * rightPtr;//节点的右指针
};
class Tree//此为AVL二叉平衡树
{
public:
	Tree();//默认构造函数
	~Tree();//默认析构函数
	TreeNode * treeSearch(UserInfo value);//搜索二叉树的值，并返回指向该值的指针，如果树内无该值，返回一个空指针
	void outputTree();//形象地打印出树（图）
	void insertTreeNode(UserInfo);//插入数值
	void inOrederTraversal(ostream & out);//中序遍历打印树
	void deleteValue(UserInfo);//删除节点
private:
	bool found;//标记在删除操作中是否存在此账户及密码
	//以下四个函数为插入节点后的旋转函数，以维持树的平衡
	void turnRight(TreeNode * &);//右旋操作，必须改变该节点的指向，所以为引用，下同
	void turnLeft(TreeNode* &);//左旋操作
	void leftAndRight(TreeNode* &);//先左旋后右旋
	void rightAndLeft(TreeNode* &);//先右旋后左旋
	//删除节点的两个辅助函数
	void  deleteHelper1(TreeNode* &, UserInfo);
	UserInfo deleteHelper2(TreeNode* &);//返回的是一个UserInfo类型的值在deleteHelper1中需要用到
	int high(TreeNode*);	//测量节点高度的函数
	int max(int s1, int s2);//返回节点高度较大值的函数
	//为实现递归原理相应的工具函数
	void outputTreeHelper(TreeNode *, int);//根据二叉树形象的横向打印树
	void destroyHelper(TreeNode *);//默认构造函数的辅助函数
	TreeNode * searchHelper(TreeNode *, UserInfo);//查询函数的辅助函数
	TreeNode * rootTreeNode;//树的根节点
	void insertHelper(TreeNode * &, UserInfo);//插入函数的辅助函数
	void inHelper(ostream & out,TreeNode*);//中序遍历输出函数的辅助函数
};
class Menu{
public :
	Menu();//默认构造函数
	~Menu();//默认析构函数
	void set_mode_set_menu();//弹出菜单栏，设定菜单选项
	int get_menu();//获取当前菜单选项
	bool get_quit();//获取决定是否退出程序的布尔变量值
	void set_userFile(string s);//可以设定存储用户信息的文件，但默认为构造函数中定义的usersInfo.txt
	string get_userFile();//取得存储用户信息的文件名
	void check_from_file();//从文件中读取用户信息，并确认是否存在该用户，有则验证成功可进入修改密码页面，无则提示请注册
	void register_into_file_tree();//注册界面，提示用户注册，并将信息存入文件
	void delete_from_file_tree();//删除界面，将用户信息从文件中删除
	void show_all_account();//超级管理员界面，按照横向的平衡树打印整棵树
	void update_password(TreeNode * temp);//修改密码界面
private:
	Tree userTree;//声明存储用户信息的一颗树
	UserInfo user;//需要用到的临时存储用户信息的变量
	string mode;//记录键盘输入的菜单选项
	bool quit;//记录是否退出程序
	int menu;//记录菜单的选项
	string userFile;//获取存储用户登陆账号密码信息的文件名,测试时使用 usersInfo.txt 每行账户 及密码结束后需回车
};