#pragma once

#include "quad.h"
#include<iostream>
#include<string>

class List
{
protected:
	//定义链表节点数据结构
	struct Node
	{
		QUADPTR data;
		Node *next;
		Node(QUADPTR d) :data(d) {}
	} *head, *tail; 

	//链表的长度
	size_t len; 

public:
	//默认构造函数
	List() :head(NULL), tail(NULL) { len = 0; }
	//复制构造函数
	List(List const& l)
	{
		head = tail = NULL;
		Node *p = l.head;
		while (p != NULL)
		{
			this->push_back(p->data);
			p = p->next;
		}
		len = 0;
	}
	//析构函数，释放掉所有动态分配的节点!!
	~List()
	{
		Node *p = head, *q;
		while (p != NULL)
		{
			q = p;
			p = p->next;
			delete q;
		}
	};

	//返回链表的尾部节点
	Node *Tail() { return tail; }
	//返回链表的头部节点
	Node *Head() { return head; }
	//获取链表的长度
	size_t size() { return len; }

	//尾部插入节点
	void push_back(const QUADPTR quad)
	{
		Node *p = new Node(quad);

		p->next = NULL;
		if (tail == NULL) head = tail = p;
		else { tail->next = p; tail = p; }

		len++;//!!!
	}

	//删除头部节点，与list保持接口一致，返回值为链表长度
	int pop_back()
	{
		if (len == 0){ return len; }
			
		Node *c = head;

		//当链表只有一个节点时，head等于tail
		if (c == tail) {
			delete c;
			head = tail = NULL;
		}
		else {
			//求tail的直接前驱节点
			while (c->next != tail){ c++; }
			delete tail;
			tail = c;
			tail->next = NULL;
		}
		
		return --len;//!!!
	}

	//重载=操作符
	List& operator=(const List& l)
	{
		head = nullptr;
		tail = nullptr;
		len = 0;
		Node *p = l.head;
		while (p != nullptr)
		{
			this->push_back(p->data);
			p = p->next;
			len++;//!!!
		}		
		return *this;
	}

	//重载+=操作符
	List& operator+=(const QUADPTR& data)
	{
		this->push_back(data);
		return *this;
	}

	QUADPTR& operator[](size_t n)
	{
		Node *p = head;
		//检查输入索引的值，对于大于链表长度的只返回链表尾
		size_t k = (n <= len) ? n : len;

		for (size_t i = 1; i <= k; i++)
		{
			p = p->next;
		}
		return p->data;
	}

	//遍历函数???
	void traverse(void(*f)(const QUADPTR&))
	{
		Node *p = head;
		int i = 1;
		while (p != NULL)
		{
			cout << "第" << i++ << "个" << endl;
			f(p->data);
			p = p->next;				//请自行添加指针移动部分
		}
	}
};




