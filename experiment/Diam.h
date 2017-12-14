#pragma once

#include<string>
#include<iostream>
#include "Canvas.h"
#include"para.h"

using namespace std;
/*
Diamond�̳���Para��
������������Ա����dd1��dd2�����Խ���
���¶�����area()����
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

