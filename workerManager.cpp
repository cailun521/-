#include "workerManager.h"

WorkerManager::WorkerManager()
{

	//�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);   //���ļ�
	if (!ifs.is_open())
	{
		//cout << "�ļ������ڣ�" << endl;
		//��ʼ������
		//��ʼ������Ϊ0
		this->m_EmpNum = 0;
		//��ʼ������ָ��Ϊ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ��ǿ�Ϊtrue
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ����ڵ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//�ļ�Ϊ��
		//cout << "�ļ�Ϊ�գ�" << endl;
		//��ʼ������Ϊ0
		this->m_EmpNum = 0;
		//��ʼ������ָ��Ϊ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ��ǿ�Ϊtrue
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ����ڣ�����������
	int num = this->get_EmpNum();
	//cout << "ְ������Ϊ�� " << num << endl;
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ��е����ݣ��浽������
	this->init_Emp();
	//for (int i = 0; i < this->m_EmpNum; i++)
	//{
	//	cout << "ְ����ţ� " << this->m_EmpArray[i]->m_Id 
	//		<< "ְ�������� " << this->m_EmpArray[i]->m_Name
	//		<< "���ű�ţ� " << this->m_EmpArray[i]->m_DeptID << endl;
	//}
}

// �˳�ϵͳ
void WorkerManager::Exit_System()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

//��ʾ�˵�
void WorkerManager::Show_Menu()
{
	cout << "*************************************************************" << endl;
	cout << "**************      ��ӭʹ��ְ������ϵͳ��   ****************" << endl;
	cout << "******************     0���˳��������    *******************" << endl;
	cout << "******************     1������ְ����Ϣ    *******************" << endl;
	cout << "******************     2����ʾְ����Ϣ    *******************" << endl;
	cout << "******************     3��ɾ��ְ����Ϣ    *******************" << endl;
	cout << "******************     4���޸�ְ����Ϣ    *******************" << endl;
	cout << "******************     5������ְ����Ϣ    *******************" << endl;
	cout << "******************     6�����ձ������    *******************" << endl;
	cout << "******************     7����������ĵ�    *******************" << endl;
	cout << "*************************************************************" << endl;
	cout << endl;
}

//���ְ��
void WorkerManager::Add_Emp()
{
	cout << "��������Ҫ��ӵ�ְ��������" << endl;
	int addNum = 0; //�����û����������
	cin >> addNum;

	if (addNum > 0)
	{
		//���
		//������ӿռ��С
		int newSize = addNum + this->m_EmpNum; //�¿ռ����� = ԭ���� + ��������

		//���ٿռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ���ռ��е����ݣ��������¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//�����������
		for (int i = 0; i < addNum; i++)
		{
			int id; //ְ�����
			string name; //ְ������
			int dSelect; //����ѡ��

			cout << "������� " << i + 1 << "��ְ���ı�ţ�" << endl;
			cin >> id;
			cout << "������� " << i + 1 << "��ְ����������" << endl;
			cin >> name;
			cout << "��ѡ���ְ����λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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

			//��������ְ��ָ�룬���浽������
			newSpace[this->m_EmpNum + i] = worker;
		}

		//�ͷ�ԭ�еĿռ�
		delete[] this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//�����µ�ְ������
		this->m_EmpNum = newSize;

		//����ְ���ļ���Ϊ�յı�־
		this->m_FileIsEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ������ " << addNum << "����ְ����" << endl;

		this->save();
	}
	else
	{
		cout << "������������" << endl;
	}
	
	//���������������ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}

//�����ļ�
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);   //��д�ļ��ķ�ʽ���ļ�

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptID << endl;
	}

	ofs.close();
}

//ͳ���ļ��е�����
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //���ļ�  ��
	 
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

//��ʼ��Ա��
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

		if (dId == 1)  //��ְͨ��
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)  //����
		{
			worker = new Manager(id, name, dId);
		}
		else  //�ϰ�
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}

	ifs.close();
}

//��ʾְ��
void WorkerManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	 }
	else
	{
		//����Ա�����ɾ��
		cout << "������Ҫɾ����Ա����ţ� " << endl;
		int id = 0;
		cin >> id; 

		int index = this->isExist(id);
		if (index != -1) {   //˵��ְ�����ڣ�����Ҫɾ����indexλ���ϵ�ְ�� 
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;   //���������е���Ա����

			this->save();  //�����ݱ��浽�ļ���
			cout << "ɾ���ɹ���" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ����" << endl;
		}
	}
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ���ڣ�������ڷ���ְ�����������е�λ�ã������ڷ���-1
int WorkerManager::isExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//�ҵ�ְ��
			index = i;
			break;
		}
	}

	return index;
}

//�޸�ְ����Ϣ
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "������Ҫ�޸ĵ�ְ���ı�ţ� " << endl;
		int id;
		cin >> id;

		int ret = this->isExist(id);
		if (ret != -1)
		{
			cout << "�ҵ���Ա���ˣ����Ϊ�� " << id << endl;
			delete this->m_EmpArray[ret]; //�ͷ�֮ǰ��Ÿ�Ա����Ϣ�Ŀռ�
			
			int nId;
			string nName;
			int nDid;

			cout << "�������޸ĺ��Ա����ţ� " << endl;
			cin >> nId;
			cout << "�������޸ĺ��Ա�������� " << endl;
			cin >> nName;
			cout << "��ѡ���޸ĺ��Ա����λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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

			cout << "�޸ĳɹ���" << endl;
			this->save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴��ˣ�" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����ְ��
void WorkerManager::Fing_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��ѡ����ҷ�ʽ��" << endl;
		cout << "1������Ա����Ų���" << endl;
		cout << "2������Ա����������" << endl;
		int selector;
		cin >> selector;
		int flag = false;
		if (selector == 1)
		{
			cout << "������Ҫ���ҵ�Ա���ı�ţ�" << endl;
			int id;
			cin >> id;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Id == id)
				{
					//�ҵ�ְ��
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "����ʧ�ܣ����޴��ˣ�" << endl;
			}
		}
		else
		{
			cout << "������Ҫ���ҵ�Ա����������" << endl;
			string name;
			cin >> name;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					//�ҵ�ְ��
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "����ʧ�ܣ����޴��ˣ�" << endl;
			}
		}
	}
	system("pause");
	system("cls");
}

//����
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1������ְ����Ž�������" << endl;
		cout << "2������ְ����Ž��н���" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;  //������Сֵ�����ֵ�±�
			for (int j = i + 1; j < m_EmpNum; j++)
			{
				if (select == 1)   //����
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else   //����
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}

			//�ж�һ��ʼ�϶�����Сֵ�����ֵ���ǲ��Ǽ������Сֵ�����ֵ��������ǣ��ͽ���
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "����ɹ��������Ľ��Ϊ�� " << endl;
		this->save();
		this->Show_Emp();
	}
}

//���
void WorkerManager::Clean_Emp()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2��ȡ��" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//����ļ�
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}

			//ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ���" << endl;
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