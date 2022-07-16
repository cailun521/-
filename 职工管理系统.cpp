#include <iostream>
using namespace std;
#include "workerManager.h"

#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

int main()
{
	//测试代码
	//Worker * worker = NULL;
	//worker = new Employee(1, "张三", 1);
	//worker->showInfo();
	//delete worker;

	//Worker* manager = NULL;
	//manager = new Manager(2, "李四", 2);
	//manager->showInfo();
	//delete manager;

	//Worker* boss = NULL;
	//boss = new Boss(3, "王五", 3);
	//boss->showInfo();
	//delete boss;

	WorkerManager wm;
	int choice = 0;
	while (true)
	{
		wm.Show_Menu();
		cout << "请输入选项！" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:  //添加
			wm.Add_Emp();
			break;
		case 2:  //显示
			wm.Show_Emp();
			break;
		case 3:  //删除
			wm.Del_Emp();
			break;
		case 4:  //修改
			wm.Mod_Emp();
			break;
		case 5:  //查找
			wm.Fing_Emp();
			break;
		case 6:  //排序
			wm.Sort_Emp();
			break;
		case 7:  //清空
			wm.Clean_Emp();
			break;
		case 0:  //退出
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