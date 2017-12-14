#pragma once

#include<string>
#include<iostream>
#include"para.h"
#include "Canvas.h"

using namespace std;
/*
Rect��̳���Para��
�ڽӿںͳ�Ա�����ϲ�û��̫��ı仯
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

