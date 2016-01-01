#include <iostream>
using namespace std;

void find_tree(int u, int v, int *l, int *r,int &flag);

int main()
{
	int length, u, v, *left,*right,flag = 0;
	cin >> length;
	left = new int[length + 1];
	right = new int[length + 1];
	for (int i = 0; i <= length;i++)
	{
		cin >> left[i];
	}
	for (int i = 0; i <= length; i++)
	{
		cin >> right[i];
	}
	cin >> u >> v;
	find_tree(u, v, left, right,flag);
	if (flag == 0)
	{
		cout << "false" << endl;
	}
	return 0;
}

void find_tree(int u, int v, int *l, int *r,int &flag)
{
	if (v == 0)
	{
		return;
	}
	if (u == v)
	{
		cout << "true" << endl;
		flag++;
		return;
	}
	find_tree(u, l[v], l, r,flag);
	find_tree(u, r[v], l, r,flag);
}