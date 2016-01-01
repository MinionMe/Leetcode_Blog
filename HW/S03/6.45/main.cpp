#include <iostream>
#include <stack>
#include <string>
using namespace std;

typedef struct BiTNode{
	char m_data;
	struct BiTNode *lchild, *rchild;
	//lchild,rchild分别为节点的左孩子，右孩子指针
}BiTNode, *BiTree;
void CrtExpTree(BiTree &T,stack<BiTree> &Ptr);
void CrtNode(BiTree &T, char ch, stack<BiTree> &Ptr);
void DeleteNode(BiTree &tree,char ch);
void PrintTree(BiTree &tree,string &s);

int main()
{
	BiTree tree;
	char ch;
	string s;
	stack<BiTree> Ptr;
	CrtExpTree(tree,Ptr);
	cin >> ch;
	DeleteNode(tree, ch);
	PrintTree(tree, s);
	cout << s;
	return 0;
}

void CrtNode(BiTree &T, char ch, stack<BiTree> &Ptr)
{
	T = new BiTNode;
	T->m_data = ch;
	T->lchild = T->rchild = NULL;
	Ptr.push(T);
}
void CrtExpTree(BiTree &T, stack<BiTree> &Ptr)
{
	string s;
	BiTree LNode, RNode, p;
	getline(cin,s);
	if (s.empty())
	{
		T = NULL;
		return;
	}
	for (int i = 0; i < s.length(); i++)
	{
		switch (s[i])
		{
		case '(':
			if (s[i + 1] == ',')
			{
				CrtNode(T, '0', Ptr);
			}
			break;
		case ',':
			if (s[i + 1] == ')')
			{
				CrtNode(T, '0', Ptr);
			}
			break;
		case ')':
			if (i == s.length() - 1 && Ptr.size() == 2)
			{
				CrtNode(T, '0', Ptr);
			}
			RNode = Ptr.top();
			Ptr.pop();
			LNode = Ptr.top();
			Ptr.pop();
			p = Ptr.top();
			// 			if (LNode->m_data == '0')
			// 			{
			// 				p->lchild == NULL;
			// 				delete LNode;
			// 				LNode == NULL;
			// 			}
			// 			else
			// 			{
			// 				p->lchild = LNode;
			// 			}
			// 			if (RNode->m_data == '0')
			// 			{
			// 				p->rchild == NULL;
			// 				delete RNode;
			// 				RNode == NULL;
			// 			}
			// 			else
			// 			{
			// 				p->rchild = RNode;
			// 			}
			p->lchild = LNode->m_data == '0' ? NULL : LNode;
			p->rchild = RNode->m_data == '0' ? NULL : RNode;
			break;
		default:
			CrtNode(T, s[i], Ptr);
			if (i >= 1)
			{
				if (s[i - 1] == '('&& s[i + 1] == ')')
				{
					CrtNode(T, '0', Ptr);
				}
			}
			break;
		}
	}
	T = Ptr.top();
}
void DeleteNode(BiTree &tree,char ch)
{
	if (tree == NULL)
	{
		return;
	}
	if (tree->m_data == ch)
	{
		delete tree;
		tree = NULL;
		return;
	}
	DeleteNode(tree->lchild,ch);
	DeleteNode(tree->rchild,ch);
}
void PrintTree(BiTree &tree, string &s)
{
	if (tree == NULL)
	{
		return;
	}
	if (tree->lchild == NULL && tree->rchild == NULL)
	{
		s.push_back(tree->m_data);
	}
	else
	{
		s.push_back(tree->m_data);
		s += "(";
		PrintTree(tree->lchild, s);
		if (tree->rchild != NULL)
		{
			s += ",";
		}
		PrintTree(tree->rchild, s);
		s += ")";
	}
}