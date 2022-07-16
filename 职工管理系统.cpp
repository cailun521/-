#include <iostream>
using namespace std;
#include "workerManager.h"

#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

int main()
{
	//���Դ���
	//Worker * worker = NULL;
	//worker = new Employee(1, "����", 1);
	//worker->showInfo();
	//delete worker;

	//Worker* manager = NULL;
	//manager = new Manager(2, "����", 2);
	//manager->showInfo();
	//delete manager;

	//Worker* boss = NULL;
	//boss = new Boss(3, "����", 3);
	//boss->showInfo();
	//delete boss;

	WorkerManager wm;
	int choice = 0;
	while (true)
	{
		wm.Show_Menu();
		cout << "������ѡ�" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:  //���
			wm.Add_Emp();
			break;
		case 2:  //��ʾ
			wm.Show_Emp();
			break;
		case 3:  //ɾ��
			wm.Del_Emp();
			break;
		case 4:  //�޸�
			wm.Mod_Emp();
			break;
		case 5:  //����
			wm.Fing_Emp();
			break;
		case 6:  //����
			wm.Sort_Emp();
			break;
		case 7:  //���
			wm.Clean_Emp();
			break;
		case 0:  //�˳�
			wm.Exit_System();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}