#include <iostream>
using namespace std;

typedef struct{
	int key;
}ElemType;

class SSTable
{
public:
	ElemType *elem;
	int length;
	SSTable() :elem(NULL), length(0){};
};
void initTable(int num, SSTable &s);
void Search_Bin(SSTable &s);
 
int main()
{
	int num;
	SSTable s;
	cin >> num;
	s.elem = new ElemType[num + 1];
	initTable(num, s);
	Search_Bin(s);
	return 0;
}
void initTable(int num, SSTable &s)
{
	s.length = num;
	for (int i = 1; i < num + 1; i++)
	{
		cin >> s.elem[i].key;
	}
}

void Search_Bin(SSTable &s)
{
	int kval;
	int low = 1, high = s.length;     // 置区间初值
	cin >> kval;
	if (s.elem[low].key > kval)
	{
		cout << 0 << endl;
		return;
	}
	else if (s.elem[high].key <= kval)
	{
		cout << high << endl;
		return;
	}
	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (kval == s.elem[mid].key)
		{
			cout << mid << endl;       // 找到待查元素
			return;
		}
		else if (s.elem[mid].key > kval )
		{
			if (s.elem[mid - 1].key < kval)
			{
				cout << mid - 1 << endl;
				return;
			}
			else
			{
				high = mid - 1;
			}
			
		}
		else
		{
			if (s.elem[mid + 1].key > kval)
			{
				cout << mid << endl;
				return;
			}
			else
			{
				low = mid + 1;
			}
		}

	}
} // Search_Bin
