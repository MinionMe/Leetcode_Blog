#include <iostream>
#include <deque>
using namespace std;

struct CyclicQueue // 循环队列
{
	int *elem;
	int rear;// (rear-1+k)%k 指向队尾元素
public:
	CyclicQueue()
	{
		int length,i;
		cin >> length;
		elem = new int [length];
		for (i = 0; i < length - 1;i++)
		{
			elem[i] = 0;
		}
		elem[i] = 1;
		rear = length - 1;
	}
	void Pop_front()
	{
		int i;
		for (i = 0; i <= rear;i++)
		{
			elem[i] = elem[(i + 1) % (rear + 1)];
		}
	}
	void Push_back(int num)
	{
		elem[rear] = num;
	}
	void CalculatingSum()
	{
		int  max_num, i, tempnum = 0;
		cin >> max_num;
		while (elem[rear] <= max_num)
		{
			for (i = 0; i <= rear; i++)
			{
				tempnum += elem[i];
			}
			if (tempnum > max_num)
			{
				break;
			}
			else
			{
				Pop_front();
				Push_back(tempnum);
			}
			tempnum = 0;
		}
		cout << elem[0];
		for (i = 1; i <= rear; i++)
		{
			cout << " " << elem[i];
		}
		cout << endl;
	}
};

int main()
{
	CyclicQueue que;
	que.CalculatingSum();
	return 0;
}