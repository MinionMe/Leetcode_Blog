#include <iostream>
using namespace std;

class LNode
{
public:
	char data;
	LNode *next;
};
LNode* CreatList(int len);
LNode* ReverseList(LNode *l);
void PrintList(LNode *l);
int main()
{
	int len;
	LNode *l;
	cin >> len;
	l = CreatList(len);
	l = ReverseList(l);
	PrintList(l);
	return 0;
}
LNode* ReverseList(LNode *l)
{
	LNode *p, *q, *m;
	m = p = q = l;
	if (l == NULL)
	{
		return NULL;
	}
	if (l->next == NULL)
	{
		return l;
	}
	else
	{
		p = p->next;
		if (p->next == NULL)
		{
			p->next = q;
			q->next = NULL;
			l = p;
			return l;
		}
		while (p->next != NULL)
		{
			q = p;
			p = p->next;
			q->next = m;
			m = q;
		}
		p->next = m;
		l->next = NULL;
		l = p;
		return l;
	}
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