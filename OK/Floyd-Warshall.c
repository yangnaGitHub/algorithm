#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define SIZE 4
#define SIZE 5
#define MAX 10000
/*******************************************
Floyd-Warshall算法（Floyd-Warshall algorithm）是解决任意两点间的最短路径的一种算法，可以正确处理有向图或负权的最短路径问题，同时也被用于计算有向图的传递闭包。
Floyd-Warshall算法的时间复杂度为O(N3)，空间复杂度为O(N2)
*******************************************/
void MidFill(int (*node)[SIZE], int xvalue, int yvalue){
    int xindex = 0, Value = 0, temp = 0, org = node[xvalue][yvalue];
    while(xindex < SIZE){
        temp = node[xindex][xvalue];
        if(0 != temp && MAX != temp){
            Value = temp + org;
            if(Value < node[xindex][yvalue])
                node[xindex][yvalue] = Value;
        }
        xindex++;
    }
}

void Floyd(int (*node)[SIZE]){
    int xindex = 0, yindex = 0, temp = 0;
    while(xindex < SIZE){
        //以index作为中间节点
        yindex = 0;
        while(yindex < SIZE){
            temp = node[xindex][yindex];
            if(0 != temp && MAX != temp)
                MidFill(node, xindex, yindex);
            yindex++;
        }
        xindex++;
    }
    for(xindex = 0; xindex < SIZE; xindex++){
        for(yindex = 0; yindex < SIZE; yindex++)
            printf("%2d ", node[xindex][yindex]);
        printf("\n");
    }
}
//此算法無法應對負迴路
void main(){
    int Matrix[SIZE][SIZE] = {{0, 6, 7, MAX, MAX}, {MAX, 0, 8, 5, -4}, {MAX, MAX, 0, -3, 9}, {MAX, -2, MAX, 0, MAX}, {2, MAX, MAX, MAX, 0}};
    //{{0, MAX, 3, MAX}, {2, 0, MAX, MAX}, {MAX, 7, 0, 1}, {6, MAX, MAX, 0}};
    Floyd(Matrix);
}

