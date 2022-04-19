#pragma once
#include <iostream>
using namespace std;
#include "worker.h";

//普通员工类，继承职工类，并重写纯虚函数
class employee : public worker
{
public:
	//构造函数
	employee(int id, string name, int did);

	//显示个人信息
	virtual void showinfo();

	//获取职工岗位
	virtual string getdeptname();
};