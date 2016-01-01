#include <iostream>
#include <string>
#include <queue>
#define MAX_TREE_SIZE 100
using namespace std;

typedef struct BiTNode{
	char m_data;
	struct BiTNode *lchild, *rchild;      //lchild,rchild分别为节点的左孩子，右孩子指针
}BiTNode, *BiTree;
class SqBiTree
{
public:
	int size;
	char elem[MAX_TREE_SIZE + 1];         // elem[0]不用
	SqBiTree() :size(0){};
};

void CrtExpTree(BiTree &T, queue<BiTree> &Ptr,SqBiTree sqBitree);
void CrtNode(BiTree &T, char ch, queue<BiTree> &Ptr);
void PrintTree(BiTree &tree, string &s);

int main()
{
	BiTree tree;
	queue<BiTree> Ptr;
	SqBiTree sqBitree;
	string s;
	CrtExpTree(tree, Ptr,sqBitree);
	PrintTree(tree, s);
	cout << s << endl;
	return 0;
}

void CrtNode(BiTree &T, char ch, queue<BiTree> &Ptr)
{
	T = new BiTNode;
	T->m_data = ch;
	T->lchild = T->rchild = NULL;
	Ptr.push(T);
}
void CrtExpTree(BiTree &T, queue<BiTree> &Ptr, SqBiTree sqBitree)
{
	string s;
	BiTree p, temp;
	getline(cin, s);
	if (s.empty())
	{
		T = NULL;
		return;
	}
	for (int i = 0,j = 0; i < s.length();i++)
	{
		switch (s[i])
		{
		case ' ':
			break;
		default:
			sqBitree.elem[j++] = s[i];
			sqBitree.size++;
			break;
		}
	}
	if (sqBitree.size == 1)
	{
		T = NULL;
		return;
	}
	for (int i = 0; i < sqBitree.size - 1;i++)
	{
		if (Ptr.empty())
		{
			CrtNode(T, sqBitree.elem[i], Ptr);
		}
		else
		{
			p = Ptr.front();
			CrtNode(temp, sqBitree.elem[i], Ptr);
			if (p->lchild == NULL)
			{
				p->lchild = temp;
			}
			else
			{
				p->rchild = temp;
				Ptr.pop();
			}
		}
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