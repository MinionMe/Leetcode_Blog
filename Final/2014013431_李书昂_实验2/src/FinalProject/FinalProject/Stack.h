/**************************************************************************

Copyright:MyCompany

Author: 李书昂

Date:2015-11-04

Description:实现Stack类以及基本操作

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
	void   push(char str);  // 进栈  
	void   pop();            // 出栈  
	bool   isEmpty();        // 判断栈是否为空   
	char   getTop();         // 获得栈顶元素  
public:
	Node*  m_Top;     // 栈顶  
	Node*  m_Bottom;  // 栈底  
};

#endif // !STACK_H
