#pragma once
#include <iostream>
using namespace std;
#include "worker.h";

//��ͨԱ���࣬�̳�ְ���࣬����д���麯��
class employee : public worker
{
public:
	//���캯��
	employee(int id, string name, int did);

	//��ʾ������Ϣ
	virtual void showinfo();

	//��ȡְ����λ
	virtual string getdeptname();
};