//main.cpp
#include"loginSystem.h"
#include<iomanip>
#include<conio.h>
using namespace std;
int main(){
	cout << "����һ������AVLƽ����������ĵ�¼ģ��ϵͳ" << endl;
	Menu newMenu;
	int m;
	while (!newMenu.get_quit()){//�ж�quit��ֵ��ȷ���Ƿ�����ѭ��
		newMenu.set_mode_set_menu();
		m = newMenu.get_menu();
		//����m��ֵ������Ӧ�ĺ���
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
		//������
		else {
			cout << "�����������������룡\n";
		}
	}


}