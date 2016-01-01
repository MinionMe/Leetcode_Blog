#include <iostream>
#include <stack>
#include <string>
#include <queue>
using namespace std;

typedef struct BiTNode{
	char m_data;
	struct BiTNode *lchild, *rchild;
	//lchild,rchild分别为节点的左孩子，右孩子指针
}BiTNode, *BiTree;
void CrtExpTree(BiTree &T, stack<BiTree> &Ptr);
void CrtNode(BiTree &T, char ch, stack<BiTree> &Ptr);
void PrintNode(BiTree &T, queue<BiTree> &Que);

int main()
{
	BiTree tree;
	stack<BiTree> Ptr;
	queue<BiTree> Que;
	CrtExpTree(tree, Ptr);
	PrintNode(tree, Que);
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
	getline(cin, s);
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
void PrintNode(BiTree &T, queue<BiTree> &Que)
{
	string s;
	BiTree p;
	if (T == NULL)
	{
		return;
	}
	Que.push(T);
	while (!Que.empty())
	{
		p = Que.front();
		Que.pop();
		s.push_back(p->m_data);
		if (p->lchild)
		{
			Que.push(p->lchild);
		}
		if (p->rchild)
		{
			Que.push(p->rchild);
		}
		if (!Que.empty())
		{
			s += " "; 
		}
	}
	cout << s << endl;
}