#include <iostream>
using namespace std;

class LNode
{
public:
	int key;
	LNode *next;
	LNode *prior;
	LNode() :key(0), next(0), prior(0){};
};

class DuLinkTable
{
public:
	LNode* sp;
	DuLinkTable() :sp(NULL){};
};
void initTable(DuLinkTable &s, int n);
void search_node(DuLinkTable &s, int search_num);
int main()
{
	int node_num, search_num;
	cin >> node_num >> search_num;
	DuLinkTable s;
	initTable(s, node_num);
	search_node(s, search_num);
	return 0;
}
void initTable(DuLinkTable &s, int n)
{
	LNode *p,*q;
	if (n == 0)
	{
		return;
	}
	int val;
	cin >> val;
	p = new LNode;
	p->key = val;
	s.sp = q = p;
	p = p->next;
	for (int i = 0; i < n - 1;i++)
	{
		cin >> val;
		p = new LNode;
		p->key = val;
		q->next = p;
		p->prior = q;
		q = p;
		p = p->next;
	}
	q->next = s.sp;
	s.sp->prior = q;
} 
void search_node(DuLinkTable &s, int search_num)
{
	int *target = new int[search_num];
	for (int i = 0; i < search_num;i++)
	{
		cin >> target[i];
	}
	for (int i = 0; i < search_num;i++)
	{
		int Kval = target[i];
		int count = 0;
		if (s.sp == NULL)
		{
			cout << 0 << " " << count + 1 << endl;
			continue;
		}
		while (1)
		{
			count++;
			if (s.sp->key == Kval)
			{
				cout << 1 << " " << count << endl;
				break;
			}
			else if (s.sp->key < Kval)
			{
				if (s.sp->next == s.sp)
				{
					cout << 0 << " " << count << endl;
					break;
				}
				if (s.sp->next->key > Kval || s.sp->next->key < s.sp->key)
				{
					s.sp = s.sp->next;
					count++;
					cout << 0 << " " << count << endl;
					break;
				}
				s.sp = s.sp->next; 
			}
			else
			{
				if (s.sp->prior == s.sp || s.sp->prior->key > s.sp->key)
				{
					cout << 0 << " " << count << endl;
					break;
				}
				if (s.sp->prior->key < Kval)
				{
					s.sp = s.sp->prior;
					count++;
					cout << 0 << " " << count << endl;
					break;
				}
				s.sp = s.sp->prior;
			}
		}
	}
	
}