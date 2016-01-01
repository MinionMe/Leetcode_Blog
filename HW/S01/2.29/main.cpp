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
void DealList(Linklist &a, Linklist &b, Linklist &c,int &n);
void PrintList(LNode *l);
int main()
{
	int len_1, len_2, len_3;
	LNode *a, *b, *c;
	cin >> len_1;
	a = CreatList(len_1);
	cin >> len_2;
	b = CreatList(len_2);
	cin >> len_3;
	c = CreatList(len_3);
	DealList(a, b, c,len_1);
	cout << len_1 << endl;
	PrintList(a);
	return 0;
}
void DealList(Linklist &a, Linklist &b, Linklist &c,int &n)
{
	Linklist p, q, r,temp;
	Linklist begin  = new LNode;
	begin->next = a;
	int num;
	p = a;
	q = b;
	r = c;
	temp = begin;
	while (p != NULL && q != NULL && r != NULL)
	{
		num = p->data;
		if (num > q->data)
		{
			q = q->next;
		}
		else if (num < q->data)
		{
			p = p->next;
			temp = temp->next;
		}
		else if (num == q->data)
		{
			if (num > r->data)
			{
				r = r->next;
			}
			else if (num < r->data)
			{
				p = p->next;
				temp = temp->next;
			}
			else if (num == r->data)
			{
				n--;
				temp->next = p->next;
				p->next = NULL;
				delete p;
				p = temp->next;
			}
		}
	}
	a = begin->next;
}
void PrintList(LNode *l)
{
	if (l == NULL)
	{
		return;
	}
	cout << l->data;
	l = l->next;
	while (l != NULL)
	{
		cout << " " << l->data;
		l = l->next;
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
	p->next = NULL;
	return begin;
}