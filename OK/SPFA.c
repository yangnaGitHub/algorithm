#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10000
//改變存儲結構也可以使得一個算法變得簡單
typedef struct REdge{
    int Dnode;
    int Len;
    struct REdge *next;
}REDGEINFO, *REDGE;

typedef struct Edge{
    int Snode;
    REDGE *Rnode;
}EDGEINFO, *EDGE;
/*******************************************
SPFA(Shortest Path Faster Algorithm)是Bellman-Ford算法的一种队列实现，减少了不必要的冗余计算
算法大致流程是用一个队列来进行维护。 初始时将源加入队列。 每次从队列中取出一个元素，并对所有与他相邻的点进行松弛，若某个相邻的点松弛成功，则将其入队
若一个点入队次数超过n，则有负权环
第二步，不是枚举所有节点，而是通过队列来进行优化 设立一个先进先出的队列用来保存待优化的结点，优化时每次取出队首结点u，并且用u点当前的最短路径估计值对离开u点所指向的结点v进行松弛操作
  如果v点的最短路径估计值有所调整，且v点不在当前的队列中，就将v点放入队尾。这样不断从队列中取出结点来进行松弛操作，直至队列空为止。
判断有无负环：如果某个点进入队列的次数超过V次则存在负环
SPFA算法有两个优化算法 SLF 和 LLL： SLF：Small Label First 策略，设要加入的节点是j，队首元素为i，若dist(j)<dist(i)，则将j插入队首，否则插入队尾。
LLL：Large Label Last 策略，设队首元素为i，队列中所有dist值的平均值为x，若dist(i)>x则将i插入到队尾，查找下一元素，直到找到某一i使得dist(i)<=x，则将i出对进行松弛操作
*******************************************/
void ListAllNode(EDGE MyEdge, int NodeNum){
    int xindex = 0;
    REDGE Edge = NULL;
    while(xindex < NodeNum){
        Edge = NULL;
        if(NULL != MyEdge[xindex].Rnode)
            Edge = MyEdge[xindex].Rnode;
        while(NULL != Edge){
            printf("%d %d %d\n", xindex, Edge->Dnode, Edge->Len);
            Edge = Edge->next;
        }
        xindex++;
    }
}

int FillDis(EDGE MyEdge, int NodeNum, int *Dis, int *Pre, int *Res){
    int xindex = 0;
    REDGE Edge = NULL;
    while(xindex < NodeNum){
        Edge = NULL;
        if(1 == Res[xindex]){
            if(NULL != MyEdge[xindex].Rnode)
                Edge = MyEdge[xindex].Rnode;
            while(NULL != Edge){
                if(Dis[Edge->Dnode] > Dis[xindex] + Edge->Len){
                    Dis[Edge->Dnode] = Dis[xindex] + Edge->Len;
                    Pre[Edge->Dnode] = Dis[xindex];
                    if(0 == Edge->Dnode)
                        return 1;
                    if(Edge->Dnode < xindex){
                        Res[Edge->Dnode] = 1;
                        return FillDis(MyEdge, NodeNum, Dis, Pre, Res);
                    }
                }
                Edge = Edge->next;
            }
        }
        Res[xindex] = 0;
        xindex++;
    }
    return 0;
}

void SPFA(EDGE MyEdge, int NodeNum, int EdgeNum){
    int xindex = 0;
    int *Dis = malloc(sizeof(int) * NodeNum);
    int *Pre = malloc(sizeof(int) * NodeNum);
    int *Res = malloc(sizeof(int) * NodeNum);
    memset(Dis, 0, sizeof(int) * NodeNum);
    memset(Pre, 0, sizeof(int) * NodeNum);
    memset(Res, 0, sizeof(int) * NodeNum);
    ListAllNode(MyEdge, NodeNum);
    for(xindex = 0; xindex < NodeNum; xindex++){
        Dis[xindex] = MAX;
        Res[xindex] = 1;
    }
    Dis[0] = 0;
    if(FillDis(MyEdge, NodeNum, Dis, Pre, Res))
        return ;
    for(xindex = 0; xindex < NodeNum; xindex++)
        printf("%d ", Dis[xindex]);
    printf("\n");
    for(xindex = 0; xindex < NodeNum; xindex++)
        printf("%d ", Pre[xindex]);
    free(Dis);
    free(Pre);
}

void main(){
    int EdgeNum = 0, NodeNum = 0, index = 0;
    EDGE MyEdge = NULL;
    REDGE Edge = NULL, Add = NULL, OldEdge = NULL;
    int Mynode[][3] = {{0, 1, 6}, {0, 2, 7}, {1, 2, 8}, {1, 3, 5}, {1, 4, -4}, {2, 3, -3}, {2, 4, 9}, {3, 1, -2}, {4, 3, 7}, {4, 0, 2}};
    EdgeNum = 10;
    NodeNum = 5;
    MyEdge = (EDGE)malloc(sizeof(EDGEINFO) * NodeNum);
    memset(MyEdge, 0, sizeof(EDGEINFO) * NodeNum);
    while(index < EdgeNum){
        MyEdge[Mynode[index][0]].Snode = Mynode[index][0];
        Add = (REDGE)malloc(sizeof(REDGEINFO));
        memset(Add, 0, sizeof(REDGEINFO));
        Add->Dnode = Mynode[index][1];
        Add->Len = Mynode[index][2];
        if(NULL == MyEdge[Mynode[index][0]].Rnode)
            MyEdge[Mynode[index][0]].Rnode = Add;
        else{
            Edge = MyEdge[Mynode[index][0]].Rnode;
            while(NULL != Edge){
                OldEdge = Edge;
                Edge = Edge->next;
            }
            OldEdge->next = Add;
        }
        index++;
    }
    SPFA(MyEdge, NodeNum, EdgeNum);
}

/**************************************************
void SwapEdge(EDGE edge, int xnode, int ynode){
    int nodeValue = 0;
    nodeValue = edge[xnode].Dnode;
    edge[xnode].Dnode = edge[ynode].Dnode;
    edge[ynode].Dnode = nodeValue;

    nodeValue = edge[xnode].Snode;
    edge[xnode].Snode = edge[ynode].Snode;
    edge[ynode].Snode = nodeValue;

    nodeValue = edge[xnode].Len;
    edge[xnode].Len = edge[ynode].Len;
    edge[ynode].Len = nodeValue;
}
//為何不想想改變存儲結構，改變存儲結構就可以很簡單的就解決了問題(查看Bellman-Ford的對應的代碼)
char MySPFA(EDGE edge, int nodenum, int edgenum){
    int xindex = 0, yindex = 0, exceptItem = 0;
    int *Dis = malloc(sizeof(int) * nodenum);
    int *pre = malloc(sizeof(int) * nodenum);
    int *reverse = malloc(sizeof(int) * nodenum);
    memset(Dis, 0, sizeof(int) * nodenum);
    memset(pre, 0, sizeof(int) * nodenum);
    memset(reverse, 0, sizeof(int) * nodenum);
    Dis[0] = 0;
    for(xindex = 1; xindex < nodenum; xindex++)
        Dis[xindex] = MAX;
    while(yindex < nodenum){
        xindex = exceptItem;
        while(xindex < edgenum){
            if(yindex == edge[xindex].Snode){
                if(Dis[edge[xindex].Dnode] > Dis[edge[xindex].Snode] + edge[xindex].Len){
                    Dis[edge[xindex].Dnode] = Dis[edge[xindex].Snode] + edge[xindex].Len;
                    pre[edge[xindex].Dnode] = Dis[edge[xindex].Snode];
                    if(0 == edge[xindex].Dnode)
                        return 1;
                    if(edge[xindex].Dnode < edge[xindex].Snode)
                        reverse[edge[xindex].Dnode] = 1;
                }
                if(xindex != exceptItem)
                    SwapEdge(edge, xindex, exceptItem);
                exceptItem++;
            }
            xindex++;
        }
        yindex++;
    }
    for(xindex = 0; xindex < nodenum; xindex++)
        printf("%d ", Dis[xindex]);
    printf("\n");
    for(xindex = 0; xindex < nodenum; xindex++)
        printf("%d ", pre[xindex]);
    printf("\n");
    for(xindex = 0; xindex < nodenum; xindex++)
        printf("%d ", reverse[xindex]);
    free(Dis);
    free(pre);
    free(reverse);
    return 0;
}
*****************************************************/
