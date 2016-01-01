#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

char num[200];
int N,K;
int get_arr_val(int start, int end);
int get_min_val(int start, int k);
int main()
{
	scanf("%s", num);
	scanf("%d", &K);
	N = strlen(num);
	printf("%d\n", get_min_val(0, K));
	return 0;
}
int get_arr_val(int start, int end)
{
	int res = 0, i;
	for (i = start; i <= end; i++)
		res = res * 10 + num[i] - '0';
	return res;
}
int get_min_val(int start, int k)
{
	int sum, i, Minsum = 999999;
	if (k == 0)
		return get_arr_val(start, N - 1);
	for (i = 0; i <= N - start - k; i++)
	{
		sum = get_arr_val(start, start + i);
		sum += get_min_val(start + i + 1, k - 1);
		if (sum < Minsum)
			Minsum = sum;
	}
	return Minsum;
}