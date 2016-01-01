#include <iostream>
#include <queue>
using namespace std;

class Lnode
{
public:
	int m_data;
	int m_firstchild;
	int m_sibling;
	int m_lastchild;
	int m_parent;
	Lnode() :m_data(0), m_firstchild(0), m_sibling(0), m_parent(0), m_lastchild(0){};
};
typedef Lnode* Ltree;
void InitTree(int n, Ltree &node);
void PrintTree(int n, Ltree &node);
int main()
{
	int num;
	Ltree node;
	cin >> num;
	InitTree(num, node);
	PrintTree(num, node);
	return 0;
}
void PrintTree(int n, Ltree &node)
{
	if (node == NULL)
	{
		return;
	}
	for (int i = 1; i < n + 1;i++)
	{
		cout << node[i].m_firstchild << " " << node[i].m_sibling << endl;
	}
}
void InitTree(int n, Ltree &node)
{
	if (n == 0)
	{
		node = NULL;
		return;
	}
	int temp;
	node = new Lnode[n + 1];
	for (int i = 1; i < n + 1; i++)
	{
		node[i].m_data = i;
		cin >> temp;
		node[i].m_parent = temp;
		if (temp == 0)
		{
			continue;
		}
		if (node[temp].m_firstchild == 0)
		{
			node[temp].m_firstchild = i;
			node[temp].m_lastchild = i;
		}
		else
		{
			node[node[temp].m_lastchild].m_sibling = i;
			node[temp].m_lastchild = i;
		}
	}
}