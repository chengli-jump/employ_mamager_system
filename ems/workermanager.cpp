#include "workermanager.h"
workermanager::workermanager()
{
	////��ʼ������
	//this->m_empnum = 0;

	////��ʼ������ָ��
	//this->m_emparray = NULL;
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	//�ļ�������	
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		this->m_empnum = 0; //��ʼ������
		this->m_fileisempty = true; //��ʼ���ļ�Ϊ��
		this->m_emparray = NULL; //��ʼ������
		ifs.close();
		return;
	}

	//�ļ����ڣ���û�м�¼
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		this->m_empnum = 0;
		this->m_emparray = NULL;
		this->m_fileisempty = true;
		ifs.close();
		return;
	}

	int num = this->get_empnum();
	cout << "��ǰ�Ѵ��ڵ�ְ������: " << num << endl;
	this->m_empnum = num;//���³�Ա����
	//����ְ������������
	this->m_emparray = new worker *[this->m_empnum];
	//��ʼ��Ա��
	init_emp();

	//���Դ���
	for (int i = 0; i < m_empnum; i++)
	{
		cout << "ְ���ţ� " << this->m_emparray[i]->m_id
			<< " ְ�������� " << this->m_emparray[i]->m_name
			<< " ���ű�ţ� " << this->m_emparray[i]->m_deptid << endl;
	}

}
workermanager::~workermanager()
{
	if (this->m_emparray != NULL)
	{
		delete[] this->m_emparray;
	}
}


void workermanager::show_menu()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void workermanager::exitsystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void workermanager::add_emp()
{
	cout << "����������ְ��������: " << endl;

	int addnum = 0;
	cin >> addnum;
	if (addnum > 0)
	{
		//�����¿ռ�Ĵ�С
		int newsize = this->m_empnum + addnum;

		//�����¿ռ�
		worker **newspace = new worker*[newsize];

		//ԭ�ռ��µ����ݴ�����¿ռ�
		if (this->m_emparray != NULL)
		{
			for (int i = 0; i < this->m_empnum; i++)
			{
				newspace[i] = this->m_emparray[i];
			}
		}
		//����������
		for (int i = 0; i < addnum; i++)
		{
			int id;
			string name;
			int dselect;

			cout << "������� " << i + 1 << "����ְ�����:" << endl;
			cin >> id;

			cout << "������� " << i + 1 << " ����ְ��������" << endl;
			cin >> name;

			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dselect;

			worker * worker = NULL;
			switch (dselect)
			{
			case 1: //��ͨԱ��
				worker = new employee(id, name, 1);
				break;
			case 2: //����
				worker = new manager(id, name, 2);
				break;
			case 3:  //�ϰ�
				worker = new boss(id, name, 3);
				break;
			default:
				break;
			}

			newspace[this->m_empnum + i] = worker;
		}

		//�ͷ�ԭ�пռ�
		delete[] this->m_emparray;

		//�����¿ռ��ָ��
		this->m_emparray = newspace;

		//�����µĸ���
		this->m_empnum = newsize;

		this->save();
		//��ʾ��Ϣ
		cout << "�ɹ����" << addnum << "����ְ��" << endl;
		this->m_fileisempty = false;

	}
	else
	{
		cout << "��������" << endl;
	}

	system("pause");
	system("cls");

}
void workermanager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i=0; i< this->m_empnum; i++)
	{
		ofs << this->m_emparray[i]->m_id << " "
			<< this->m_emparray[i]->m_name << " "
			<< this->m_emparray[i]->m_deptid << endl;
	}
	ofs.close();
}

int workermanager::get_empnum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		//��¼����;
		num++;
	}
	ifs.close();
	return num;

}

void workermanager::init_emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		worker *worker = NULL;
		//���ݲ�ͬ�Ĳ���id������ͬ�Ķ���
		if (did == 1)
		{
			worker = new employee(id, name, did);

		}
		else if (did == 2)
		{
			worker = new manager(id, name, did);
		}
		else
		{
			worker = new boss(id, name, did);
		}
		//�����������
		this->m_emparray[index] = worker;
		index++;
	}
}

void workermanager::show_emp()
{
	if (this->m_fileisempty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < m_empnum; i++)
		{
			//���ö�̬���ýӿ�
			this->m_emparray[i]->showinfo();
		}
	}
	system("pause");
	system("cls");
}

int workermanager::isexist(int id)
{
	int index = -1;
	for (int i = 0; i < m_empnum; i++)
	{
		if (this->m_emparray[i]->m_id == id)
		{
			index = i;
			break;
		}
	}

	return index;
}

void workermanager::del_emp()
{
	if (this->m_fileisempty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}

	else
	{
		//��ְ�����ɾ��
		cout << "��������Ҫɾ����ְ���ţ�" << endl;
		int id = 0;
		cin >> id;

		int index = isexist(id);
		if (index != -1)
		{
			for (int i = index; i < m_empnum - 1; i++)
			{
				m_emparray[i] = m_emparray[i + 1];
			}
			this->m_empnum--;

			this->save();  //ɾ�����ݺ�ͬ�����ļ�

			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}

	}

	system("pause");
	system("cls");
}

void workermanager::mod_emp()
{
	if (this->m_fileisempty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "�������޸�ְ���ı�ţ�" << endl;
		int id;
		cin >> id;
		int ret = this->isexist(id);
		if (ret != -1)
		{
			//���ҵ�Ѱ���޸ĵı��
			delete this->m_emparray[ret];
			int newid = 0;
			string newname = "";
			int dselect = 0;

			cout << "�鵽�� " << id << "��ְ������������ְ���ţ� " << endl;
			cin >> newid;

			cout << "�������������� " << endl;
			cin >> newname;

			cout << "�������λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dselect;

			worker * worker = NULL;
			switch (dselect)
			{
			case 1:
				worker = new employee(newid, newname, dselect);
				break;
			case 2:
				worker = new manager(newid, newname, dselect);
				break;
			case 3:
				worker = new boss(newid, newname, dselect);
				break;
			default:
				break;
			}

			//����rmp����
			this->m_emparray[ret] = worker;

			cout << "�޸ĳɹ�" << endl;

			//����
			this->save();

		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		}
	}


	system("pause");
	system("cls");
}

void workermanager::find_emp()
{
	if (this->m_fileisempty)
	{
		cout << "�ļ������ڻ���Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ" << endl;
		cout << "1.��ְ������" << endl;
		cout << "2.����������" << endl;

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "��������ҵ�ְ�����: " << endl;
			cin >> id;

			int ret = isexist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_emparray[ret]->showinfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}

		}
		else if (select == 2)
		{
			string name;
			cout << "������Ҫ���ҵ�����" << endl;
			cin >> name;

			bool flag = false; //���ҵ��ı�־
			for (int i = 0; i < m_empnum; i++)
			{
				if (this->m_emparray[i]->m_name == name)
				{
					flag = true;
					cout << "���ҳɹ�,ְ�����Ϊ��"
						<< m_emparray[i]->m_id
						<< " �ŵ���Ϣ���£�" << endl;
					this->m_emparray[i]->showinfo();

				}
			}
			if (flag == false)
			{
				//���޴���
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}
int workermanager::partition(worker ** m_emparray, int l, int r)
{
	int i = l, j = r;
	while (i < j)
	{
		while (i<j && m_emparray[j]->m_id >=  m_emparray[l]->m_id)j--;
		while (i < j && m_emparray[i]->m_id <= m_emparray[l]->m_id) i++;
		worker *temp = m_emparray[i];
		m_emparray[i] = m_emparray[j];
		m_emparray[j] = temp;
	}
	worker *temp = m_emparray[i];
	m_emparray[i] = m_emparray[l];
	m_emparray[l] = temp;
	return i;
}
void workermanager::quicksort(worker ** m_emparray, int l, int r)
{
	if (l > r)
	{
		return;
	}
	//�ڱ�����
	int mid_id = partition(m_emparray, l, r);
	quicksort(m_emparray, l, mid_id - 1);
	quicksort(m_emparray, mid_id+1, r);
}
void workermanager::sort_emp()
{
	if (this->m_fileisempty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		quicksort(m_emparray, 0, m_empnum - 1);
		cout << "����ɹ�,������Ϊ" << endl;
		this->save();
		this->show_emp();

	}

}

void workermanager::clean_file()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//��ģʽ ios::trunc �������ɾ���ļ������´���
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_emparray != NULL)
		{
			for (int i = 0; i < this->m_empnum; i++)
			{
				if (this->m_emparray[i] != NULL)
				{
					delete this->m_emparray[i];
				}
			}
			this->m_empnum = 0;
			delete[] this->m_emparray;
			this->m_emparray = NULL;
			this->m_fileisempty = true;
		}
		cout << "��ճɹ�" << endl;
	}

	system("pause");
	system("cls");
}

void test01()
{
	worker *worker1 = NULL;
	worker1 = new employee(1, "����", 1);
	worker1->showinfo();
	delete worker1;

	manager a = manager(2, "����", 2);
	worker & worker2 = a;
	worker2.showinfo();
	/*delete &worker2;*/

	worker *worker3 = NULL;
	worker3 = new boss(3, "����", 3);
	worker3->showinfo();
	delete worker3;
}

void test02()
{
	workermanager wm1;
	cout << "���֮ǰԱ������: " << wm1.m_empnum << endl;
	wm1.add_emp();

	cout << "���֮��Ա������: " << wm1.m_empnum << endl;
}

void test03()
{
	workermanager wm1;
	wm1.get_empnum();
}


int main()
{
	/*test03();*/
	workermanager wm;
	int choice = 0;

	while (true)
	{
		wm.show_menu();
		cout << "������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:  //�˳�ϵͳ
			wm.exitsystem();
			break;
		case 1:  //���ְ��
			wm.add_emp();
			break;
		case 2: //��ʾְ��
			wm.show_emp();
			break;
		case 3: //ɾ��ְ��
			wm.del_emp();
			break;
		case 4: //�޸�ְ��
			wm.mod_emp();
			break;
		case 5:	//����ְ��
			wm.find_emp();
			break;
		case 6: //����ְ��
			wm.sort_emp();
			break;
		case 7: //����ļ�
			wm.clean_file();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
}