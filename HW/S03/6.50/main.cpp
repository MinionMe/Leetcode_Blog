#include <iostream>
#include <string>
#include <queue>
using namespace std;

typedef struct BiTNode{
	char m_data;
	struct BiTNode *lchild, *rchild;      //lchild,rchild分别为节点的左孩子，右孩子指针
}BiTNode, *BiTree;
void CrtExpTree(BiTree &T, queue<BiTree> &Ptr);
void CrtNode(BiTree &T, char ch, queue<BiTree> &Ptr);
void PrintTree(BiTree &tree, string &s);

int main()
{
	BiTree tree;
	queue<BiTree> Ptr;
	string s;
	CrtExpTree(tree, Ptr);
	PrintTree(tree, s);
	cout << s << endl;
	return 0;
}

void CrtNode(BiTree &T, char ch,queue<BiTree> &Ptr)
{
	T = new BiTNode;
	T->m_data = ch;
	T->lchild = T->rchild = NULL;
	Ptr.push(T);
}
void CrtExpTree(BiTree &T, queue<BiTree> &Ptr)
{
	string s, tempstr;
	BiTree p,temp;
	getline(cin, s);
	if (s.empty())
	{
		T = NULL;
		return;
	}
	while (!(s[0] == '^' && s[1] == '^'))
	{
		if (s[0] == '^')
		{
			CrtNode(T, s[1], Ptr);
		}
		else
		{
			while (!Ptr.empty())
			{
				p = Ptr.front();
				if (p->m_data == s[0])
				{
					CrtNode(temp, s[1], Ptr);
					switch (s[2])
					{
					case 'L':
						p->lchild = temp;
						break;
					case 'R':
						p->rchild = temp;
						break;
					default:
						break;
					}
					break;
				}
				Ptr.pop();
				Ptr.push(p);
			}
		}
		getline(cin, s);
	}
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