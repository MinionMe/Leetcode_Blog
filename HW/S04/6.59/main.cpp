#include <iostream>
#include <queue>
using namespace std;

class Lnode
{
public:
	int m_data;
	int m_first_child;
	int m_second_child;
	int m_parent;
	Lnode() :m_data(0), m_first_child(0), m_second_child(0), m_parent(0){};
};
typedef Lnode* Ltree;
void InitTree(int n,Ltree &node);
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
	queue<Lnode> que;
	Lnode temp;
	que.push(node[1]);
	while (!que.empty())
	{
		temp = que.front();
		if (temp.m_first_child != 0)
		{
			cout << temp.m_data << " " << temp.m_first_child << endl;
			que.push(node[temp.m_first_child]);
		}
		if (temp.m_second_child != 0)
		{
			cout << temp.m_data << " " << temp.m_second_child << endl;
			que.push(node[temp.m_second_child]);
		}
		que.pop();
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
	for (int i = 1; i < n + 1;i++)
	{
		node[i].m_data = i;
		cin >> temp;
		node[i].m_first_child = temp;
		node[temp].m_parent = i;
		cin >> temp;
		node[node[i].m_parent].m_second_child = temp;
	}
}