//main.cpp
#include"loginSystem.h"
#include<iomanip>
#include<conio.h>
using namespace std;
int main(){
	cout << "这是一个基于AVL平衡树计算机的登录模拟系统" << endl;
	Menu newMenu;
	int m;
	while (!newMenu.get_quit()){//判断quit的值来确定是否跳出循环
		newMenu.set_mode_set_menu();
		m = newMenu.get_menu();
		//根据m的值调用相应的函数
		if (m == 0){
			newMenu.check_from_file();
		}
		else if (m == 1){
			newMenu.register_into_file_tree();
		}
		else if (m == 2){
			newMenu.delete_from_file_tree();
		}
		else if(m == 3){
			break;
		}
		else if(m == 4){
			newMenu.show_all_account();
		}
		//错误处理
		else {
			cout << "输入有误，请重新输入！\n";
		}
	}


}