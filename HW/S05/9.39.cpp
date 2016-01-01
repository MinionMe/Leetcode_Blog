#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>
using namespace std;

typedef struct BiTNode{
	int m_data;
	struct BiTNode *lchild, *rchild;
	//lchild,rchild分别为节点的左孩子，右孩子指针
}BiTNode, *BiTree;
void CrtExpTree(BiTree &T,stack<BiTree> &Ptr);
void CrtNode(BiTree &T, int integer, stack<BiTree> &Ptr);
void PrintTree(BiTree &tree,string &s);
void divideTree(BiTree &tree,int _val);
int main()
{
	int _val;
	BiTree tree;
	stack<BiTree> Ptr;
	CrtExpTree(tree,Ptr);
	cin >> _val;
	divideTree(tree, _val);
	return 0;
}
void divideTree(BiTree &tree,int _val)
{
	if (tree == NULL)
	{
		return;
	}
	string s1,s2;
	BiTree t1 = NULL,t2 = NULL,temp = NULL;
	stack<BiTree> stack_1, stack_2;
	BiTree p;
	p = tree;
	while (p != NULL)
	{
		if (p->m_data <= _val)
		{
			stack_1.push(p);
			if (p->rchild == NULL || p->rchild->m_data < _val)
			{
				if (!stack_2.empty())
				{
					t2 = stack_2.top();
					t2->lchild = NULL;
					while (stack_2.size() != 1)
					{
						stack_2.pop();
					}
					t2 = stack_2.top();
					stack_2.pop();
					break;
				}
			}
			p = p->rchild;
		}
		else
		{
			stack_2.push(p);
			if (p->lchild == NULL || p->lchild->m_data > _val)
			{
				if (!stack_1.empty())
				{
					t1 = stack_1.top();
					t1->rchild = NULL;
					while (stack_1.size() != 1)
					{
						stack_1.pop();
					}
					t1 = stack_1.top();
					stack_1.pop();
					break;
				}
			}		
			p = p->lchild;
		}
	}
	if (stack_1.empty())
	{
		while (!stack_2.empty())
		{
			if (stack_2.top()->lchild != NULL && stack_2.top()->lchild->m_data < _val)
			{
				stack_2.top()->lchild = t2;
			}
			
			t2 = stack_2.top();
			stack_2.pop();
		}
	}
	else if (stack_2.empty())
	{
		while (!stack_1.empty())
		{
			if (stack_1.top()->rchild != NULL && stack_1.top()->rchild->m_data > _val)
			{
				stack_1.top()->rchild = t1;
			}
			t1 = stack_1.top();
			stack_1.pop();
		}
	}
	if (t1 != NULL)
	{
		PrintTree(t1, s1);
		cout << s1 << endl;
	}
	else
	{
		cout << endl;
	}
	if (t2 != NULL)
	{
		PrintTree(t2,s2);
		cout << s2 << endl;
	}
	else
	{
		cout << endl;
	}
}
void CrtNode(BiTree &T, int integer, stack<BiTree> &Ptr)
{
	T = new BiTNode;
	T->m_data = integer;
	T->lchild = T->rchild = NULL;
	Ptr.push(T);
}
void CrtExpTree(BiTree &T, stack<BiTree> &Ptr)
{
	string s;
	BiTree LNode, RNode, p;
	int temp = 0;
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
				CrtNode(T, -1, Ptr);
			}
			break;
		case ',':
			if (s[i + 1] == ')')
			{
				CrtNode(T, -1, Ptr);
			}
			break;
		case '-':
			CrtNode(T, -1, Ptr);
			break;
		case ')':
			if (i == s.length() - 1 && Ptr.size() == 2)
			{
				CrtNode(T, -1, Ptr);
			}
			RNode = Ptr.top();
			Ptr.pop();
			LNode = Ptr.top();
			Ptr.pop();
			p = Ptr.top();
			p->lchild = LNode->m_data == -1 ? NULL : LNode;
			p->rchild = RNode->m_data == -1 ? NULL : RNode;
			break;
		default:
			temp = s[i] - '0';
			while (s[++i] >= '0' && s[i] <= '9')
			{
				temp = temp * 10 + s[i] - '0';
			}
			CrtNode(T, temp, Ptr);
			if (i >= 1)
			{
				if (s[i - 1] == '('&& s[i + 1] == ')')
				{
					CrtNode(T, -1, Ptr);
				}
			}
			i--;
			break;
		}
	}
	T = Ptr.top();
}
void PrintTree(BiTree &tree, string &s)
{
	char *ch = new char[5];
	if (tree == NULL)
	{
		s.push_back('-');
		return;
	}
	if (tree->lchild == NULL && tree->rchild == NULL)
	{
		_itoa(tree->m_data,ch,10);
		s += ch;
	}
	else
	{
		_itoa(tree->m_data, ch, 10);
		s += ch;
		s += "(";
		PrintTree(tree->lchild, s);
		s += ",";
		PrintTree(tree->rchild, s);
		s += ")";
	}
}