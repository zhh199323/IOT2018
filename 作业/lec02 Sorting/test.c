#include <stdio.h>
#include <assert.h>
#include "sort.h"
#define N 15





int main(int argc, char const *argv[])
{

    int a[N] = {19, 38, 12, 40, 41, 39, 54, 76, 35, 47, 80, 14, 9, 44, 19};
    printArray(a, N);
    BInsertSort(a,N);
    printArray(a, N);


    mergeSort(a, N);
    printArray(a, N);
    
    quickSort(a, N);
    printArray(a, N);

    return 0;
}


