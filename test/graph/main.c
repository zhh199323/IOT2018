#include "mgraph.h"
#include "heap.h"
#include <stdio.h>
#include <windows.h>
////chen yue graph && cs106x graph
int main(int argc, char const *argv[])
{
    MGraph G;
    int dist[MaxVertexNum] = {INFINITY};
    int path[MaxVertexNum] = {0};
    G = BuildGraph();
    heapDijkstra(G, dist, path, 0);
    for (int i = 0; i < G->Nv; i++)
    {
        printf("Distance from 0 to %d is %d |", i, dist[i]);
        printf("Path is %d ", i);
        for (int j = path[i]; j >= 0; j = path[j])
        {
          printf("%d ",j);
        }      
        printf("\n");
    }
Sleep(2000);
return 0;
}
