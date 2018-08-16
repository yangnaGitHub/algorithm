#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 6
#define MAX 10000

/*******************************************
算法解决的是有向图中单个源点到其他顶点的最短路径问题
Dijkstra算法是典型最短路径算法，用于计算一个节点到其他所有节点的最短路径
主要特点是以起始点为中心向外层层扩展，直到扩展到终点为止
Dijkstra算法能得出最短路径的最优解，但由于它遍历计算的节点很多，所以效率低
开放最短路径优先（OSPF，Open Shortest Path First）算法是迪科斯彻算法在网络路由中的一个具体实现
与 Dijkstra 算法不同，Bellman-Ford算法可用于具有负数权值边的图
要求图中所有的边的权值都是非负的
*******************************************/
void Dijkstra(int (*node)[SIZE]){
    int Record[SIZE] = {0}, index = 0, Tag = 0, temp = 0, Value = 0;
    while(index < SIZE)
        Record[index] = node[0][index++];
    index = 1;
    while(index < SIZE){
        Tag = 1;
        while(Tag < SIZE){
            temp = node[index][Tag];
            if(0 != temp && MAX != temp){
                Value = Record[index] + temp;
                if(Value < Record[Tag])
                    Record[Tag] = Value;
            }
            Tag++;
        }
        index++;
    }
    Tag = 0;
    while(Tag < SIZE)
        printf("%d ", Record[Tag++]);
}

void main(){
    int Martix[SIZE][SIZE] = {{0, 7, 9, MAX, MAX, 14}, {7, 0, 10, 15, MAX, MAX}, {9, 10, 0, 11, MAX, 2}, {MAX, 15, 11, 0, 6, MAX}, {MAX, MAX, MAX, 6, 0, 9}, {14, MAX, 2, MAX, 9, 0}};
    Dijkstra(Martix);
}
