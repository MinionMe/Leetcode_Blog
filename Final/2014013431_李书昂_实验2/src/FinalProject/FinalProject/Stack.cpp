#include "Stack.h"


Stack::Stack()
{
	m_Top = m_Bottom = NULL;
}
Stack::~Stack()
{
	while (m_Top != m_Bottom)
	{
		Node *pTmpNode = m_Bottom;
		m_Bottom = m_Bottom->next;
		delete pTmpNode;
	}
	delete m_Top;
}
bool Stack::isEmpty()
{
	if (m_Bottom == NULL && m_Top == NULL)
		return true;
	else
		return false;
}
void Stack::push(char str)   //stack ´¦Àí
{
	Node *ptempNode = new Node;
	ptempNode->m_str = str;
	if (isEmpty())
	{
		m_Top = ptempNode;
		m_Bottom = m_Top;
		m_Bottom->prior = NULL;
		m_Bottom->next = NULL;
	}
	else
	{
		m_Top->next = ptempNode;
		ptempNode->prior = m_Top;
		m_Top = m_Top->next;
		m_Top->next = NULL;
	}
}
char Stack::getTop()
{
	return m_Top->m_str;
}
void Stack::pop()
{
	if (isEmpty())
	{
		cout << "Õ»Îª¿Õ" << endl;
		exit(0);
	}
	else
	{
		if (m_Top == m_Bottom)
			delete m_Top;
		else
		{
			m_Top = m_Top->prior;
			delete m_Top->next;
		}
	}
}