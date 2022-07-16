#include <iostream>
#pragma once
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"

class WorkerManager
{
public:
	WorkerManager();

	//显示菜单
	void Show_Menu();

	//退出系统
	void Exit_System();

	//职工人数
	int m_EmpNum;

	//职工数组指针
	Worker** m_EmpArray;

	//添加职工
	void Add_Emp();

	//保存文件
	void save();

	//判断文件是否为空
	bool m_FileIsEmpty;

	//统计文件中的人数
	int get_EmpNum();

	//初始化员工
	void init_Emp();

	//显示职工
	void Show_Emp();

	//删除职工
	void Del_Emp();

	//判断职工是否存在，如果存在返回职工所在数组中的位置，不存在返回-1
	int isExist(int id);

	//修改职工信息
	void Mod_Emp();

	//查找职工
	void Fing_Emp();

	//排序
	void Sort_Emp();

	//清空
	void Clean_Emp();

	~WorkerManager();
};
