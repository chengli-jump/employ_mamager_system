#pragma once
#include <iostream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

//������ʵ��Ա������ɾ�Ĳ�
class workermanager
{
public:
	workermanager();

	~workermanager();

	void show_menu();

	void exitsystem();

	//����ְ��
	void add_emp();

	//��¼�ļ��е���������
	int m_empnum;

	//Ա�������ָ��
	worker	** m_emparray;

};