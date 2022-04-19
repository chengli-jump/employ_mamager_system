#pragma once
#include <iostream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>
#define FILENAME "empfile.txt"

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

	//职工信息保存
	void save();

	//统计存档中的人数
	int get_empnum();

	//初始化存档中的员工数组
	void init_emp();

	//显示职工
	void show_emp();

	//删除员工
	void del_emp();

	//修改职工
	void mod_emp();

	//查找职工
	void find_emp();

	//排序职工
	void sort_emp();

	//快速排序
	void quicksort(worker ** m_emparray,int l, int r);

	//哨兵划分
	int partition(worker ** m_emparray, int l, int r);

	//职工是否存在
	int isexist(int id);

	//清空文件
	void clean_file();

	//记录文件中的人数个数
	int m_empnum;

	//员工数组的指针
	worker	** m_emparray;

	//标志empfile文件是否为空
	bool m_fileisempty;

};