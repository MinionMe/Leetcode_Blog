#include <iostream>
using namespace std;

class LNode
{
public:
	int data;
	LNode *next;
};
LNode* CreatList(int len);
LNode* intersectionList(LNode *a, LNode *b,int &len);
void PrintList(LNode *l);
int main()
{
	int len_1, len_2,len_3;
	len_3 = 0;
	LNode *a, *b, *c;
	cin >> len_1;
	a = CreatList(len_1);
	cin >> len_2;
	b = CreatList(len_2);
	c = intersectionList(a, b,len_3);
	cout << len_3 << endl;
	PrintList(c);
	return 0;
}
LNode* intersectionList(LNode *a, LNode *b,int &len)
{
	LNode *p, *q,*temp,*c,*begin;
	c = new LNode;
	begin = c;
	if (a == NULL || b == NULL)
	{
		return NULL;
	}
	p = a;
	q = b;
	while (p != NULL && q != NULL)
	{
		if (p->data == q->data)
		{
			len++;
			temp = new LNode;
			temp->data = p->data;
			c->next = temp;
			c = c->next;
			p = p->next;
			q = q->next;
		}
		else if (p->data < q->data)
		{
			p = p->next;
		}
		else
		{
			q = q->next;
		}
	}
	c->next = NULL;
	return begin->next;
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