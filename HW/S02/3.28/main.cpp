#include <iostream>
#include <string>
using namespace std;

class LNode
{
public:
	int data;
	LNode *next;
};
typedef LNode* Linklist;
LNode* CreatList(int len);
void DealList(Linklist &a);
void PrintList(LNode *l);
int main()
{
	int len_1;
	LNode *a;
	cin >> len_1;
	a = CreatList(len_1);
	DealList(a);
	PrintList(a);
	return 0;
}
void DealList(Linklist &a)
{
	int num,integer;
	cin >> num;
	string str;
	Linklist p;
	for (int i = 0; i < num;i++)
	{
		cin >> str;
		if (str == "insert")
		{
			cin >> integer;
			p = new LNode;
			p->data = integer;
			p->next = a->next;
			a->next = p;
			a = a->next;
		}
		else
		{
			if (a->next == a)
			{
				delete a;
				a = NULL;
			}
			else
			{
				p = a->next;
				a->next = p->next;
				delete p;
			}
		}
	}
}
void PrintList(LNode *l)
{
	Linklist begin = l;
	if (l == NULL)
	{
		return;
	}
	l = l->next;
	cout << l->data;
	for (l = l->next; l != begin->next; l = l->next)
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
	return p;
}