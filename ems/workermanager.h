#pragma once
#include <iostream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

//管理类实现员工的增删改查
class workermanager
{
public:
	workermanager();

	~workermanager();

	void show_menu();

	void exitsystem();

	//增加职工
	void add_emp();

	//记录文件中的人数个数
	int m_empnum;

	//员工数组的指针
	worker	** m_emparray;

};