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
	cout << "�ϰ��ţ� " << this->m_Id
		<< "\t�ϰ������� " << this->m_Name
		<< "\t��λ�� " << this->getDeptName()
		<< "\t�ϰ�ְ�� ��������"
		<< endl;
}

string Boss::getDeptName()
{
	return string("�ϰ�");
}