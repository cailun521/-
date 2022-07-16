#include "workerManager.h"

WorkerManager::WorkerManager()
{

	//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);   //读文件
	if (!ifs.is_open())
	{
		//cout << "文件不存在！" << endl;
		//初始化属性
		//初始化人数为0
		this->m_EmpNum = 0;
		//初始化数组指针为空
		this->m_EmpArray = NULL;
		//初始化文件是否是空为true
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在但数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空
		//cout << "文件为空！" << endl;
		//初始化人数为0
		this->m_EmpNum = 0;
		//初始化数组指针为空
		this->m_EmpArray = NULL;
		//初始化文件是否是空为true
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在，并且有数据
	int num = this->get_EmpNum();
	//cout << "职工人数为： " << num << endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将文件中的数据，存到数组中
	this->init_Emp();
	//for (int i = 0; i < this->m_EmpNum; i++)
	//{
	//	cout << "职工编号： " << this->m_EmpArray[i]->m_Id 
	//		<< "职工姓名： " << this->m_EmpArray[i]->m_Name
	//		<< "部门编号： " << this->m_EmpArray[i]->m_DeptID << endl;
	//}
}

// 退出系统
void WorkerManager::Exit_System()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

//显示菜单
void WorkerManager::Show_Menu()
{
	cout << "*************************************************************" << endl;
	cout << "**************      欢迎使用职工管理系统！   ****************" << endl;
	cout << "******************     0、退出管理程序    *******************" << endl;
	cout << "******************     1、增加职工信息    *******************" << endl;
	cout << "******************     2、显示职工信息    *******************" << endl;
	cout << "******************     3、删除职工信息    *******************" << endl;
	cout << "******************     4、修改职工信息    *******************" << endl;
	cout << "******************     5、查找职工信息    *******************" << endl;
	cout << "******************     6、按照编号排序    *******************" << endl;
	cout << "******************     7、清空所有文档    *******************" << endl;
	cout << "*************************************************************" << endl;
	cout << endl;
}

//添加职工
void WorkerManager::Add_Emp()
{
	cout << "请输入需要添加的职工人数！" << endl;
	int addNum = 0; //保存用户输入的人数
	cin >> addNum;

	if (addNum > 0)
	{
		//添加
		//计算添加空间大小
		int newSize = addNum + this->m_EmpNum; //新空间人数 = 原人数 + 新增人数

		//开辟空间
		Worker** newSpace = new Worker * [newSize];

		//将原来空间中的数据，拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//批量添加数据
		for (int i = 0; i < addNum; i++)
		{
			int id; //职工编号
			string name; //职工姓名
			int dSelect; //部门选择

			cout << "请输入第 " << i + 1 << "个职工的编号！" << endl;
			cin >> id;
			cout << "请输入第 " << i + 1 << "个职工的姓名！" << endl;
			cin >> name;
			cout << "请选择该职工岗位！" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			//将创建的职工指针，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原有的空间
		delete[] this->m_EmpArray;

		//更新新空间的指向
		this->m_EmpArray = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		//更新职工文件不为空的标志
		this->m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加了 " << addNum << "名新职工！" << endl;

		this->save();
	}
	else
	{
		cout << "输入数据有误！" << endl;
	}
	
	//按任意键后，清屏后回到上级目录
	system("pause");
	system("cls");
}

//保存文件
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);   //以写文件的方式打开文件

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptID << endl;
	}

	ofs.close();
}

//统计文件中的人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //打开文件  读
	 
	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id >> name >> dId)
	{
		num++;
	}
	return num;
}

//初始化员工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;

		if (dId == 1)  //普通职工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)  //经理
		{
			worker = new Manager(id, name, dId);
		}
		else  //老板
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}

	ifs.close();
}

//显示职工
void WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	 }
	else
	{
		//按照员工编号删除
		cout << "请输入要删除的员工编号： " << endl;
		int id = 0;
		cin >> id; 

		int index = this->isExist(id);
		if (index != -1) {   //说明职工存在，并且要删除掉index位置上的职工 
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;   //更新数组中的人员个数

			this->save();  //将数据保存到文件中
			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//判断职工是否存在，如果存在返回职工所在数组中的位置，不存在返回-1
int WorkerManager::isExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//找到职工
			index = i;
			break;
		}
	}

	return index;
}

//修改职工信息
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入要修改的职工的编号： " << endl;
		int id;
		cin >> id;

		int ret = this->isExist(id);
		if (ret != -1)
		{
			cout << "找到该员工了，编号为： " << id << endl;
			delete this->m_EmpArray[ret]; //释放之前存放该员工信息的空间
			
			int nId;
			string nName;
			int nDid;

			cout << "请输入修改后的员工编号： " << endl;
			cin >> nId;
			cout << "请输入修改后的员工姓名： " << endl;
			cin >> nName;
			cout << "请选择修改后的员工岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> nDid;

			Worker* worker = NULL;
			switch (nDid)
			{
			case 1:
				worker = new Employee(nId, nName, nDid);
				break;
			case 2:
				worker = new Manager(nId, nName, nDid);
				break;
			case 3:
				worker = new Boss(nId, nName, nDid);
				break;
			default:
				break;
			}
			this->m_EmpArray[ret] = worker;

			cout << "修改成功！" << endl;
			this->save();
		}
		else
		{
			cout << "修改失败，查无此人！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//查找职工
void WorkerManager::Fing_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请选择查找方式！" << endl;
		cout << "1、按照员工编号查找" << endl;
		cout << "2、按照员工姓名查找" << endl;
		int selector;
		cin >> selector;
		int flag = false;
		if (selector == 1)
		{
			cout << "请输入要查找的员工的编号！" << endl;
			int id;
			cin >> id;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Id == id)
				{
					//找到职工
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "查找失败，查无此人！" << endl;
			}
		}
		else
		{
			cout << "请输入要查找的员工的姓名！" << endl;
			string name;
			cin >> name;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					//找到职工
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "查找失败，查无此人！" << endl;
			}
		}
	}
	system("pause");
	system("cls");
}

//排序
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式！" << endl;
		cout << "1、按照职工编号进行升序" << endl;
		cout << "2、按照职工编号进行降序" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;  //声明最小值或最大值下标
			for (int j = i + 1; j < m_EmpNum; j++)
			{
				if (select == 1)   //升序
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else   //降序
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}

			//判断一开始认定的最小值或最大值，是不是计算的最小值或最大值，如果不是，就交换
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "排序成功！排序后的结果为： " << endl;
		this->save();
		this->Show_Emp();
	}
}

//清空
void WorkerManager::Clean_Emp()
{
	cout << "确定清空？" << endl;
	cout << "1、确定" << endl;
	cout << "2、取消" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//删除堆区的每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}

			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		system("cls");
	}
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}