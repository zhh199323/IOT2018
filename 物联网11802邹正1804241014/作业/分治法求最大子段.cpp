#include <stdio.h>  
  
int maxSubValues(int nums[], int minIndex, int maxIndex) {  
    int sum = 0;  
    int allMax = 0;  
    int leftMax = 0;  
    int rightMax = 0;  
    int middleIndex = (minIndex + maxIndex) / 2;  
    int i;  
    if (minIndex == maxIndex) { // �����һ��Ԫ����  
        if (nums[minIndex] < 0) { // ����Ӷ��и��涨��������ݶ��Ǹ���������Ӷ�ֵΪ0  
            return 0;  
        } else {  
            return nums[minIndex];  
        }  
    }  
    leftMax = maxSubValues(nums, minIndex, middleIndex);  
    rightMax = maxSubValues(nums, middleIndex+1, maxIndex);  
    for (i=middleIndex; i>=0; i--) { // ���е������ۼ����ֵ  
        sum += nums[i];  
        if (allMax < sum) {  
            allMax = sum;  
        }  
    }  
    sum = allMax; // �������ֵ  
    for (i=middleIndex+1; i <= maxIndex; i++) {  
        sum += nums[i]; // �����ۼ����ֵ�����ۼӣ��ҵ������ۼ����ֵ  
        if (allMax < sum) {  
            allMax = sum;  
        }  
    }  
    // �Ƚ��������Ӷκ��Ҳ�����Ӷλ����м��������ۼӵ����ֵ����˭����  
    if (allMax < leftMax) {  
        allMax = leftMax;  
    } else if (allMax < rightMax) {  
        allMax = rightMax;  
    }  
    return allMax;  
}  
  
int main(int argc, char **argv) {  
    int nums[5];
    int i;
    printf("������5����"); 
	for(i=0;i<5;i++)
	{
		scanf("%d\n",&nums[i]);
	 } 
    printf("max sub:%d\n", maxSubValues(nums, 0, sizeof nums / sizeof(int) - 1));  
    return 0;  
}  
