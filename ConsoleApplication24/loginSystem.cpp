//loginSystem.cpp
#include<iostream>
#include<conio.h>
#include<string>
#include<iomanip>
using namespace std;
#include"loginSystem.h"
UserInfo::UserInfo(){//用户信息的构造函数，默认均为空字符串
	myId = "";
	myPassword = "";
}
UserInfo::UserInfo(string id, string pw){//构造函数重载
	myId = id;
	myPassword = pw;
}
UserInfo::~UserInfo(){}//没有需要释放的指针
UserInfo*::UserInfo::get_this(){//取得指向该用户的指针
	return this;
}
string UserInfo::id()const{ //取得用户的账号信息
	return myId; 
}
string UserInfo::get_myPassword(){//取得该用户的密码
	return myPassword;
}
void UserInfo::set_myPassword(string newpass){//设置用户的密码
	myPassword = newpass;
}
void UserInfo::set_myId(string newid){//设置用户的账号
	myId = newid;
}
void UserInfo::read(istream &in)//从输入流中读取账号及密码
{
	in >> myId >> myPassword;
}
void UserInfo::write(ostream &out){//向输出流输出账号及密码信息，以空格为间
	out << myId << " " << myPassword << endl;
}
bool UserInfo::operator==(const UserInfo & user)const{//等号重载
	return myId < user.myId &&
		myPassword == user.myPassword;
}
bool UserInfo::operator<(const UserInfo & user)const{//小于号重载
	return myId < user.myId ||
		myId == user.myId && myPassword < user.myPassword;//当账号一样是按照密码进行对比
}
bool UserInfo::operator>(const UserInfo & user)const{//大于号重载
	return myId>user.myId ||
		myId == user.myId && myPassword>user.myPassword;//当账号一样是按照密码进行对比
}
ostream & operator<<(ostream & out, UserInfo &user) {//UserInfo类的友元函数用于输出流运算符重载
	user.write(out);
	return out;
}
istream & operator>>(istream & in, UserInfo & user){//UserInfo类的友元函数用于输入流运算符重载
	user.read(in);
	return in;
}
Tree::Tree(){
	found = true;//默认为真
	rootTreeNode = 0;//根节点指向空
}
Tree::~Tree()
{
	destroyHelper(rootTreeNode);//调用辅助函数
}
int Tree::max(int s1, int s2)//返回节点高度较大值的函数
	{
		return s1>s2 ? s1 : s2;
	}
void Tree::deleteValue(UserInfo value)
{
	if (rootTreeNode != 0)//不为空树进行删除
	{
		deleteHelper1(rootTreeNode, value);//调用删除函数的辅助函数
		if (found){//删除成功后提示删除成功
			cout << "成功删除！" << endl;
		}
	}
	else
		cerr << "本地文件中没有任何账户信息！" << endl;
}
UserInfo Tree::deleteHelper2(TreeNode* &nodePtr)//找出一个左子树为空的叶子节点将值返回进行删除
{
	UserInfo retVal;//声明一个临时的变量
	if (nodePtr->leftPtr != 0)//该左子树不为空
	{
		retVal = deleteHelper2(nodePtr->leftPtr);//将左子树传入递归，寻找相应的值进行删除
		if (high(nodePtr->rightPtr) - high(nodePtr->leftPtr) == 2)
		{
			if (high(nodePtr->rightPtr->leftPtr)>high(nodePtr->rightPtr->rightPtr))//说明是RL型
				rightAndLeft(nodePtr);
			else//说明是RR型
				turnLeft(nodePtr);
		}
		nodePtr->height = max(high(nodePtr->leftPtr), high(nodePtr->rightPtr)) + 1;
	}
	else//当左子树为空时执行以下删除操作
	{
		retVal = nodePtr->data;//将要被删除的值存储起来，在最后返回
		TreeNode * temp = nodePtr;
		nodePtr = nodePtr->rightPtr == 0 ? 0 : nodePtr->rightPtr;//判断右子树是否为空，赋给其相应的指针
		delete temp;//释放该节点
	}
	return retVal;//返回删除的值
}
void Tree::deleteHelper1(TreeNode* &nodePtr, UserInfo value)
{
	if (nodePtr == 0)//找不到该数值
	{
		cout << endl << "没有该用户的注册信息，无法删除！\n";
		found = false;
		return;
	}
	if (nodePtr->data<value)//如果当前数据值小于寻找目标值
	{
		deleteHelper1(nodePtr->rightPtr, value);//进入右子树递归
		if (high(nodePtr->leftPtr) - high(nodePtr->rightPtr) == 2)//由于在右边删除了一个节点出现不平衡
		{
			if (high(nodePtr->leftPtr->rightPtr)>high(nodePtr->leftPtr->leftPtr))//该条件成立说明是LR型不平衡
				leftAndRight(nodePtr);
			else
				turnRight(nodePtr);//相等或者大于，说明是LL型
		}
	}
	else if (value<nodePtr->data)//如果当前数据值大于寻找目标值
	{
		deleteHelper1(nodePtr->leftPtr, value);//进入左子树递归
		if (high(nodePtr->rightPtr) - high(nodePtr->leftPtr) == 2)//由于在左边删除了一个节点出现不平衡
		{
			if (high(nodePtr->rightPtr->leftPtr)>high(nodePtr->rightPtr->rightPtr))//该条件成立说明RL型不平衡
				rightAndLeft(nodePtr);
			else
				turnLeft(nodePtr);
		}
	}
	else//出上述两种情况之外就是相等的情况了，找到目标值
	{
		if (nodePtr->rightPtr == 0)//若该值右子树为空
		{
			TreeNode * temp = nodePtr;//定义一个临时变量等于该值
			nodePtr = nodePtr->leftPtr;//既然右子树为空，只要将该值的指向改为他的左子树
			delete temp;//最后再将其释放
		}
		else if (nodePtr->leftPtr == 0)//与上述相类似的情况
		{
			TreeNode * temp = nodePtr;
			nodePtr = nodePtr->rightPtr;
			delete temp;
		}
		else//两个子树均不为空的情况
		{
			nodePtr->data = deleteHelper2(nodePtr->rightPtr);//调用辅助函数deleteHelper2将删除的叶节点的值赋值给需要删除的节点
			if (high(nodePtr->leftPtr) - high(nodePtr->rightPtr) == 2)
			{
				if (high(nodePtr->leftPtr->rightPtr)>high(nodePtr->leftPtr->leftPtr))//说明是LR型
					leftAndRight(nodePtr);
				else
					turnRight(nodePtr);//相等或者大于
			}
		}
	}
	if (nodePtr != 0)
		nodePtr->height = max(high(nodePtr->leftPtr), high(nodePtr->rightPtr)) + 1;//更新节点的高度

}
void Tree::turnRight(TreeNode* &nodePtr)//右旋操作
{
	TreeNode * temp = nodePtr->leftPtr;//将该节点的左子树记录
	nodePtr->leftPtr = temp->rightPtr;//该节点的左指针指向该节点左子树根的右子树
	nodePtr->height = max(high(nodePtr->leftPtr), high(nodePtr->rightPtr)) + 1;//更新该子树的高度
	temp->rightPtr = nodePtr;//将该节点放在之前记录指针的右指针
	nodePtr = temp;//该节点成为根
	nodePtr->height = max(high(nodePtr->leftPtr), high(nodePtr->rightPtr)) + 1;//更新高度
}
void Tree::turnLeft(TreeNode* &nodePtr)//左旋操作
{
	TreeNode* temp = nodePtr->rightPtr;//记录该节点的右子树
	nodePtr->rightPtr = temp->leftPtr;//该节点的右子树指向原先节点右子树的左子树
	nodePtr->height = max(high(nodePtr->leftPtr), high(nodePtr->rightPtr)) + 1;//更新当前高度
	temp->leftPtr = nodePtr;//原先节点的左指针指向改变后的nodePtr
	nodePtr = temp;//使之成为根
	nodePtr->height = max(high(nodePtr->leftPtr), high(nodePtr->rightPtr)) + 1;//更新高度
}
void Tree::leftAndRight(TreeNode* &nodePtr)//LR型不平衡的旋转
{
	turnLeft(nodePtr->leftPtr);
	turnRight(nodePtr);
}
void Tree::rightAndLeft(TreeNode* &nodePtr)//RL型不平衡的旋转
{
	turnRight(nodePtr->rightPtr);
	turnLeft(nodePtr);
}
int Tree::high(TreeNode* nodePtr){//返回该节点的高度
	return nodePtr == 0 ? -1 : nodePtr->height;
}
TreeNode* Tree::treeSearch(UserInfo value){//返回该值所在节点指针
	return searchHelper(rootTreeNode, value);
}
TreeNode* Tree::searchHelper(TreeNode* nodePtr, UserInfo value){//使用递归实现搜索
	TreeNode* retPtr = 0;
	if (nodePtr == 0)//没有找到则返回空指针
		return retPtr;
	if (value<nodePtr->data)//当前值比目标值大向其左边递归
		return searchHelper(nodePtr->leftPtr, value);
	if (value>nodePtr->data)//当前值比目标值小向其右边递归
		return searchHelper(nodePtr->rightPtr, value);
	return nodePtr;//这种if的测试应该把最不可能的结果放在最后进行。
}
TreeNode::TreeNode(UserInfo value)//节点的初始化
{
	data = value;
	leftPtr = rightPtr = 0;
	height = 0;//一般在插入节点的时候会初始化新节点，而该节点一开始肯定被插入到叶出，而叶节点的高度为0；
}
UserInfo *TreeNode::getData()//返回该节点的指针
{
	return &data;
}
void Tree::insertTreeNode(UserInfo value)//在树种插入一个节点，调用辅助函数insertHelper
{
	insertHelper(rootTreeNode, value);
}
void Tree::insertHelper(TreeNode* &nodePtr, UserInfo value)
{
	if (nodePtr == 0)//如果树为空直接进行插入
		nodePtr = new TreeNode(value);
	else
	{
		if (value<nodePtr->data)//当前值比目标值大
		{
			insertHelper(nodePtr->leftPtr, value);//向左递归
			if (high(nodePtr->leftPtr) - high(nodePtr->rightPtr) == 2)//插入以后改变平衡
			{
				if (value<nodePtr->leftPtr->data)//如果插入的值小于该节点左子的数据则说明是LL型
					turnRight(nodePtr);
				else//反之为LR型
					leftAndRight(nodePtr);
			}
		}
		else if (nodePtr->data<value)//当前值小于目标值
		{
			insertHelper(nodePtr->rightPtr, value);//进入右子树递归
			if (high(nodePtr->rightPtr) - high(nodePtr->leftPtr) == 2)//出现不平衡
			{
				if (value<nodePtr->rightPtr->data)//插入的值小于该节点右子的数据值说明是RL型
					rightAndLeft(nodePtr);
				else//否则为RR型
					turnLeft(nodePtr);
			}
		}
		else //如果value==nodePtr->data；因为是重复，所以直接无视掉；(空操作；
			;
	}
	//更新高度
	nodePtr->height = max(high(nodePtr->leftPtr), high(nodePtr->rightPtr)) + 1;
}
void Tree::inOrederTraversal(ostream & out){//遍历输出函数，调用inHelper辅助函数
	inHelper(out, rootTreeNode);
}
void Tree::inHelper(ostream & out, TreeNode* nodePtr)
{
	if (nodePtr == 0)//当指针为空时直接返回
		return;
	inHelper(out, nodePtr->leftPtr);//中序遍历LVR
	out << "  " << nodePtr->data;
	inHelper(out, nodePtr->rightPtr);
}
void Tree::destroyHelper(TreeNode* nodePtr){//析构函数的辅助函数
	if (nodePtr == 0)
		return;
	destroyHelper(nodePtr->leftPtr);//先左后右的释放顺序
	destroyHelper(nodePtr->rightPtr);
	delete nodePtr;
}
void Tree::outputTree(){//输出平衡树，调用辅助函数outputTreeHelper
	cout << endl;
	if (rootTreeNode != 0)
		outputTreeHelper(rootTreeNode, 0);
	else
		cout << "文件中没有账号！\n";
}
void Tree::outputTreeHelper(TreeNode* nodePtr, int space){//space 表示输出该值之前要输出多少个空格
	if (nodePtr != 0)
	{
		outputTreeHelper(nodePtr->rightPtr, space + 5);//输出该值之前应该先输出该值得左子树，往下推进一层，所以空格数加5
		for (int i = 0; i < space; i++)//输出空格以构建层次感
			cout << ' ';
		cout << *nodePtr->getData() << endl;//输出数值外还要输出换行
		outputTreeHelper(nodePtr->leftPtr, space + 5);
	}
}
Menu::Menu(){//默认构造函数
	userFile = "usersInfo.txt";//在测试阶段将存放用户信息的文件直接定义成usersInfo.txt并不作改变
	menu = 0;
	quit = false;
}
Menu::~Menu(){//无需要释放的指针
}
int Menu::get_menu(){//得到菜单选项
	return menu;
}
bool Menu::get_quit(){//得到是否退出程序的布尔变量
	return quit;
}
string Menu::get_userFile(){//得到存储用户信息的文件，测试阶段没有用到
	return userFile;
}
void Menu::set_userFile(string s){//可以自己设定存储的文件
	userFile = s;
}
void Menu::set_mode_set_menu(){//主菜单界面，控制用户的输入选项，设置menu的值
	char c = 26;
	char c1 = 27;
	cout << setfill(c1) << setw(27) << "主菜单";
	for (int i = 0; i < 20; i++)cout <<c;//界面美化元素
	cout << endl;
	cout << "1.输入login 进入登陆界面，进入后可更新修改密码！\n" << "2.输入register进入注册界面\n" << "3.输入delete进入删除用户账号界面\n"
		<< "4.输入quit退出程序\n" << "5.输入dchdtc成为超级管理员查看所有账号信息！\n" << endl;
	cin >> mode;
	if (mode == "login"){
		menu = 0;
	}
	else if (mode == "register"){
		menu = 1;
	}
	else if (mode == "delete"){
		menu = 2;
	}
	else  if (mode == "quit"){
		menu = 3;
		quit = true;//当选择结束程序时同时将quit的值赋为一
	}
	else if (mode == "dchdtc"){
		menu = 4;
	}
	else {//其他情况一律为-1方便错误处理
		menu = -1;
	}

}
void Menu::check_from_file(){//登录以及修改密码界面
	ifstream inStream(userFile);
	Tree  userTree;//临时树，存储读出来的用户信息
	UserInfo user;//临时变量，存储用户输入的信息
	if (!inStream.is_open()){
		cerr << "Cannot open " << userFile << endl;
		exit(1);
	}
	for (;;){
		inStream >> user;
		if (inStream.eof())break;//到达文件底部就break,不再写入树中
		userTree.insertTreeNode(user);
	}
	inStream.close();//将文件关闭
	char c = 26;
	char c1 = 27;
	cout << setfill(c1) << setw(27) << "登录";
	for (int i = 0; i < 20; i++)cout << c;//界面美化元素
	for (;;){
		string account = "";
		char password[11];
		int i = 0;
		cout << "\n 请输入您的用户名以及密码\n";
		cout << "用户名：";
		cin >> account;
		user.set_myId(account);//存入用户账号
		cout << endl;
		cout << "密码：";
		bool error = false;//判断用户输入密码是否违法
		while ((*(password + i) = _getch()) != 13){
			if (*(password + i) != '\b' && i< 10){
				_putch('*');//密码的隐式显示
				i++;
			}
			else if (*(password + i) == '\b' && i > 0){//回退键的处理
				cout << '\b';
				cout << '\0';
				cout << '\b';
				i--;
			}
			if (i >10){
				error = true;
				break;
			}
		}
		cout << endl;
		string newpassword(&password[0],&password[i]);//将读入的字符数组转化为字符串
		user.set_myPassword(newpassword);//存入用户密码
		TreeNode *temp = userTree.treeSearch(user);//调用查找函数，寻找是否存在该用户
		if (temp)//如果不为空
		{
			string choice;
			cout << "登录成功！\n";
			cout << setfill('*') << setw(27) << "登录后功能页";
			for (int i = 0; i < 20; i++)cout << '*';//界面美化元素
			//修改密码功能
			cout << "\n当前，您可以修改您的密码\n" << "1.输入change进入修改密码界面\n" << "2.输入back返回主界面\n";
			while (cin >> choice){
				if (choice == "change"){
					update_password(temp);//调用修改密码函数
					ofstream fout(userFile);
					userTree.inOrederTraversal(fout);//将修改后的值写入文件
					fout.close();
					return;
				}
				else if (choice == "back"){
					return;
				}
				else{
					cout << "输入有误，请重新输入！\n" << endl;
				}
			}


		}
		else//为空
		{
			cout << "还未注册,请您到主菜单进行注册！\n";
			return;
		}
	}

}
void Menu::register_into_file_tree(){//注册界面
	ofstream fout(userFile, ios::app);//打开文件，以在尾部添加方式打开
	if (!fout.is_open()){
		cerr << "Cannot open " << userFile << endl;
		exit(1);
	}
	char c = 26;
	char c1 = 27;
	cout << setfill(c1) << setw(27) << "新用户注册";
	for (int i = 0; i < 20; i++)cout << c;//界面美化元素
	string account = "";
	char password[11];
	int i = 0;
	cout << "\n 请输入您的用户名以及密码，为保障账户安全，密码长度要求不小于6不大于10\n";
	cout << "用户名：";
	cin >> account;
	user.set_myId(account);
	cout << endl;
	cout << "密码：";
	while ((*(password + i) = _getch()) != 13){
		if (*(password + i) != '\b' && i< 10){
			_putch('*');
			i++;
		}
		else if (*(password + i) == '\b' && i > 0){
			cout << '\b';
			cout << '\0';
			cout << '\b';
			i--;
		}
	   if (i >10){
		   break;
		}
	}
	cout << endl;
	string newpassword(&password[0], &password[i]);
	user.set_myPassword(newpassword);
	if (i <= 10 && i >= 6 && userTree.treeSearch(user) == NULL){
		userTree.insertTreeNode(user);//在树中存入该用户
		fout << user;//在文件中写入该用户
		cout << "注册成功\n";
	}
	else if (userTree.treeSearch(user) != NULL){
		cout << "该用户已经存在，请直接登录\n";
	}
	else{
		cout << "注册失败，密码不符合要求\n";
	}

	fout.close();
}
void Menu::delete_from_file_tree(){//删除界面
	ifstream inStream(userFile);
	Tree userTree;//声明临时树，存储读取的信息
	UserInfo user;//声明临时用户，存储读取的用户
	if (!inStream.is_open()){
		cerr << "Cannot open " << userFile << endl;
		exit(1);
	}
	for (;;){
		inStream >> user;
		if (inStream.eof())break;
		userTree.insertTreeNode(user);
	}
	inStream.close();
	char c = 26;
	char c1 = 27;
	cout << setfill(c1) << setw(27) << "删除功能";
	for (int i = 0; i < 20; i++)cout << c;//界面美化元素
	ofstream fout(userFile);
	string account = "";
	char password[11];//多留一位作缓冲用
	int i = 0;
	cout << "\n 请输入您的用户名以及密码，密码要求不小于6不大于10\n";
	cout << "用户名：";
	cin >> account;
	user.set_myId(account);
	cout << endl;
	cout << "密码：";
	while ((*(password + i) = _getch()) != 13){
		if (*(password + i) != '\b' && i< 10){
			_putch('*');
			i++;
		}
		else if (*(password + i) == '\b' && i > 0){
			cout << '\b';
			cout << '\0';
			cout << '\b';
			i--;
		}
		if (i >10){
			break;
		}
	}
	string newpassword(&password[0], &password[i]);
	user.set_myPassword(newpassword);
	if (i >= 6 && i <= 10 && userTree.treeSearch(user) != NULL ){
		cout << endl;
		userTree.deleteValue(user);
	}
	else if(i<6 || i >10){
		cout << "\n"<<"密码输入格式有误！" << endl;
	}
	else{
		cout << "\n文件中没有此账号信息！" << endl;
	}
	userTree.inOrederTraversal(fout);//写入文件
	fout.close();
}
void Menu::show_all_account(){//超级管理员界面
	ifstream inStream(userFile);
	Tree userTree;
	if (!inStream.is_open()){
		cerr << "Cannot open " << userFile << endl;
		exit(1);
	}
	for (;;){
		inStream >> user;
		if (inStream.eof())break;
		userTree.insertTreeNode(user);
	}
	inStream.close();
	char c = 26;
	char c1 = 27;
	cout << setfill(c1) << setw(27) << "超级管理员";
	for (int i = 0; i < 20; i++)cout << c;//界面美化元素
	cout << "\n此系统中存在的用户信息二叉查找树显示为：" << endl;
	userTree.outputTree();//调用输出树函数，横向打印出整棵树
}
void Menu::update_password(TreeNode * temp){//修改密码功能
	string newpass,oldpass ,id;
	cout << "为保障账户安全请输入旧密码：\n";
	cin >> oldpass;
	if (oldpass == temp->getData()->get_myPassword()){//需要有一个验证过程
		cout << "验证成功！\n";
		cout << "请输入新密码：" << endl;
		char password[11];
		int i = 0;
		while ((*(password + i) = _getch()) != 13){
			if (*(password + i) != '\b' && i< 10){
				_putch('*');
				i++;
			}
			else if (*(password + i) == '\b' && i > 0){
				cout << '\b';
				cout << '\0';
				cout << '\b';
				i--;
			}
			if (i >10){
				break;
			}
		}
		cout << endl;
		string newpassword(&password[0], &password[i]);
		if (i <= 10 && i >= 6 ){
			temp->getData()->set_myPassword(newpassword);//取得该节点的指针之后进行修改
			cout << "修改成功，请重新登录！\n";
		}
		else{
			cout << "修改失败，密码不符合要求\n";
		}

	}
	else{
		cout << "密码错误，验证失败！" << endl;
	}

}
