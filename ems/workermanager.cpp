#include "workermanager.h"
workermanager::workermanager()
{
	//初始化人数
	this->m_empnum = 0;

	//初始化数组指针
	this->m_emparray = NULL;

}
workermanager::~workermanager()
{

}


void workermanager::show_menu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void workermanager::exitsystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void workermanager::add_emp()
{
	cout << "请输入增加职工的数量: " << endl;

	int addnum = 0;
	cin >> addnum;
	if (addnum > 0)
	{
		//计算新空间的大小
		int newsize = this->m_empnum + addnum;

		//开辟新空间
		worker **newspace = new worker*[newsize];

		//原空间下的内容存放在新空间
		if (this->m_emparray != NULL)
		{
			for (int i = 0; i < this->m_empnum; i++)
			{
				newspace[i] = this->m_emparray[i];
			}
		}
		//输入新数据
		for (int i = 0; i < addnum; i++)
		{
			int id;
			string name;
			int dselect;

			cout << "请输入第 " << i + 1 << "个新职工编号:" << endl;
			cin >> id;

			cout << "请输入第 " << i + 1 << " 个新职工姓名：" << endl;
			cin >> name;

			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dselect;

			worker * worker = NULL;
			switch (dselect)
			{
			case 1: //普通员工
				worker = new employee(id, name, 1);
				break;
			case 2: //经理
				worker = new manager(id, name, 2);
				break;
			case 3:  //老板
				worker = new boss(id, name, 3);
				break;
			default:
				break;
			}

			newspace[this->m_empnum + i] = worker;
		}

		//释放原有空间
		delete[] this->m_emparray;

		//更改新空间的指向
		this->m_emparray = newspace;

		//更新新的个数
		this->m_empnum = newsize;

		//提示信息
		cout << "成功添加" << addnum << "名新职工" << endl;

	}
	else
	{
		cout << "输入有误" << endl;
	}

	system("pause");
	system("cls");

}

void test01()
{
	worker *worker1 = NULL;
	worker1 = new employee(1, "张三", 1);
	worker1->showinfo();
	delete worker1;

	manager a = manager(2, "李四", 2);
	worker & worker2 = a;
	worker2.showinfo();
	/*delete &worker2;*/

	worker *worker3 = NULL;
	worker3 = new boss(3, "王五", 3);
	worker3->showinfo();
	delete worker3;
}

void test02()
{
	workermanager wm1;
	cout << "添加之前员工数量: " << wm1.m_empnum << endl;
	wm1.add_emp();

	cout << "添加之后员工数量: " << wm1.m_empnum << endl;
}


int main()
{
	test02();
	workermanager wm;
	int choice = 0;

	while (true)
	{
		wm.show_menu();
		cout << "请输入选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:  //退出系统
			wm.exitsystem();
		case 1:  //添加职工
			break;
		case 2: //显示职工
			break;
		case 3: //删除职工
			break;
		case 4: //修改职工
			break;
		case 5:	//查找职工
			break;
		case 6: //排序职工
			break;
		case 7: //清空文件
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
}