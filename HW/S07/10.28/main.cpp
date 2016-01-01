#include <iostream>
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
void two_sideSort(SqList &sq);

int main()
{
	SqList sq;
	initArray(sq);
	two_sideSort(sq);
	printArray(sq);
	return 0;
}
void two_sideSort(SqList &sq)
{
	int d = 1,temp;
	int pos[3];
	pos[0] = 1;
	pos[2] = sq.length;
	int i = 1, flag = 1;
	while (flag)
	{
		flag = 0;
		while (i != pos[d+1])
		{
			if ((sq.key[i]-sq.key[i + d])*d>0)
			{
				temp = sq.key[i];
				sq.key[i] = sq.key[i + d];
				sq.key[i + d] = temp;
				flag = 1;
			}
			i += d;
		}
		pos[d + 1] -= d;
		i = pos[d + 1];
		d = -d;
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
	cout << endl;
}