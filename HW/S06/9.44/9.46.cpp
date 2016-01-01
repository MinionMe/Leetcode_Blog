#include <iostream>
#include <string>
using namespace std;

typedef struct{
	int row;
	int col;
	int key;
}data;
//此为输入数据的结构。每一个数据由行号row、列号col和关键字key构成。此三个域均为非负整数。

typedef struct{
	int key[10000];
	int count;
}HashTable;
//其中count表示表中记录的个数
void InitHashTable(HashTable &ht);
void SearchTable(HashTable &ht);
int main()
{
	HashTable ht;
	InitHashTable(ht);
	SearchTable(ht);
	return 0;
}
void SearchTable(HashTable &ht)
{
	int search_num;
	cin >> search_num;
	data aim[100];
	for (int i = 0; i < search_num; i++)
	{
		cin >> aim[i].row >> aim[i].col;
	}
	for (int i = 0; i < search_num; i++)
	{
		cout << ht.key[aim[i].row/3+aim[i].col*7] << endl;
	}
}
void InitHashTable(HashTable &ht)
{
	int num;
	cin >> num;
	data temp;
	for (int i = 0; i < 10000; i++)
	{
		ht.key[i] = 0;
	}
	for (int i = 0; i < num; i++)
	{
		cin >> temp.row >> temp.col >> temp.key;
		ht.key[temp.row/3+temp.col*7]= temp.key;
	}
}