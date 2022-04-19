#include "workermanager.h"
workermanager::workermanager()
{
	//��ʼ������
	this->m_empnum = 0;

	//��ʼ������ָ��
	this->m_emparray = NULL;

}
workermanager::~workermanager()
{

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

		//��ʾ��Ϣ
		cout << "�ɹ����" << addnum << "����ְ��" << endl;

	}
	else
	{
		cout << "��������" << endl;
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


int main()
{
	test02();
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
		case 1:  //���ְ��
			break;
		case 2: //��ʾְ��
			break;
		case 3: //ɾ��ְ��
			break;
		case 4: //�޸�ְ��
			break;
		case 5:	//����ְ��
			break;
		case 6: //����ְ��
			break;
		case 7: //����ļ�
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
}