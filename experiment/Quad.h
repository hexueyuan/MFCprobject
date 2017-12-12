#pragma once

#include<string>
#include "Canvas.h"

using namespace std;

/*
Quadrangle抽象类拥有一个成员变量和三个接口
一个成员变量：name
三个接口：area()、what()、draw()
其中area()和draw()为纯虚函数
*/
class Quadrangle
{
public:
	string name; //形体的标识
	Quadrangle(string nm = "Quadrangle") :name(nm) {}
	virtual double area() const = 0;
	string what() const { return name; };
	virtual void draw() const = 0;
};

//定义Quadrangle指针类型变量
typedef Quadrangle * QUADPTR;