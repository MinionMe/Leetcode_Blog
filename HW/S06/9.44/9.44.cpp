#include <iostream>
#include <string>
using namespace std;

typedef struct
{
	string key;
	int count;
}HashTable;
//其中count表示表中记录的个数
void InitHashTable(HashTable *ht);
void PrintHashTable(HashTable *ht);
int main()
{
	HashTable ht[100];
	InitHashTable(ht);
	PrintHashTable(ht);
	return 0;
}
void PrintHashTable(HashTable *ht)
{
	for (int d = 0; d <= 25; d++)
	{
		for (int k = 0; k < 100; k++)
		{
			if (ht[k].key[0] == 'A' + d)
			{
				cout << ht[k].key << endl;
				for (int n = k + 1; n < 100; n++)
				{
					if (ht[n].key[0] == ht[k].key[0])
					{
						cout << ht[n].key << endl;
					}
				}
				break;
			}
		}
	}
}
void InitHashTable(HashTable *ht)
{
	int num;
	cin >> num;
	string tempstr;
	int i = 0, temp = 0;
	while (i < num)
	{
		cin >> tempstr;
		temp = tempstr[0];
		for (int j = 0; j < i + 1; j++)
		{
			if (ht[(temp + 36) % 100].key == "")
			{
				ht[(temp + 36) % 100].key = tempstr;
				break;
			}
			else
			{
				temp++;
			}		
		}
		i++;
	}
}