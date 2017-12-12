#pragma once

#include<string>
#include<iostream>
#include"quad.h"
#include "Canvas.h"

using namespace std;
/*
Para类继承了Quadrangle类，并实体化了两个接口
Para自身拥有两个成员变量width和height
补充了获取这两个成员变量的接口Width()和Height()
*/
class Para : public Quadrangle
{
public:
	Para(double w = 1, double h = 1, string nm = "Parallelogram") :width(w), height(h), Quadrangle(nm){};
	~Para() {};
	//定义两个接口
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

