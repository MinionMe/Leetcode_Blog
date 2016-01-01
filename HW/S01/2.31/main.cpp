#include <iostream>
using namespace std;

class LNode
{
public:
	int data;
	LNode *next;
};
typedef LNode* Linklist;
LNode* CreatList(int len);
void DealList(Linklist &a, int &n);
void PrintList(LNode *l);
int main()
{
	int len_1, n;
	LNode *a;
	cin >> len_1;
	a = CreatList(len_1);
	cin >> n;
	DealList(a, n);
	PrintList(a);
	return 0;
}
void DealList(Linklist &a, int &n)
{
	Linklist p, q, r;
	Linklist begin = new LNode;
	begin->next = a;
	if (a->next == a)
	{
		a = NULL;
		return;
	}
	for (q = a, p = a->next, r = begin;; p = p->next, q = q->next, r = r->next)
	{
		if (p->data == n)
		{
			break;
		}
	}
	if (r == begin)
	{
		a = p;
		q->next = NULL;
		p->next = p;
		delete q;
	}
	else
	{
		r->next = q->next;
		q->next = NULL;
		delete q;
	}


}
void PrintList(LNode *l)
{
	Linklist begin = l;
	if (l == NULL)
	{
		return;
	}
	cout << l->data;
	for (l = l->next; l != begin; l = l->next)
	{
		cout << " " << l->data;
	}
	cout << endl;
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
	p->next = begin;
	return begin;
}