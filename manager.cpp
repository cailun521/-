#include "manager.h"
using namespace std;

Manager::Manager(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptID = dId;
}

void Manager::showInfo()
{
	cout << "经理编号： " << this->m_Id
		<< "\t经理姓名： " << this->m_Name
		<< "\t岗位： " << this->getDeptName()
		<< "\t经理职责： 完成老板分配的任务！"
		<< endl;
}

string Manager::getDeptName()
{
	return string("经理");
}