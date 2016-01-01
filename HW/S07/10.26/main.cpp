#include <iostream>
using namespace std;

void initArray(int *a, int num);
void sort_array(int *a, int num);
void printArray(int *a, int num, int _count);
int main()
{
	int num;
	cin >> num;
	int *a = new int[num + 2];
	initArray(a, num);
	sort_array(a, num);
	return 0;
}
void initArray(int *a, int num)
{
	for (int i = 1; i <= num; i++)
	{
		cin >> a[i];
	}
}
void sort_array(int *a, int num)
{
	int temp,flag;
	int _count = 0;
	for (int j = num; j > 1;)          // 冒泡排序，外层循环
	{
		for (int i = 1; i < j; i++)    // 内层循环
		{
			if (a[i] > a[i + 1])                 // 把大的数往上冒
			{
				temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;
				flag = i;
			}
			_count++;
		}
		j = flag;
		flag = 0;
	}
	printArray(a, num, _count);
}
void printArray(int *a, int num, int _count)
{
	int i;
	for (i = 1; i <= num; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	cout << _count << endl;
}