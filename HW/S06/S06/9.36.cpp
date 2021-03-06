#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>
using namespace std;

class BiTNode{
public:
	int m_data;
	BiTNode *lchild, *rchild;
	//lchild,rchild分别为节点的左孩子，右孩子指针
	BiTNode() :m_data(0), lchild(0), rchild(0){};
};
typedef BiTNode* BiTree;
void CrtExpTree(BiTree &T, stack<BiTree> &Ptr);
void CrtNode(BiTree &T, int integer, stack<BiTree> &Ptr);
void PrintTree(BiTree &tree, string &s);
void insertNode(BiTree &tree, int _val);
int main()
{
	int _val;
	string s;
	BiTree tree;
	stack<BiTree> Ptr;
	CrtExpTree(tree, Ptr);
	cin >> _val;
	insertNode(tree, _val);
	if (tree != NULL)
	{
		PrintTree(tree, s);
		cout << s << endl;
	}
	return 0;
}
void insertNode(BiTree &tree, int _val)
{
	BiTree p = tree, temp;
	if (tree == NULL)
	{
		temp = new BiTNode;
		temp->m_data = _val;
		tree = temp;
		return;
	}
	while (p)
	{
		if (p->m_data < _val)
		{
			if (p->rchild == NULL)
			{
				temp = new BiTNode;
				temp->m_data = _val;
				p->rchild = temp;
				break;
			}
			p = p->rchild;
		}
		else
		{
			if (p->lchild == NULL)
			{
				temp = new BiTNode;
				temp->m_data = _val;
				p->lchild = temp;
				break;
			}
			p = p->lchild;
		}
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
		_itoa(tree->m_data, ch, 10);
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