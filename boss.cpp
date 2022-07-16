#include "boss.h"
using namespace std;

Boss::Boss(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptID = dId;
}

void Boss::showInfo()
{
	cout << "老板编号： " << this->m_Id
		<< "\t老板姓名： " << this->m_Name
		<< "\t岗位： " << this->getDeptName()
		<< "\t老板职责： 分配任务！"
		<< endl;
}

string Boss::getDeptName()
{
	return string("老板");
}