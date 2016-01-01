#include "iostream"
#define MAXSIZE 200
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
void Msort(int SR[], int &length);
void MergePass(int SR[], int TR1[], int &len, int &CurrentSize);
void Merge(int SR[], int TR[], int l, int m, int n);
int main()
{
	SqList sq;
	initArray(sq); 
	Msort(sq.key,sq.length);  
	printArray(sq);
	return 0;
}
void Msort(int SR[],int &length) 
{
	int *temp = new int [length + 1] ; // 辅助表temp[]中。
  int len = 1;
  while (len < length) 
  {   //归并排序
    MergePass (SR, temp, len,length); //第一趟将原始表归并，结果放在辅助表中
 		len *= 2;	              //一趟两路归并排序后归并项长度加倍
	  MergePass (temp, SR, len,length); //第二趟将辅助表归并，//结果放在原始表中
    len *= 2;                  
  }
  delete [ ] temp;
} // Msort
void MergePass (int SR[], int TR1[], int &len,int &CurrentSize) 
{
// 一趟归并排序，将表SR[ ]中两个长度为len的有序子表进行归并，
// 结果放在TR1[ ]的相同位置。
    int i = 1;
    while (i+2*len <= CurrentSize) 
    {
      Merge(SR, TR1, i, i+len-1, i + 2 * len - 1);
      i += 2 * len;      //循环对长度为len的子表两两归并，//直到剩余元素个数不足2×len。
    }
    if (i+len <= CurrentSize)
      Merge(SR, TR1, i, i+len-1, CurrentSize);
                   //一个子表长度为len，另一个子表长度不足len，                      
                   //再做一次归并，
    else 
      for (int j = i; j <= CurrentSize; j++)
        TR1[j] = SR[j];   //只有一个长度不足len的子表，复制
} 

void Merge (int SR[], int TR[], int l, int m, int n) 
{  // 将有序的记录序列 SR[l..m] 和 SR[m+1..n]
   // 归并为有序的记录序列 TR[i..n]
	int i,j,k;
	for (k=l, i=l, j=m+1;  i<=m && j<=n;  ++k)   
	{// 将SR中记录由小到大地并入TR
    	if (SR[i]<=SR[j])  
    		TR[k] = SR[i++];
    	else 
    		TR[k] = SR[j++];
  }
	if (i<=m) 
		for (; i <=m ; ++i,++k)
			TR[k] = SR[i];
	else if (j<=n) 
		for (; j <=n ; ++j,++k)
			TR[k] = SR[j];
} // Merge


void initArray(SqList &sq)
{
	cin >> sq.length;
	for (int i = 1; i <= sq.length; i++)
		cin >> sq.key[i];
}
void printArray(SqList &sq)
{
	int i;
	for (i = 1;i <= sq.length; i++)
		cout << sq.key[i] << " ";
}