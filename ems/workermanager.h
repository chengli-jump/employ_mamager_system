#pragma once
#include <iostream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>
#define FILENAME "empfile.txt"

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

	//ְ����Ϣ����
	void save();

	//ͳ�ƴ浵�е�����
	int get_empnum();

	//��ʼ���浵�е�Ա������
	void init_emp();

	//��ʾְ��
	void show_emp();

	//ɾ��Ա��
	void del_emp();

	//�޸�ְ��
	void mod_emp();

	//����ְ��
	void find_emp();

	//����ְ��
	void sort_emp();

	//��������
	void quicksort(worker ** m_emparray,int l, int r);

	//�ڱ�����
	int partition(worker ** m_emparray, int l, int r);

	//ְ���Ƿ����
	int isexist(int id);

	//����ļ�
	void clean_file();

	//��¼�ļ��е���������
	int m_empnum;

	//Ա�������ָ��
	worker	** m_emparray;

	//��־empfile�ļ��Ƿ�Ϊ��
	bool m_fileisempty;

};