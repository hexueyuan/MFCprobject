#pragma once

#include<string>
#include<iostream>
#include"quad.h"
#include "Canvas.h"

using namespace std;
/*
Trapezoid类继承了Quadrangle类
声明了三个成员变量width1、width2和height
定义了area()函数
*/
class Trapezoid : public Quadrangle
{
public:
	Trapezoid(double w1 = 1, double w2 = 2, double h = 1, string nm = "Trapezoid") :width1(w1), width2(w2), height(h), Quadrangle(nm) {}
	~Trapezoid() {}

	void draw() const { Canvas::drawQuad(this); }
	double area() const { return (width1 + width2)*height / 2; }
	string what() const { return name; }

	double Width1()const { return width1; }
	double Width2()const { return width2; }
	double Height()const { return height; }

private:
	double width1;
	double width2;
	double height;
};
