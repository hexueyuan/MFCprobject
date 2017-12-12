#pragma once

#include<string>
#include<iostream>
#include"quad.h"
#include "Canvas.h"

using namespace std;
/*
Para��̳���Quadrangle�࣬��ʵ�廯�������ӿ�
Para����ӵ��������Ա����width��height
�����˻�ȡ��������Ա�����Ľӿ�Width()��Height()
*/
class Para : public Quadrangle
{
public:
	Para(double w = 1, double h = 1, string nm = "Parallelogram") :width(w), height(h), Quadrangle(nm){};
	~Para() {};
	//���������ӿ�
	void draw() const { Canvas::drawQuad(this); }
	double area() const { return width*height; }

	string what() const { return name; }

	double& Width() { return width; }
	double& Height() { return height; }

//	Para&operator=(const Para&pa)
//	{
//		name = pa.name;
//		width = pa.width;
//		height = pa.height;
//		return *this;
//	}
protected:
	double width;
	double height;
};

