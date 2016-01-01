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
void HeapSort(SqList &sq);
void HeapAdjust (int R[], int s, int m);
int main()
{
	SqList sq;
	initArray(sq);
	HeapSort(sq);
	printArray(sq);
	return 0;
}
void HeapAdjust (int R[], int s, int m)
{   // 已知 R[s..m]中记录的关键字除 R[s] 之外均
    // 满足堆的特征，本函数自上而下调整 R[s] 的
    // 关键字，使 R[s..m] 也成为一个大顶堆。
	int rc = R[s];    // 暂存 R[s] 
	for (int j=2*s; j<=m; j*=2) 
	{ // j 初值指向左孩子
    	if ( j<m && R[j]<R[j+1])  ++j;     
             // 左/右“子树根”之间先进行相互比较
             // 令 j 指示关键字较大记录的位置
		if ( rc >= R[j] )  break; 
           // 再作“根”和“子树根”之间的比较，
           // 若“>=”成立，则说明已找到 rc 的插
           // 入位置 s ，不需要继续往下调整
		R[s] = R[j];   
		s = j;    
        // 否则记录上移，尚需继续往下调整
	}
	R[s] = rc;  // 将调整前的堆顶记录插入到 s 位置
} // HeapAdjust

void HeapSort (SqList &sq) 
{
  // 对顺序表 sq 进行堆排序。
	for (int i=sq.length/2; i>0;--i)
    	HeapAdjust (sq.key, i, sq.length);    // 建大顶堆
	for (int i = sq.length; i > 1; --i) 
	{
		int temp = sq.key[1];
		sq.key[1] = sq.key[i];
		sq.key[i] = temp;
		// 将堆顶记录和当前堆子序列
		//  H.r[1..i]中最后一个记录相互交换
		HeapAdjust(sq.key, 1, i - 1);  // 对 H.r[1] 进行筛选
	}
} // HeapSort

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