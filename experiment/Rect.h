#pragma once

#include<string>
#include<iostream>
#include"para.h"
#include "Canvas.h"

using namespace std;
/*
Rect类继承了Para类
在接口和成员变量上并没有太大的变化
*/
class Rect : public Para
{
public:
	Rect(int w = 1, int h = 2, string nm = "Rectangle") :Para(w, h, nm) {}
	~Rect() {}

	string what()const { return name; }
	double area()const { return Para::area(); }
	void draw()const { Canvas::drawQuad(this); }

	double& Width(){ return width; }
	double& Height(){ return height; }
};

