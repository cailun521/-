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

	//��ʾ�˵�
	void Show_Menu();

	//�˳�ϵͳ
	void Exit_System();

	//ְ������
	int m_EmpNum;

	//ְ������ָ��
	Worker** m_EmpArray;

	//���ְ��
	void Add_Emp();

	//�����ļ�
	void save();

	//�ж��ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

	//ͳ���ļ��е�����
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	//��ʾְ��
	void Show_Emp();

	//ɾ��ְ��
	void Del_Emp();

	//�ж�ְ���Ƿ���ڣ�������ڷ���ְ�����������е�λ�ã������ڷ���-1
	int isExist(int id);

	//�޸�ְ����Ϣ
	void Mod_Emp();

	//����ְ��
	void Fing_Emp();

	//����
	void Sort_Emp();

	//���
	void Clean_Emp();

	~WorkerManager();
};
