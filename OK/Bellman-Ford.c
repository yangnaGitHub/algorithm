#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10000
typedef struct Edge{
    int Snode;
    int Dnode;
    int Len;
}EDGEINFO, *EDGE;

/*******************************************
允许输入图中存在负权边，只要不存在从源点可达的负权回路
图中可以存在负权边，但此条负权边，构不成负权回路，不影响回路的形成
在不包含负权回路的图中，是可以得出d[v]<=d[u]+w(u，v)
单源最短路径(从源点s到其它所有顶点v);
有向图&无向图(无向图可以看作(u,v),(v,u)同属于边集E的有向图);
边权可正可负(如有负权回路输出错误提示);
差分约束系统;
第一，初始化所有点。每一个点保存一个值，表示从原点到达这个点的距离，将原点的值设为0，其它的点的值设为无穷大（表示不可达）。
第二，进行循环，循环下标为从1到n－1（n等于图中点的个数）。在循环内部，遍历所有的边，进行松弛计算。
第三，遍历途中所有的边（edge（u，v）），判断是否存在这样情况：d（v） > d (u) + w(u,v),则返回false，表示途中存在从源点可达的权为负的回路
如果存在从源点可达的权为负的回路。则 应为无法收敛而导致不能求出最短路径。
*******************************************/
void Bellman_Ford(EDGE edge, int nodenum, int edgenum){
    int xindex = 0, yindex = 0;
    int *Dis = malloc(sizeof(int) * nodenum);
    int *pre = malloc(sizeof(int) * nodenum);
    memset(Dis, 0, sizeof(int) * nodenum);
    memset(pre, 0, sizeof(int) * nodenum);
    Dis[0] = 0;
    for(xindex = 1; xindex < nodenum; xindex++)
        Dis[xindex] = MAX;
    for(xindex = 0; xindex < nodenum; xindex++){
        for(yindex = 0; yindex < edgenum; yindex++){
            if(Dis[edge[yindex].Dnode] > Dis[edge[yindex].Snode] + edge[yindex].Len){
                Dis[edge[yindex].Dnode] = Dis[edge[yindex].Snode] + edge[yindex].Len;
                pre[edge[yindex].Dnode] = Dis[edge[yindex].Snode];
            }
        }
    }
    for(xindex = 0; xindex < edgenum; xindex++){
        if(Dis[edge[xindex].Dnode] > Dis[edge[xindex].Snode] + edge[xindex].Len)
            return 1;
    }
    for(xindex = 0; xindex < nodenum; xindex++)
        printf("%d ", Dis[xindex]);
    printf("\n");
    for(xindex = 0; xindex < nodenum; xindex++)
        printf("%d ", pre[xindex]);
    free(Dis);
    free(pre);
    if(NULL != Dis || NULL != pre){
        Dis = pre = NULL;
    }
    return 0;
}

void main(){
    int EdgeNum = 0, NodeNum = 0, index = 0;
    EDGE MyEdge = NULL;
    int Mynode[][3] = {{0, 1, 6}, {0, 2, 7}, {1, 2, 8}, {1, 3, 5}, {1, 4, -4}, {2, 3, -3}, {2, 4, 9}, {3, 1, -2}, {4, 3, 7}, {4, 0, 2}};
    /*printf("Please Enter NodeNum and EdgeNum > ");
    scanf("%d%d", &NodeNum, &EdgeNum);*/
    EdgeNum = 10;
    NodeNum = 5;
    MyEdge = (EDGE)malloc(sizeof(EDGEINFO) * EdgeNum);
    memset(MyEdge, 0, sizeof(EDGEINFO) * EdgeNum);
    while(index < EdgeNum){
        /*printf("Please Enter EDGE%2d SNode Dnode and Len > ", index + 1);
        scanf("%d %d %d", &(MyEdge[index].Snode), &(MyEdge[index].Dnode), &(MyEdge[index].Len));*/
        MyEdge[index].Snode = Mynode[index][0];
        MyEdge[index].Dnode = Mynode[index][1];
        MyEdge[index].Len = Mynode[index][2];
        index++;
    }
    Bellman_Ford(MyEdge, NodeNum, EdgeNum);
}
