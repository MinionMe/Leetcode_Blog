#include <iostream>
#include <string>
using namespace std;

class LNode
{
public:
	string data;
	LNode *next;
};
typedef LNode* Linklist;
LNode* CreatList(int len);
void DealList(Linklist &a, Linklist &b, Linklist &c,Linklist &d,int len);
void PrintList(LNode *l);
int main()
{
	int len_1;
	LNode *a, *b, *c, *d;
	cin >> len_1;
	a = CreatList(len_1);
	DealList(a, b, c, d,len_1);
	PrintList(b);
	PrintList(c);
	PrintList(d);
	return 0;
}
void DealList(Linklist &a, Linklist &b, Linklist &c, Linklist &d,int len)
{
	Linklist p, b0, c0, d0, bq, cq, dq;
	int i;
	b = b0 = bq = new LNode;
	c = c0 = cq = new LNode;
	d = d0 = dq = new LNode;
	for (i = 0,p = a; i < len; i++)
	{
			b0 = new LNode;
			b0->data = p->data;
			bq->next = b0;
			bq = b0;
			p = p->next;
			c0 = new LNode;
			c0->data = p->data;
			cq->next = c0;
			cq = c0;
			p = p->next;
			d0 = new LNode;
			d0->data = p->data;
			dq->next = d0;
			dq = d0;
			p = p->next;
	}
	b = b->next;
	b0->next = b;
	c = c->next;
	c0->next = c;
	d = d->next;
	d0->next = d;
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
	for (int i = 0; i < 3 * len - 1; i++)
	{
		p = new LNode;
		cin >> p->data;
		q->next = p;
		q = p;
	}
	p->next = NULL;
	return begin;
}