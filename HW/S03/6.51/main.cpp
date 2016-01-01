#include <iostream>
#include <stack>
#include <string>
#include <queue>
using namespace std;

typedef struct BiTNode{
	char m_data;
	struct BiTNode *lchild, *rchild;      //lchild,rchild�ֱ�Ϊ�ڵ�����ӣ��Һ���ָ��
	int priority;
}BiTNode, *BiTree;
void CrtExpTree(BiTree &T, stack<BiTree> &Ptr);
void CrtNode(BiTree &T, char ch, stack<BiTree> &Ptr);
string getResult(BiTree &T, stack<BiTree> &Ptr);

int main()
{
	BiTree tree;
	stack<BiTree> Ptr;
	string s;
	CrtExpTree(tree, Ptr);
	s = getResult(tree, Ptr);
	cout << s << endl;
	return 0;
}

void CrtNode(BiTree &T, char ch, stack<BiTree> &Ptr)
{
	T = new BiTNode;
	T->m_data = ch;
	switch (ch)
	{
	case '+':
		T->priority = 1;
		break;
	case '-':
		T->priority = 2;
		break;
	case '*':
		T->priority = 3;
		break;
	case '/':
		T->priority = 4;
		break;
	default:
		T->priority = 0;
		break;
	}
	T->lchild = T->rchild = NULL;
	Ptr.push(T);
}
void CrtExpTree(BiTree &T, stack<BiTree> &Ptr)
{
	string s,tempstr;
	BiTree LNode, RNode, p;
	getline(cin, s);
	if (s.empty())
	{
		T = NULL;
		return;
	}
	if (s.length() == 1)
	{
		CrtNode(T,s[0],Ptr);
		return;
	}
	for (int i = 0; i < s.length(); i++)
	{
		switch (s[i])
		{
		case '(':
		case ',':
			break;
		case ')':
			RNode = Ptr.top();
			Ptr.pop();
			LNode = Ptr.top();
			Ptr.pop();
			p = Ptr.top();
			p->lchild = LNode;
			p->rchild = RNode;
			break;
		default: 
			CrtNode(T, s[i], Ptr);
			break;
		}
	}
	T = Ptr.top();
	Ptr.pop();
}
string getResult(BiTree &T, stack<BiTree> &Ptr)
{
	BiTree p = T;
	string tempstr;
	if (p == NULL)
	{
		return "";
	}
	if (p->lchild == NULL && p->rchild == NULL)
	{
		tempstr += p->m_data;
		return tempstr;
	}
	if (p->lchild->priority == 0)
	{
		tempstr += p->lchild->m_data;
	}
	else
	{
		if (p->priority > p->lchild->priority)
		{
			tempstr += '(' + getResult(p->lchild, Ptr) + ')';
		}
		else
			tempstr += getResult(p->lchild, Ptr);
	} 
	tempstr += p->m_data;
	if (p->rchild->priority == 0)
	{
		tempstr += p->rchild->m_data; 
	}
	else
	{
		if (p->priority > p->rchild->priority)
		{
			tempstr += '(' + getResult(p->rchild, Ptr) + ')';
		}
		else
			tempstr += getResult(p->rchild, Ptr);
	} 
	return tempstr;
}