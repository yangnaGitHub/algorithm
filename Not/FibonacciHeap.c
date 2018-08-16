#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10000

/*******************************************
Dijkstra 算法使用了松弛技术，对每个顶点v<-V，都设置一个属性d[v]，用来描述从源点s到v的最短路径上权值的上界，称为最短路径的估计
最小优先队列fibonacci堆效率最高


*******************************************/
