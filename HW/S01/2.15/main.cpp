#include <iostream>
using namespace std;

class LNode
{
public:
	char data;
	LNode* next;
};
LNode* CreatList(int len);
LNode* ConnectList(LNode *l, LNode *m);
void PrintList(LNode *l);
LNode* l;
LNode* m;
int main()
{
	int len_1,len_2;
	cin >> len_1;
	l = CreatList(len_1);
	cin >> len_2;
	m = CreatList(len_2);
	l = ConnectList(l, m);
	cout << len_1 + len_2 << endl;
	PrintList(l);
	return 0;
}

LNode* CreatList(int len)
{
	if (len == 0)
	{
		return NULL;
	}
	LNode *begin,*p,*q;
	begin = q = p = NULL;
	p = new LNode;
	q = begin = p;
	cin >> p->data;
	for (int i = 0; i < len - 1;i++)
	{
		p = new LNode;
		cin >> p->data;
		q->next = p;
		q = p;
	}
	p->next = NULL;
	return begin;
}
LNode* ConnectList(LNode* l, LNode* m)
{
	LNode *p;
	if (l == NULL)  
	{
		return m;
	}
	p = l;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = m;
	return l;
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