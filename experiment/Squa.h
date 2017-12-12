#pragma once

#include<string>
#include<iostream>
#include"rect.h"
#include "Canvas.h"

using namespace std;
/*
Square类继承了Rect类
在接口上没有太大的变化，唯一的区别是Square只有一个特征值
正方形只需要边长即可
*/
class Square : public Rect
{
public:
	Square(int w = 6, string nm = "Square") :Rect(w, w, nm) {};
	~Square() {};

	void draw() const { Rect::draw(); };
	double area() const { return width*width; }
	string what() const { return name; }

	double& Width() { return width; };

//	Square&operator=(const Square&sq)
//	{
//		name = sq.name;
//		width = sq.width;
//		return *this;
//	}
};
