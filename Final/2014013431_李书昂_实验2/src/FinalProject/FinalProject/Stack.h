/**************************************************************************

Copyright:MyCompany

Author: ���鰺

Date:2015-11-04

Description:ʵ��Stack���Լ���������

**************************************************************************/

#ifndef STACK_H
#define STACK_H
#include <iostream>
using namespace std;
class Node
{
public:
	char m_str;
	Node *next;
	Node *prior;
};
class Stack
{
public:
	Stack();
	~Stack();
	void   push(char str);  // ��ջ  
	void   pop();            // ��ջ  
	bool   isEmpty();        // �ж�ջ�Ƿ�Ϊ��   
	char   getTop();         // ���ջ��Ԫ��  
public:
	Node*  m_Top;     // ջ��  
	Node*  m_Bottom;  // ջ��  
};

#endif // !STACK_H
