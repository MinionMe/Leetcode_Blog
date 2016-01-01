#include <iostream>
using namespace std;

void qSort (int* a, int s, int t) 
{
	int l, r, value;
	if (s >= t)
		return;
	l = s; r = t;
	value = a[l];
	do
	{
		while ((l < r) && (a[r] >= value)) r--;
		if (l < r){ a[l] = a[r]; l++; }
		while ((l < r) && a[l] <= value) l++;
		if (l < r) { a[r] = a[l]; r--; }
	} while (l != r);
	a[l] = value;
	qSort(a, s, l - 1);
	qSort(a, r + 1, t);
} // QSort

int main()
{
	int integer,n[30],num;
	integer = -1;
	num = 0;
	while (integer != 0)
	{
		cin >> integer;
		n[num] = integer;
		num++;
	}
	num -= 1;
	qSort(n,0,num - 1);
	for (int i = 0; i < num-1 ; ++i)
	{
		cout << n[i] << " ";
	}
	cout << n[num-1] << endl;
	return 0;
}








   
