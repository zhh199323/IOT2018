#include "heap.h"

int main(int argc, char const *argv[])
{
   MaxHeap heap;                //构建大顶堆
    int n, m, choice;
    while(1)
    {
        printf("Please input choice\n");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
                printf("Please input node number:\n");
                scanf("%d", &n);
                heap = CreateHeap(n);
                printf("Please input nodes:\n");
                for (int i = 0; i < n; i++)
                {        
                    scanf("%d", &m);
                    Insert(heap, m);
                }
                break;
            case 2:
                m=heap->Size;
                for (int i = 0; i < m; i++)
                {
                    printf("%d",DeleteMax(heap));
                }
                break;
            case 3:
                print(heap);
                break;
            default:
                exit(-1);
        }
    }
        Sleep(2000);
        return 0;
    
}
