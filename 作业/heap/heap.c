#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

MaxHeap CreateHeap(int MaxSize)
{ /*参数MaxSize是大小 返回创建容量为MaxSize的空的最大堆 */

    MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType *)malloc((MaxSize + 1) * sizeof(ElementType));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Data[0] = MAXDATA; /* 定义"哨兵"为大于堆中所有可能元素的值*/

    return H;
}

bool IsFull(MaxHeap H)      //满为true，不满为false
{
    return (H->Size == H->Capacity);
}

bool Insert(MaxHeap H, ElementType X)
{ /* 将元素X插入最大堆H，其中H->Data[0]已经定义为哨兵 */
    int i;
    if (IsFull(H))
    {
        printf("最大堆已满");
        return false;
    }
    i = ++H->Size; /* i指向插入后堆中的最后一个元素的位置 */
    for (; H->Data[i / 2] < X; i /= 2)
        H->Data[i] = H->Data[i / 2]; /* 上滤X */
    H->Data[i] = X;                  /* 将X插入 */
    return true;
}

#define ERROR -1 /* 错误标识应根据具体情况定义为堆中不可能出现的元素值 */


bool IsEmpty(MaxHeap H)
{
    return (H->Size == 0);
}

ElementType DeleteMax(MaxHeap H)
{ /* 从最大堆H中取出键值为最大的元素，并删除一个结点 */
    int Parent, Child;
    ElementType MaxItem, X;

    if (IsEmpty(H))
    {
        printf("最大堆已为空");
        return ERROR;
    }

    MaxItem = H->Data[1]; /* 取出根结点存放的最大值 */
    /* 用最大堆中最后一个元素从根结点开始向上过滤下层结点 */
    X = H->Data[H->Size--]; /* 注意当前堆的规模要减小 */
    for (Parent = 1; Parent * 2 <= H->Size; Parent = Child)
    {
        Child = Parent * 2;
        if ((Child != H->Size) && (H->Data[Child] < H->Data[Child + 1]))
            Child++; /* Child指向左右子结点的较大者 */
        if (X >= H->Data[Child])
            break; /* 找到了合适位置 */
        else       /* 下滤X */
            H->Data[Parent] = H->Data[Child];
    }
    H->Data[Parent] = X;

    return MaxItem;
}

/*----------- 建造最大堆 -----------*/
void PercDown(MaxHeap H, int p)
{ /* 下滤：将H中以H->Data[p]为根的子堆调整为最大堆 */
    int Parent, Child;
    ElementType X;

    X = H->Data[p]; /* 取出根结点存放的值 */
    for (Parent = p; Parent * 2 <= H->Size; Parent = Child)
    {
        Child = Parent * 2;
        if ((Child != H->Size) && (H->Data[Child] < H->Data[Child + 1]))
            Child++; /* Child指向左右子结点的较大者 */
        if (X >= H->Data[Child])
            break; /* 找到了合适位置 */
        else       /* 下滤X */
            H->Data[Parent] = H->Data[Child];
    }
    H->Data[Parent] = X;
}
void print(MaxHeap H)
{
    Queue *Q;
    Q=(Queue*)malloc(sizeof(struct Queue));
    int i=1;
    int max=H->Size;
    InitQueue(Q);
    EnQueue(Q,H->Data[i]);

    while (!QueueEmpty(Q))
    {
        printf("%d ",DeQueue(Q));
        if(2*i<=max)
            EnQueue(Q,H->Data[2*i]);
        if(2*i+1<=max)
            EnQueue(Q,H->Data[2*i+1]);
        i++;
    }
    printf("\n");
}
void InitQueue(Queue *Q)
{
    Q->data=(ElementType*)malloc(sizeof(ElementType)*100);
    if(!Q->data)
        exit(-1);
    Q->front = Q->rear =0;
    Q->queuesize=MAXDATA/10;
}

bool EnQueue(Queue* Q, ElementType e)
{
    *(Q->data+Q->rear)=e;
    Q->rear=(Q->rear+1);
    return true;
}

int  DeQueue (Queue *Q)
{
    int e=*(Q->data+Q->front);
    Q->front=Q->front+1;
    return e;
}


int GetQueue (Queue *Q)
{
    return *(Q->data+Q->front);
}

bool QueueEmpty (Queue * Q)
{
    if(Q->front==Q->rear)
        return true;
    else
        return false;
}