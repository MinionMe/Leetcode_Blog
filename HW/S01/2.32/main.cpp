#include <iostream>
using namespace std;

class LNode
{
public:
	int data;
	LNode *next;
	LNode *prior;
};
typedef LNode* Linklist;
LNode* CreatList(int len);
void DoList(Linklist &a);
void PrintList(LNode *l,int &n);
int main()
{
	int len_1,n;
	LNode *a;
	cin >> len_1;
	a = CreatList(len_1);
	cin >> n;
	DoList(a);
	PrintList(a, n);
	return 0;
}
void PrintList(LNode *l,int &n)
{
	Linklist begin, p;
	begin = p = l;
	if (l == NULL)
	{
		return;
	}
	if (l != NULL)
	{
		for (p = l; p->next != l;p = p->next)
		{
			if (p->data == n)
			{
				begin = p;
				break;
			}
		}
		if (p->next == l)
		{
			begin = p;
		}
	}
	cout << begin->data;
	for (p = p->prior;p != begin; p = p->prior)
	{
		cout << " " << p->data;
	}
	cout << endl;
}
void DoList(Linklist &a)
{
	Linklist begin,p,q;
	begin = p = a;
	if (p == NULL)
	{
		return;
	}
	if (p->next == NULL)
	{
		p->next = p;
		p->prior = p;
		return;
	}
	q = p->next;
	for (; q->next != NULL;p = p->next,q = q->next)
	{
		q->prior = p;
	}
	q->prior = p;
	begin->prior = q;
	q->next = begin;
}
LNode* CreatList(int len)
{
	if (len == 0)
	{
		return NULL;
	}
	LNode *begin, *p, *q;
	begin = q = p = NULL;
	p = new LNode;
	q = begin = p;
	cin >> p->data;
	for (int i = 0; i < len - 1; i++)
	{
		p = new LNode;
		cin >> p->data;
		q->next = p;
		q = p;
	}
	p->next = NULL;
	return begin;
}