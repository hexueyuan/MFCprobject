#pragma once

#include "quad.h"
#include<iostream>
#include<string>

template<class DATA> 
class List
{
protected:
	//��������ڵ����ݽṹ
	struct Node
	{
		DATA data;
		Node *next;
		Node(DATA d) :data(d) {}
	} *head, *tail; 

	//����ĳ���
	size_t len; 

public:
	//Ĭ�Ϲ��캯��
	List() :head(NULL), tail(NULL) { len = 0; }
	//���ƹ��캯��
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
	//�����������ͷŵ����ж�̬����Ľڵ�!!
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

	//���������β���ڵ�
	Node *Tail() { return tail; }
	//���������ͷ���ڵ�
	Node *Head() { return head; }
	//��ȡ����ĳ���
	size_t size() { return len; }

	//β������ڵ�
	void push_back(const DATA quad)
	{
		Node *p = new Node(quad);

		p->next = NULL;
		if (tail == NULL) head = tail = p;
		else { tail->next = p; tail = p; }

		len++;//!!!
	}

	//ɾ��ͷ���ڵ㣬��list���ֽӿ�һ�£�����ֵΪ������
	int pop_back()
	{
		if (len == 0){ return len; }
			
		Node *c = head;

		//������ֻ��һ���ڵ�ʱ��head����tail
		if (c == tail) {
			delete c;
			head = tail = NULL;
		}
		else {
			//��tail��ֱ��ǰ���ڵ�
			while (c->next != tail){ c++; }
			delete tail;
			tail = c;
			tail->next = NULL;
		}
		
		return --len;//!!!
	}

	//����=������
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

	//����+=������
	List& operator+=(const DATA& data)
	{
		this->push_back(data);
		return *this;
	}

	DATA& operator[](size_t n)
	{
		Node *p = head;
		//�������������ֵ�����ڴ��������ȵ�ֻ��������β
		size_t k = (n <= len) ? n : len;

		for (size_t i = 1; i <= k; i++)
		{
			p = p->next;
		}
		return p->data;
	}

	//��������
	void traverse(void(*f)(const DATA&))
	{
		Node *p = head;
		int i = 1;
		while (p != NULL)
		{
			cout << "��" << i++ << "��" << endl;
			f(p->data);
			p = p->next;				//���������ָ���ƶ�����
		}
	}

	Node* begin()
	{
		return head;
	}

	Node* end()
	{
		return tail->next;
	}

	public:
		class Iterator
		{
		private:
			Node* p;
		public:
			Iterator():p(nullptr) {}
			Iterator(Iterator& i):p(i.p){}
			~Iterator() {}

			Iterator& operator=(Iterator& i)
			{
				p = i.p;
				return *this;
			}

			Iterator& operator=(Node* n)
			{
				p = n;
				return *this;
			}

			Iterator& operator++()
			{
				p = p->next;
				return *this;
			}

			bool operator==(Iterator& i)
			{
				return (p == i.p);
			}

			bool operator!=(Iterator& i)
			{
				return !(*this!=i);
			}

			Iterator& operator+(int k)
			{
				while (k--)
				{
					p = p->next;
				}
				return *this;
			}

			Node& operator*()
			{
				return *p;
			}
		};
};
