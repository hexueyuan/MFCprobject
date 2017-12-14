#pragma once

#include<string>
#include<iostream>
#include "Canvas.h"
#include"para.h"

using namespace std;
/*
Diamond继承了Para类
声明了两个成员变量dd1和dd2两条对角线
重新定义了area()函数
*/
class Diamond : public Para
{
public:
	Diamond(double d1 = 1, double d2 = 2, string nm = "Diamond") :dd1(d1),dd2(d2),Para(d1,d2,nm) {};
	~Diamond() {};

	void draw() const { Para::draw(); }
	double area() const { return dd1*dd2 / 2; }
	string what() const { return name; }

	double& Width1() { return dd1; }
	double& Width2() { return dd2; }

protected:
	double dd1, dd2;

};

