//一趟快速排序的算法是：
//1）设置两个变量i、j，排序开始的时候：i=0，j=N-1；
//2）以第一个数组元素作为关键数据，赋值给key，即key=A[0]；
//3）从j开始向前搜索，即由后开始向前搜索(j--)，找到第一个小于key的值A[j]，将A[j]和A[i]的值交换；
//4）从i开始向后搜索，即由前开始向后搜索(i++)，找到第一个大于key的A[i]，将A[i]和A[j]的值交换；
//5）重复第3、4步，直到i=j； (3,4步中，没找到符合条件的值，即3中A[j]不小于key,4中A[i]不大于key的时候改变j、i的值，使得j=j-1，i=i+1，直至找到为止。找到符合条件的值，进行交换的时候i， j指针位置不变。另外，i==j这一过程一定正好是i+或j-完成的时候，此时令循环结束）。


#include<stdio.h>

void quick_sort(int a[]);
void rec_quick(int a[],int i,int j);
 
int main(){
	int a[8] = {7,3,1,9,5,4,6,8};
	quick_sort(a);
	for(int i = 0 ; i < 8 ; i++)
	{
		printf("%d ",a[i]);
	}
	return 0;
} 

void rec_quick(int a[],int i,int j)
{
	int left = i;
	int right = j;
	int key = a[i];
	if(i < j)
	{
		while(i < j)
		{
			while(a[j] >= key && i < j)
			{
				j--;
				
			}
			
			a[i] = a[j];
			
			while(a[i] <=key && i <j)
			{
				i++;
			}
			
			a[j] = a[i];
		}
		a[i] = key;
		rec_quick(a,left,i-1);
		rec_quick(a,i+1,right);
	}
}

void quick_sort(int a[]){
	int i,j;
	i = 0; j = 7;
	rec_quick(a,i,j);
}


