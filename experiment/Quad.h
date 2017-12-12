#pragma once

#include<string>
#include "Canvas.h"

using namespace std;

/*
Quadrangle������ӵ��һ����Ա�����������ӿ�
һ����Ա������name
�����ӿڣ�area()��what()��draw()
����area()��draw()Ϊ���麯��
*/
class Quadrangle
{
public:
	string name; //����ı�ʶ
	Quadrangle(string nm = "Quadrangle") :name(nm) {}
	virtual double area() const = 0;
	string what() const { return name; };
	virtual void draw() const = 0;
};

//����Quadrangleָ�����ͱ���
typedef Quadrangle * QUADPTR;