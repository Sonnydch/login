//loginSystem.cpp
#include<iostream>
#include<conio.h>
#include<string>
#include<iomanip>
using namespace std;
#include"loginSystem.h"
UserInfo::UserInfo(){//�û���Ϣ�Ĺ��캯����Ĭ�Ͼ�Ϊ���ַ���
	myId = "";
	myPassword = "";
}
UserInfo::UserInfo(string id, string pw){//���캯������
	myId = id;
	myPassword = pw;
}
UserInfo::~UserInfo(){}//û����Ҫ�ͷŵ�ָ��
UserInfo*::UserInfo::get_this(){//ȡ��ָ����û���ָ��
	return this;
}
string UserInfo::id()const{ //ȡ���û����˺���Ϣ
	return myId; 
}
string UserInfo::get_myPassword(){//ȡ�ø��û�������
	return myPassword;
}
void UserInfo::set_myPassword(string newpass){//�����û�������
	myPassword = newpass;
}
void UserInfo::set_myId(string newid){//�����û����˺�
	myId = newid;
}
void UserInfo::read(istream &in)//���������ж�ȡ�˺ż�����
{
	in >> myId >> myPassword;
}
void UserInfo::write(ostream &out){//�����������˺ż�������Ϣ���Կո�Ϊ��
	out << myId << " " << myPassword << endl;
}
bool UserInfo::operator==(const UserInfo & user)const{//�Ⱥ�����
	return myId < user.myId &&
		myPassword == user.myPassword;
}
bool UserInfo::operator<(const UserInfo & user)const{//С�ں�����
	return myId < user.myId ||
		myId == user.myId && myPassword < user.myPassword;//���˺�һ���ǰ���������жԱ�
}
bool UserInfo::operator>(const UserInfo & user)const{//���ں�����
	return myId>user.myId ||
		myId == user.myId && myPassword>user.myPassword;//���˺�һ���ǰ���������жԱ�
}
ostream & operator<<(ostream & out, UserInfo &user) {//UserInfo�����Ԫ����������������������
	user.write(out);
	return out;
}
istream & operator>>(istream & in, UserInfo & user){//UserInfo�����Ԫ�����������������������
	user.read(in);
	return in;
}
Tree::Tree(){
	found = true;//Ĭ��Ϊ��
	rootTreeNode = 0;//���ڵ�ָ���
}
Tree::~Tree()
{
	destroyHelper(rootTreeNode);//���ø�������
}
int Tree::max(int s1, int s2)//���ؽڵ�߶Ƚϴ�ֵ�ĺ���
	{
		return s1>s2 ? s1 : s2;
	}
void Tree::deleteValue(UserInfo value)
{
	if (rootTreeNode != 0)//��Ϊ��������ɾ��
	{
		deleteHelper1(rootTreeNode, value);//����ɾ�������ĸ�������
		if (found){//ɾ���ɹ�����ʾɾ���ɹ�
			cout << "�ɹ�ɾ����" << endl;
		}
	}
	else
		cerr << "�����ļ���û���κ��˻���Ϣ��" << endl;
}
UserInfo Tree::deleteHelper2(TreeNode* &nodePtr)//�ҳ�һ��������Ϊ�յ�Ҷ�ӽڵ㽫ֵ���ؽ���ɾ��
{
	UserInfo retVal;//����һ����ʱ�ı���
	if (nodePtr->leftPtr != 0)//����������Ϊ��
	{
		retVal = deleteHelper2(nodePtr->leftPtr);//������������ݹ飬Ѱ����Ӧ��ֵ����ɾ��
		if (high(nodePtr->rightPtr) - high(nodePtr->leftPtr) == 2)
		{
			if (high(nodePtr->rightPtr->leftPtr)>high(nodePtr->rightPtr->rightPtr))//˵����RL��
				rightAndLeft(nodePtr);
			else//˵����RR��
				turnLeft(nodePtr);
		}
		nodePtr->height = max(high(nodePtr->leftPtr), high(nodePtr->rightPtr)) + 1;
	}
	else//��������Ϊ��ʱִ������ɾ������
	{
		retVal = nodePtr->data;//��Ҫ��ɾ����ֵ�洢����������󷵻�
		TreeNode * temp = nodePtr;
		nodePtr = nodePtr->rightPtr == 0 ? 0 : nodePtr->rightPtr;//�ж��������Ƿ�Ϊ�գ���������Ӧ��ָ��
		delete temp;//�ͷŸýڵ�
	}
	return retVal;//����ɾ����ֵ
}
void Tree::deleteHelper1(TreeNode* &nodePtr, UserInfo value)
{
	if (nodePtr == 0)//�Ҳ�������ֵ
	{
		cout << endl << "û�и��û���ע����Ϣ���޷�ɾ����\n";
		found = false;
		return;
	}
	if (nodePtr->data<value)//�����ǰ����ֵС��Ѱ��Ŀ��ֵ
	{
		deleteHelper1(nodePtr->rightPtr, value);//�����������ݹ�
		if (high(nodePtr->leftPtr) - high(nodePtr->rightPtr) == 2)//�������ұ�ɾ����һ���ڵ���ֲ�ƽ��
		{
			if (high(nodePtr->leftPtr->rightPtr)>high(nodePtr->leftPtr->leftPtr))//����������˵����LR�Ͳ�ƽ��
				leftAndRight(nodePtr);
			else
				turnRight(nodePtr);//��Ȼ��ߴ��ڣ�˵����LL��
		}
	}
	else if (value<nodePtr->data)//�����ǰ����ֵ����Ѱ��Ŀ��ֵ
	{
		deleteHelper1(nodePtr->leftPtr, value);//�����������ݹ�
		if (high(nodePtr->rightPtr) - high(nodePtr->leftPtr) == 2)//���������ɾ����һ���ڵ���ֲ�ƽ��
		{
			if (high(nodePtr->rightPtr->leftPtr)>high(nodePtr->rightPtr->rightPtr))//����������˵��RL�Ͳ�ƽ��
				rightAndLeft(nodePtr);
			else
				turnLeft(nodePtr);
		}
	}
	else//�������������֮�������ȵ�����ˣ��ҵ�Ŀ��ֵ
	{
		if (nodePtr->rightPtr == 0)//����ֵ������Ϊ��
		{
			TreeNode * temp = nodePtr;//����һ����ʱ�������ڸ�ֵ
			nodePtr = nodePtr->leftPtr;//��Ȼ������Ϊ�գ�ֻҪ����ֵ��ָ���Ϊ����������
			delete temp;//����ٽ����ͷ�
		}
		else if (nodePtr->leftPtr == 0)//�����������Ƶ����
		{
			TreeNode * temp = nodePtr;
			nodePtr = nodePtr->rightPtr;
			delete temp;
		}
		else//������������Ϊ�յ����
		{
			nodePtr->data = deleteHelper2(nodePtr->rightPtr);//���ø�������deleteHelper2��ɾ����Ҷ�ڵ��ֵ��ֵ����Ҫɾ���Ľڵ�
			if (high(nodePtr->leftPtr) - high(nodePtr->rightPtr) == 2)
			{
				if (high(nodePtr->leftPtr->rightPtr)>high(nodePtr->leftPtr->leftPtr))//˵����LR��
					leftAndRight(nodePtr);
				else
					turnRight(nodePtr);//��Ȼ��ߴ���
			}
		}
	}
	if (nodePtr != 0)
		nodePtr->height = max(high(nodePtr->leftPtr), high(nodePtr->rightPtr)) + 1;//���½ڵ�ĸ߶�

}
void Tree::turnRight(TreeNode* &nodePtr)//��������
{
	TreeNode * temp = nodePtr->leftPtr;//���ýڵ����������¼
	nodePtr->leftPtr = temp->rightPtr;//�ýڵ����ָ��ָ��ýڵ�����������������
	nodePtr->height = max(high(nodePtr->leftPtr), high(nodePtr->rightPtr)) + 1;//���¸������ĸ߶�
	temp->rightPtr = nodePtr;//���ýڵ����֮ǰ��¼ָ�����ָ��
	nodePtr = temp;//�ýڵ��Ϊ��
	nodePtr->height = max(high(nodePtr->leftPtr), high(nodePtr->rightPtr)) + 1;//���¸߶�
}
void Tree::turnLeft(TreeNode* &nodePtr)//��������
{
	TreeNode* temp = nodePtr->rightPtr;//��¼�ýڵ��������
	nodePtr->rightPtr = temp->leftPtr;//�ýڵ��������ָ��ԭ�Ƚڵ���������������
	nodePtr->height = max(high(nodePtr->leftPtr), high(nodePtr->rightPtr)) + 1;//���µ�ǰ�߶�
	temp->leftPtr = nodePtr;//ԭ�Ƚڵ����ָ��ָ��ı���nodePtr
	nodePtr = temp;//ʹ֮��Ϊ��
	nodePtr->height = max(high(nodePtr->leftPtr), high(nodePtr->rightPtr)) + 1;//���¸߶�
}
void Tree::leftAndRight(TreeNode* &nodePtr)//LR�Ͳ�ƽ�����ת
{
	turnLeft(nodePtr->leftPtr);
	turnRight(nodePtr);
}
void Tree::rightAndLeft(TreeNode* &nodePtr)//RL�Ͳ�ƽ�����ת
{
	turnRight(nodePtr->rightPtr);
	turnLeft(nodePtr);
}
int Tree::high(TreeNode* nodePtr){//���ظýڵ�ĸ߶�
	return nodePtr == 0 ? -1 : nodePtr->height;
}
TreeNode* Tree::treeSearch(UserInfo value){//���ظ�ֵ���ڽڵ�ָ��
	return searchHelper(rootTreeNode, value);
}
TreeNode* Tree::searchHelper(TreeNode* nodePtr, UserInfo value){//ʹ�õݹ�ʵ������
	TreeNode* retPtr = 0;
	if (nodePtr == 0)//û���ҵ��򷵻ؿ�ָ��
		return retPtr;
	if (value<nodePtr->data)//��ǰֵ��Ŀ��ֵ��������ߵݹ�
		return searchHelper(nodePtr->leftPtr, value);
	if (value>nodePtr->data)//��ǰֵ��Ŀ��ֵС�����ұߵݹ�
		return searchHelper(nodePtr->rightPtr, value);
	return nodePtr;//����if�Ĳ���Ӧ�ð�����ܵĽ�����������С�
}
TreeNode::TreeNode(UserInfo value)//�ڵ�ĳ�ʼ��
{
	data = value;
	leftPtr = rightPtr = 0;
	height = 0;//һ���ڲ���ڵ��ʱ����ʼ���½ڵ㣬���ýڵ�һ��ʼ�϶������뵽Ҷ������Ҷ�ڵ�ĸ߶�Ϊ0��
}
UserInfo *TreeNode::getData()//���ظýڵ��ָ��
{
	return &data;
}
void Tree::insertTreeNode(UserInfo value)//�����ֲ���һ���ڵ㣬���ø�������insertHelper
{
	insertHelper(rootTreeNode, value);
}
void Tree::insertHelper(TreeNode* &nodePtr, UserInfo value)
{
	if (nodePtr == 0)//�����Ϊ��ֱ�ӽ��в���
		nodePtr = new TreeNode(value);
	else
	{
		if (value<nodePtr->data)//��ǰֵ��Ŀ��ֵ��
		{
			insertHelper(nodePtr->leftPtr, value);//����ݹ�
			if (high(nodePtr->leftPtr) - high(nodePtr->rightPtr) == 2)//�����Ժ�ı�ƽ��
			{
				if (value<nodePtr->leftPtr->data)//��������ֵС�ڸýڵ����ӵ�������˵����LL��
					turnRight(nodePtr);
				else//��֮ΪLR��
					leftAndRight(nodePtr);
			}
		}
		else if (nodePtr->data<value)//��ǰֵС��Ŀ��ֵ
		{
			insertHelper(nodePtr->rightPtr, value);//�����������ݹ�
			if (high(nodePtr->rightPtr) - high(nodePtr->leftPtr) == 2)//���ֲ�ƽ��
			{
				if (value<nodePtr->rightPtr->data)//�����ֵС�ڸýڵ����ӵ�����ֵ˵����RL��
					rightAndLeft(nodePtr);
				else//����ΪRR��
					turnLeft(nodePtr);
			}
		}
		else //���value==nodePtr->data����Ϊ���ظ�������ֱ�����ӵ���(�ղ�����
			;
	}
	//���¸߶�
	nodePtr->height = max(high(nodePtr->leftPtr), high(nodePtr->rightPtr)) + 1;
}
void Tree::inOrederTraversal(ostream & out){//�����������������inHelper��������
	inHelper(out, rootTreeNode);
}
void Tree::inHelper(ostream & out, TreeNode* nodePtr)
{
	if (nodePtr == 0)//��ָ��Ϊ��ʱֱ�ӷ���
		return;
	inHelper(out, nodePtr->leftPtr);//�������LVR
	out << "  " << nodePtr->data;
	inHelper(out, nodePtr->rightPtr);
}
void Tree::destroyHelper(TreeNode* nodePtr){//���������ĸ�������
	if (nodePtr == 0)
		return;
	destroyHelper(nodePtr->leftPtr);//������ҵ��ͷ�˳��
	destroyHelper(nodePtr->rightPtr);
	delete nodePtr;
}
void Tree::outputTree(){//���ƽ���������ø�������outputTreeHelper
	cout << endl;
	if (rootTreeNode != 0)
		outputTreeHelper(rootTreeNode, 0);
	else
		cout << "�ļ���û���˺ţ�\n";
}
void Tree::outputTreeHelper(TreeNode* nodePtr, int space){//space ��ʾ�����ֵ֮ǰҪ������ٸ��ո�
	if (nodePtr != 0)
	{
		outputTreeHelper(nodePtr->rightPtr, space + 5);//�����ֵ֮ǰӦ���������ֵ���������������ƽ�һ�㣬���Կո�����5
		for (int i = 0; i < space; i++)//����ո��Թ�����θ�
			cout << ' ';
		cout << *nodePtr->getData() << endl;//�����ֵ�⻹Ҫ�������
		outputTreeHelper(nodePtr->leftPtr, space + 5);
	}
}
Menu::Menu(){//Ĭ�Ϲ��캯��
	userFile = "usersInfo.txt";//�ڲ��Խ׶ν�����û���Ϣ���ļ�ֱ�Ӷ����usersInfo.txt�������ı�
	menu = 0;
	quit = false;
}
Menu::~Menu(){//����Ҫ�ͷŵ�ָ��
}
int Menu::get_menu(){//�õ��˵�ѡ��
	return menu;
}
bool Menu::get_quit(){//�õ��Ƿ��˳�����Ĳ�������
	return quit;
}
string Menu::get_userFile(){//�õ��洢�û���Ϣ���ļ������Խ׶�û���õ�
	return userFile;
}
void Menu::set_userFile(string s){//�����Լ��趨�洢���ļ�
	userFile = s;
}
void Menu::set_mode_set_menu(){//���˵����棬�����û�������ѡ�����menu��ֵ
	char c = 26;
	char c1 = 27;
	cout << setfill(c1) << setw(27) << "���˵�";
	for (int i = 0; i < 20; i++)cout <<c;//��������Ԫ��
	cout << endl;
	cout << "1.����login �����½���棬�����ɸ����޸����룡\n" << "2.����register����ע�����\n" << "3.����delete����ɾ���û��˺Ž���\n"
		<< "4.����quit�˳�����\n" << "5.����dchdtc��Ϊ��������Ա�鿴�����˺���Ϣ��\n" << endl;
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
		quit = true;//��ѡ���������ʱͬʱ��quit��ֵ��Ϊһ
	}
	else if (mode == "dchdtc"){
		menu = 4;
	}
	else {//�������һ��Ϊ-1���������
		menu = -1;
	}

}
void Menu::check_from_file(){//��¼�Լ��޸��������
	ifstream inStream(userFile);
	Tree  userTree;//��ʱ�����洢���������û���Ϣ
	UserInfo user;//��ʱ�������洢�û��������Ϣ
	if (!inStream.is_open()){
		cerr << "Cannot open " << userFile << endl;
		exit(1);
	}
	for (;;){
		inStream >> user;
		if (inStream.eof())break;//�����ļ��ײ���break,����д������
		userTree.insertTreeNode(user);
	}
	inStream.close();//���ļ��ر�
	char c = 26;
	char c1 = 27;
	cout << setfill(c1) << setw(27) << "��¼";
	for (int i = 0; i < 20; i++)cout << c;//��������Ԫ��
	for (;;){
		string account = "";
		char password[11];
		int i = 0;
		cout << "\n �����������û����Լ�����\n";
		cout << "�û�����";
		cin >> account;
		user.set_myId(account);//�����û��˺�
		cout << endl;
		cout << "���룺";
		bool error = false;//�ж��û����������Ƿ�Υ��
		while ((*(password + i) = _getch()) != 13){
			if (*(password + i) != '\b' && i< 10){
				_putch('*');//�������ʽ��ʾ
				i++;
			}
			else if (*(password + i) == '\b' && i > 0){//���˼��Ĵ���
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
		string newpassword(&password[0],&password[i]);//��������ַ�����ת��Ϊ�ַ���
		user.set_myPassword(newpassword);//�����û�����
		TreeNode *temp = userTree.treeSearch(user);//���ò��Һ�����Ѱ���Ƿ���ڸ��û�
		if (temp)//�����Ϊ��
		{
			string choice;
			cout << "��¼�ɹ���\n";
			cout << setfill('*') << setw(27) << "��¼����ҳ";
			for (int i = 0; i < 20; i++)cout << '*';//��������Ԫ��
			//�޸����빦��
			cout << "\n��ǰ���������޸���������\n" << "1.����change�����޸��������\n" << "2.����back����������\n";
			while (cin >> choice){
				if (choice == "change"){
					update_password(temp);//�����޸����뺯��
					ofstream fout(userFile);
					userTree.inOrederTraversal(fout);//���޸ĺ��ֵд���ļ�
					fout.close();
					return;
				}
				else if (choice == "back"){
					return;
				}
				else{
					cout << "�����������������룡\n" << endl;
				}
			}


		}
		else//Ϊ��
		{
			cout << "��δע��,���������˵�����ע�ᣡ\n";
			return;
		}
	}

}
void Menu::register_into_file_tree(){//ע�����
	ofstream fout(userFile, ios::app);//���ļ�������β����ӷ�ʽ��
	if (!fout.is_open()){
		cerr << "Cannot open " << userFile << endl;
		exit(1);
	}
	char c = 26;
	char c1 = 27;
	cout << setfill(c1) << setw(27) << "���û�ע��";
	for (int i = 0; i < 20; i++)cout << c;//��������Ԫ��
	string account = "";
	char password[11];
	int i = 0;
	cout << "\n �����������û����Լ����룬Ϊ�����˻���ȫ�����볤��Ҫ��С��6������10\n";
	cout << "�û�����";
	cin >> account;
	user.set_myId(account);
	cout << endl;
	cout << "���룺";
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
		userTree.insertTreeNode(user);//�����д�����û�
		fout << user;//���ļ���д����û�
		cout << "ע��ɹ�\n";
	}
	else if (userTree.treeSearch(user) != NULL){
		cout << "���û��Ѿ����ڣ���ֱ�ӵ�¼\n";
	}
	else{
		cout << "ע��ʧ�ܣ����벻����Ҫ��\n";
	}

	fout.close();
}
void Menu::delete_from_file_tree(){//ɾ������
	ifstream inStream(userFile);
	Tree userTree;//������ʱ�����洢��ȡ����Ϣ
	UserInfo user;//������ʱ�û����洢��ȡ���û�
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
	cout << setfill(c1) << setw(27) << "ɾ������";
	for (int i = 0; i < 20; i++)cout << c;//��������Ԫ��
	ofstream fout(userFile);
	string account = "";
	char password[11];//����һλ��������
	int i = 0;
	cout << "\n �����������û����Լ����룬����Ҫ��С��6������10\n";
	cout << "�û�����";
	cin >> account;
	user.set_myId(account);
	cout << endl;
	cout << "���룺";
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
		cout << "\n"<<"���������ʽ����" << endl;
	}
	else{
		cout << "\n�ļ���û�д��˺���Ϣ��" << endl;
	}
	userTree.inOrederTraversal(fout);//д���ļ�
	fout.close();
}
void Menu::show_all_account(){//��������Ա����
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
	cout << setfill(c1) << setw(27) << "��������Ա";
	for (int i = 0; i < 20; i++)cout << c;//��������Ԫ��
	cout << "\n��ϵͳ�д��ڵ��û���Ϣ�����������ʾΪ��" << endl;
	userTree.outputTree();//��������������������ӡ��������
}
void Menu::update_password(TreeNode * temp){//�޸����빦��
	string newpass,oldpass ,id;
	cout << "Ϊ�����˻���ȫ����������룺\n";
	cin >> oldpass;
	if (oldpass == temp->getData()->get_myPassword()){//��Ҫ��һ����֤����
		cout << "��֤�ɹ���\n";
		cout << "�����������룺" << endl;
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
			temp->getData()->set_myPassword(newpassword);//ȡ�øýڵ��ָ��֮������޸�
			cout << "�޸ĳɹ��������µ�¼��\n";
		}
		else{
			cout << "�޸�ʧ�ܣ����벻����Ҫ��\n";
		}

	}
	else{
		cout << "���������֤ʧ�ܣ�" << endl;
	}

}
