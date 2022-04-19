#include "workermanager.h"
workermanager::workermanager()
{
	////初始化人数
	//this->m_empnum = 0;

	////初始化数组指针
	//this->m_emparray = NULL;
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	//文件不存在	
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		this->m_empnum = 0; //初始化人数
		this->m_fileisempty = true; //初始化文件为空
		this->m_emparray = NULL; //初始化数组
		ifs.close();
		return;
	}

	//文件存在，但没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->m_empnum = 0;
		this->m_emparray = NULL;
		this->m_fileisempty = true;
		ifs.close();
		return;
	}

	int num = this->get_empnum();
	cout << "当前已存在的职工个数: " << num << endl;
	this->m_empnum = num;//更新成员属性
	//根据职工数创建数组
	this->m_emparray = new worker *[this->m_empnum];
	//初始化员工
	init_emp();

	//测试代码
	for (int i = 0; i < m_empnum; i++)
	{
		cout << "职工号： " << this->m_emparray[i]->m_id
			<< " 职工姓名： " << this->m_emparray[i]->m_name
			<< " 部门编号： " << this->m_emparray[i]->m_deptid << endl;
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

		this->save();
		//提示信息
		cout << "成功添加" << addnum << "名新职工" << endl;
		this->m_fileisempty = false;

	}
	else
	{
		cout << "输入有误" << endl;
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
		//记录人数;
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
		//根据不同的部门id创建不同的对象
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
		//存放在数组中
		this->m_emparray[index] = worker;
		index++;
	}
}

void workermanager::show_emp()
{
	if (this->m_fileisempty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < m_empnum; i++)
		{
			//利用多态调用接口
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
		cout << "文件不存在或记录为空！" << endl;
	}

	else
	{
		//按职工编号删除
		cout << "请输入想要删除的职工号：" << endl;
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

			this->save();  //删除数据后同步到文件

			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}

	}

	system("pause");
	system("cls");
}

void workermanager::mod_emp()
{
	if (this->m_fileisempty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号：" << endl;
		int id;
		cin >> id;
		int ret = this->isexist(id);
		if (ret != -1)
		{
			//查找到寻妖修改的编号
			delete this->m_emparray[ret];
			int newid = 0;
			string newname = "";
			int dselect = 0;

			cout << "查到： " << id << "号职工，请输入新职工号： " << endl;
			cin >> newid;

			cout << "请输入新姓名： " << endl;
			cin >> newname;

			cout << "请输入岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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

			//更改rmp数组
			this->m_emparray[ret] = worker;

			cout << "修改成功" << endl;

			//保存
			this->save();

		}
		else
		{
			cout << "修改失败，查无此人" << endl;
		}
	}


	system("pause");
	system("cls");
}

void workermanager::find_emp()
{
	if (this->m_fileisempty)
	{
		cout << "文件不存在或者为空" << endl;
	}
	else
	{
		cout << "请输入查找的方式" << endl;
		cout << "1.按职工查找" << endl;
		cout << "2.按姓名查找" << endl;

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "请输入查找的职工编号: " << endl;
			cin >> id;

			int ret = isexist(id);
			if (ret != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_emparray[ret]->showinfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}

		}
		else if (select == 2)
		{
			string name;
			cout << "请输入要查找的名字" << endl;
			cin >> name;

			bool flag = false; //查找到的标志
			for (int i = 0; i < m_empnum; i++)
			{
				if (this->m_emparray[i]->m_name == name)
				{
					flag = true;
					cout << "查找成功,职工编号为："
						<< m_emparray[i]->m_id
						<< " 号的信息如下：" << endl;
					this->m_emparray[i]->showinfo();

				}
			}
			if (flag == false)
			{
				//查无此人
				cout << "查找失败，查无此人" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
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
	//哨兵划分
	int mid_id = partition(m_emparray, l, r);
	quicksort(m_emparray, l, mid_id - 1);
	quicksort(m_emparray, mid_id+1, r);
}
void workermanager::sort_emp()
{
	if (this->m_fileisempty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		quicksort(m_emparray, 0, m_empnum - 1);
		cout << "排序成功,排序结果为" << endl;
		this->save();
		this->show_emp();

	}

}

void workermanager::clean_file()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//打开模式 ios::trunc 如果存在删除文件并重新创建
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
		cout << "清空成功" << endl;
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
		cout << "请输入选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:  //退出系统
			wm.exitsystem();
			break;
		case 1:  //添加职工
			wm.add_emp();
			break;
		case 2: //显示职工
			wm.show_emp();
			break;
		case 3: //删除职工
			wm.del_emp();
			break;
		case 4: //修改职工
			wm.mod_emp();
			break;
		case 5:	//查找职工
			wm.find_emp();
			break;
		case 6: //排序职工
			wm.sort_emp();
			break;
		case 7: //清空文件
			wm.clean_file();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
}