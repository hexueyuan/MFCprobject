#pragma once

#include<string>
#include<iostream>
#include"rect.h"
#include "Canvas.h"

using namespace std;
/*
Square��̳���Rect��
�ڽӿ���û��̫��ı仯��Ψһ��������Squareֻ��һ������ֵ
������ֻ��Ҫ�߳�����
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
