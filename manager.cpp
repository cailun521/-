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
	cout << "�����ţ� " << this->m_Id
		<< "\t���������� " << this->m_Name
		<< "\t��λ�� " << this->getDeptName()
		<< "\t����ְ�� ����ϰ���������"
		<< endl;
}

string Manager::getDeptName()
{
	return string("����");
}