分解：先把数组从中间分开，分到只有一个元素

合并：合并的时候将两个部分进行比较，进行排序

关键：合并子数组

和快速排序相反 


#include<stdio.h>
#include<stdlib.h>

int comeIn(int a[],int n,int mark);
void Merge(int left, int right ,int center ,int *temArray,int a[]);
void rec_Sort(int a[],int *temArray,int left,int right);
 
int main()
{
	int left,right;
	int a[20];
	int n,j,mark,i;
	n = 0;
	n = comeIn(a,j,mark);
	int *temArray = (int *)malloc(sizeof(int) *n);
	left = 0;right = n-1;
	rec_Sort(a,temArray,left,right);

	for(i = 0;i <= n - 1;i++)
	{
		printf("%d ",a[i]);
	}
	return 0;
}


int comeIn(int a[],int n,int mark)
{
	printf("请输入一些数字，输入-999结束，此程序会为您把它们进行升序排列:\n");
	scanf("%d",&mark);
	while(mark != -999)
	{
		a[n++] = mark;
		scanf("%d",&mark);
	}
	return n;
}

void Merge(int left, int right ,int center ,int *temArray,int a[])
{
	int p,q;
	int r = 0;
	p = left;
	q = center + 1;
	while(p <= center && q <= right)
	{
		if(a[p] > a[q])
		{
			temArray[r++] = a[q++];
		}
		else
		{
			temArray[r++] = a[p++];
		}
	}
	while(p <= center)
	{
		temArray[r++] = a[p++];
	}
	while(q <= right)
	{
		temArray[r++] = a[q++];
	}
	for(int i = 0;i <= right - left;i++)
	{
		a[left + i] = temArray[i];
	}
}

void rec_Sort(int a[],int *temArray,int left,int right)
{
	int center;
	if(right > left)
	{
		center = left + (right - left) / 2;
		rec_Sort(a,temArray,left,center);
		rec_Sort(a,temArray,center + 1,right);
		Merge(left,right,center,temArray,a);
	}
}


