//快速排序
//
//分治过程
//
//分解：从数组中选取一个主元x，根据x的值，将数组划分成两个子数组，使得前一个数组的每个元素<= x<= 后一个数组中的每个元素 
//
//       <=x  | x |  >=x
//
//解决：对两个子数组进行递归排序
//
//合并：什么都不需要做
//
//关键：划分子过程 
//
//和归并排序相反
//
//
//四个区域
//一：主元x
//二：<=x的区域
//三：>x的区域
//四：未排序的区域
//
//i为区域一的最后一个下标
//j为区域三的第一个元素
//i+1到j-1是区域二的元素 
//
//x|      <=x       |     >=x         |    ??? 
//                ↑                    ↑
//				i                     j 
//
//如果区域四的元素比x大，则进入区域三
//直接j++
//如果区域四的元素比x小，则进入区域二
//先i++，将i的元素和j的元素换位置，然后j++ 
//
//都排序完了之后把i和x换位置即可 

#include<stdio.h>


void qSort(int a[], int p, int q);
int rec_quickSort(int a[],int p,int q);
void print_qSort(int n,int a[]);

int main()
{
	int a[8] = {1,3,5,4,2,6,9,7};
	int p = 0;
	int q = 7;	
	qSort(a,p,q);
	print_qSort(7,a);
 } 
 
 
 void qSort(int a[], int p, int q)                  //快速排序的函数 
{
	int r;
	if(p < q)
	{
		r = rec_quickSort(a,p,q);
		qSort(a,p,r);                               //递归调用自己，不断拆分 
		qSort(a,r+1,q);
	}
}


int rec_quickSort(int a[],int p,int q)
{
	int x = a[p];
	int i = p;
	int temp;
	for(int j = p+1 ; j <= q; j++)
	{
		if(a[j] <= x)
		{
			i++;
			temp = a[i];                            //排序过程 
			a[i] = a[j];
			a[j] = temp;
		}
	}
	temp = a[i];
	a[i] = a[p];
	a[p] = temp;
	
	return i;
} 



void print_qSort(int n,int a[])
{
	for(int i = 0 ; i <= n ; i++)
	{
		printf("%d",a[i]);
	 } 
}
