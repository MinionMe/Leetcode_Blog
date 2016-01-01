#include <iostream>
#include <stack>
#define MAXSIZE 200 //最大长度
using namespace std;

class SqList
{
public:
	int key[MAXSIZE + 1]; //r[0]闲置或者用作哨兵单元
	int length;
	SqList() :length(0){};
};
void initArray(SqList &sq);
void printArray(SqList &sq);
void qSort(SqList &sq);
void _sort(SqList &sq,int l,int r);
int partition(SqList &sq, int left, int right);
void judgeIfqsort(SqList &sq,int left, int right,int p,stack<int> &t);
int main()
{
	SqList sq;
	initArray(sq);
	qSort(sq);
	printArray(sq);
	return 0;
}
void qSort(SqList &sq)
{
	stack<int> t;
	if (sq.length <= 3)
	{
		_sort(sq, 1, sq.length);
		return;
	}
	else
	{
		int p = partition(sq, 1, sq.length);
		judgeIfqsort(sq, 1, sq.length, p, t);
		while (!t.empty())
		{
			int r = t.top();
			t.pop();
			int l = t.top();
			t.pop();
			p = partition(sq, l, r);
			judgeIfqsort(sq, l, r, p, t);
		}
	}
}
void judgeIfqsort(SqList &sq,int l, int r, int p, stack<int> &t)
{
	if (p - l <= 3)
	{
		_sort(sq, l, p - 1);
		if (r - p <= 3)
		{
			_sort(sq, p + 1, r);
		}
		else
		{
			t.push(p + 1);
			t.push(r);
		}
		return;
	}
	else if (r - p <= 3)
	{
		_sort(sq, p + 1, r);
		t.push(l);
		t.push(p - 1);
		return;
	}
	else
	{
		if (r - p > p - l)
		{
			t.push(p + 1);
			t.push(r);
			t.push(l);
			t.push(p - 1);
		}
		else
		{
			t.push(l);
			t.push(p - 1);
			t.push(p + 1);
			t.push(r);
		}
	}
}
void initArray(SqList &sq)
{
	cin >> sq.length;
	for (int i = 1; i <= sq.length; i++)
	{
		cin >> sq.key[i];
	}
}
void printArray(SqList &sq)
{
	int i;
	for (i = 1; i <= sq.length; i++)
	{
		cout << sq.key[i] << " ";
	}
}
int partition(SqList &sq, int left, int right)
{
	sq.key[0] = sq.key[left];
	while (left < right)
	{
		while (left < right && sq.key[right] >= sq.key[0])
			right--;
		sq.key[left] = sq.key[right];
		while (left < right && sq.key[left] <= sq.key[0])
			left++;
		sq.key[right] = sq.key[left];
	}
	sq.key[left] = sq.key[0];
	return left;
}
void _sort(SqList &sq,int l,int r)
{
	int temp, flag;
	for (int j = 1; j < r - l + 1;j++)          // 冒泡排序，外层循环
	{
		for (int i = l; i <= r - j; i++)    // 内层循环
		{
			if (sq.key[i] > sq.key[i + 1])                 // 把大的数往上冒
			{
				temp = sq.key[i];
				sq.key[i] = sq.key[i + 1];
				sq.key[i + 1] = temp;
			}
		}
	}
}