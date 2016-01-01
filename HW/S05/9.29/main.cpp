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
int Search_Bin(SSTable &s, int kval);
void Search(SSTable &s, int search_num);
int main()
{
	int num,search_num;
	SSTable s;
	cin >> num;
	s.elem = new ElemType[num + 1];
	initTable(num, s);
	cin >> search_num;
	Search(s, search_num);
}
void initTable(int num, SSTable &s)
{
	s.length = num;
	for (int i = 1; i < num + 1;i++)
	{
		cin >> s.elem[i].key;
	}
}
void Search(SSTable &s, int search_num)
{
	int *Kval = new int[search_num],*result = new int[search_num];
	for (int i = 0; i < search_num;i++)
	{
		cin >> Kval[i];
		result[i] = Search_Bin(s, Kval[i]);
	}
	for (int i = 0; i < search_num; i++)
	{
		cout << result[i] << endl;
	}
}
int Search_Bin(SSTable &s, int kval) 
{
	int low = 1,high = s.length;     // �������ֵ
	while (low <= high) 
	{
		int mid = (low + high) / 2;
		if (kval == s.elem[mid].key)
			return  mid;        // �ҵ�����Ԫ��
		else  if (kval < s.elem[mid].key)
			high = mid - 1;       // ������ǰ��������в���
		else  low = mid + 1; // �����ں��������в���
	}
	return 0;                 // ˳����в����ڴ���Ԫ��
} // Search_Bin
