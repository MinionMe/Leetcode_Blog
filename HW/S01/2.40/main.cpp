#include <iostream>
#include <math.h>
using namespace std;

class PolyTerm
{
public:
	int coef;
	int exp;
};

struct SqPoly
{
	PolyTerm *data;
	SqPoly *next;
};
SqPoly* CreatList(int len);
SqPoly* MinusList(SqPoly *a, SqPoly *b,int &len);
void PrintList(SqPoly *a);
int main()
{
	int len_1,len_2,len_3 = 0;
	SqPoly *a,*b,*c;
	cin >> len_1;
	a = CreatList(len_1);
	cin >> len_2;
	b = CreatList(len_2);
	c = MinusList(a, b,len_3);
	cout << len_3 << endl;
	PrintList(c);
	return 0;
}
SqPoly* MinusList(SqPoly *a, SqPoly *b,int &len)
{
	SqPoly *p, *q;
	SqPoly *begin, *p0, *q0;
	p0 = new SqPoly;
	q0 = begin = p0;
	for (p = a, q = b; p != NULL && q != NULL;)
	{
		if (p->data->exp > q->data->exp)
		{
			p0 = new SqPoly;
			p0->data = new PolyTerm;
			p0->data->coef = -q->data->coef;
			p0->data->exp = q->data->exp;
			q0->next = p0;
			q0 = p0;
			q = q->next;
			len++;
		}
		else if (p->data->exp < q->data->exp)
		{
			p0 = new SqPoly;
			p0->data = new PolyTerm;
			p0->data->coef = p->data->coef;
			p0->data->exp = p->data->exp;
			q0->next = p0;
			q0 = p0;
			p = p->next;
			len++;
		}
		else
		{
			if (p->data->coef - q->data->coef != 0)
			{
				p0 = new SqPoly;
				p0->data = new PolyTerm;
				p0->data->coef = p->data->coef - q->data->coef;
				p0->data->exp = p->data->exp;
				q0->next = p0;
				q0 = p0;
				len++;
			}	
			p = p->next;
			q = q->next;
		}
	}
	if (p == NULL && q != NULL)
	{
		while (q != NULL)
		{
			p0 = new SqPoly;
			p0->data = new PolyTerm;
			p0->data->coef = -q->data->coef;
			p0->data->exp = q->data->exp;
			q0->next = p0;
			q0 = p0;
			q = q->next;
			len++;
		}
	}
	else if (p != NULL && q == NULL)
	{
		while (p != NULL)
		{
			p0 = new SqPoly;
			p0->data = new PolyTerm;
			p0->data->coef = p->data->coef;
			p0->data->exp = p->data->exp;
			q0->next = p0;
			q0 = p0;
			p = p->next;
			len++;
		}
	}
	p0->next = NULL;
	return begin->next;
}
void PrintList(SqPoly *l)
{
	if (l == NULL)
	{
		return;
	}
	while (l != NULL)
	{
		cout << l->data->coef << " " << l->data->exp << endl;
		l = l->next;
	}
}


SqPoly* CreatList(int len)
{
	if (len == 0)
	{
		return NULL;
	}
	SqPoly *begin, *p, *q;
	begin = q = p = NULL;
	p = new SqPoly;
	q = begin = p;
	p->data = new PolyTerm;
	cin >> p->data->coef;
	cin >> p->data->exp;
	for (int i = 0; i < len - 1; i++)
	{
		p = new SqPoly;
		p->data = new PolyTerm;
		cin >> p->data->coef;
		cin >> p->data->exp;
		q->next = p;
		q = p;
	}
	p->next = NULL;
	return begin;
}