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
int Caculatelist(int n,int len, SqPoly* a);
int main()
{
	int len,n,result;
	cin >> len;
	SqPoly *a;
	a = CreatList(len);
	cin >> n;
	result = Caculatelist(n, len, a);
	cout << result << endl;
	return 0;
}
int Caculatelist(int n, int len, SqPoly* a)
{
	SqPoly *p;
	int result = 0,i;
	for (p = a,i = 0; i < len;i++,p = p->next)
	{
		result += p->data->coef * pow(n, p->data->exp);
	}
	return result;
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