#include "iostream"
#define MAXSIZE 200
using namespace std;

class SqList
{
public:
	int key[MAXSIZE + 1]; //r[0]���û��������ڱ���Ԫ
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
	int *temp = new int [length + 1] ; // ������temp[]�С�
  int len = 1;
  while (len < length) 
  {   //�鲢����
    MergePass (SR, temp, len,length); //��һ�˽�ԭʼ��鲢��������ڸ�������
 		len *= 2;	              //һ����·�鲢�����鲢��ȼӱ�
	  MergePass (temp, SR, len,length); //�ڶ��˽�������鲢��//�������ԭʼ����
    len *= 2;                  
  }
  delete [ ] temp;
} // Msort
void MergePass (int SR[], int TR1[], int &len,int &CurrentSize) 
{
// һ�˹鲢���򣬽���SR[ ]����������Ϊlen�������ӱ���й鲢��
// �������TR1[ ]����ͬλ�á�
    int i = 1;
    while (i+2*len <= CurrentSize) 
    {
      Merge(SR, TR1, i, i+len-1, i + 2 * len - 1);
      i += 2 * len;      //ѭ���Գ���Ϊlen���ӱ������鲢��//ֱ��ʣ��Ԫ�ظ�������2��len��
    }
    if (i+len <= CurrentSize)
      Merge(SR, TR1, i, i+len-1, CurrentSize);
                   //һ���ӱ���Ϊlen����һ���ӱ��Ȳ���len��                      
                   //����һ�ι鲢��
    else 
      for (int j = i; j <= CurrentSize; j++)
        TR1[j] = SR[j];   //ֻ��һ�����Ȳ���len���ӱ�����
} 

void Merge (int SR[], int TR[], int l, int m, int n) 
{  // ������ļ�¼���� SR[l..m] �� SR[m+1..n]
   // �鲢Ϊ����ļ�¼���� TR[i..n]
	int i,j,k;
	for (k=l, i=l, j=m+1;  i<=m && j<=n;  ++k)   
	{// ��SR�м�¼��С����ز���TR
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