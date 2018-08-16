#include <stdio.h>
#include <stdlib.h>

#define SIZE 12
/***********************************************************************
description:需要使用每个资源的n个活动组成的集合S= {a1，a2，···，an }，资源每次只能由一个活动使用
            每个活动ai都有一个开始时间si和结束时间fi，且 0≤si<fi<∞ 。一旦被选择后，活动ai就占据半开时间区间[si,fi)
            如果[si,fi]和[sj,fj]互不重叠，则称ai和aj两个活动是兼容的。该问题就是要找出一个由互相兼容的活动组成的最大子集

            01 02 03 04 05 06 07 08 09 10 11
     si ==> 01 03 00 05 03 05 06 08 08 02 12
     fi ==> 04 05 06 07 08 09 10 11 12 13 14
{01, 04, 08, 11} {02, 04, 09, 11}
***********************************************************************/
//Dynamic
void Dynamic_ItemChoose(int *start, int *end, int size, int (*collect)[size], int (*ret)[size]){
    int xindex, yindex, zindex = 0;
    int temp = 0;
    for(yindex = 1; yindex < size; yindex++)
        for(xindex = yindex; xindex < size; xindex++)
            collect[xindex][yindex] = 0;
    for(yindex = 2; yindex < size; yindex++){
        for(xindex = 1; xindex < yindex; xindex++){
            for(zindex = xindex + 1; zindex < yindex; zindex++){
                if(start[zindex] >= end[xindex] && end[zindex] <= start[yindex]){
                    temp = collect[xindex][zindex] + collect[zindex][yindex] + 1;
                    if(collect[xindex][yindex] < temp){
                        collect[xindex][yindex] = temp;
                        ret[xindex][yindex] = zindex;
                    }
                }
            }
        }
    }
    for(xindex = 1; xindex < size; xindex++){
        for(yindex = 1; yindex < size; yindex++)
            printf("%d ", collect[xindex][yindex]);
        printf("\n");
    }
    printf("\n");
    for(xindex = 1; xindex < size; xindex++){
        for(yindex = 1; yindex < size; yindex++)
            printf("%d ", ret[xindex][yindex]);
        printf("\n");
    }
}
//Greedy
void Greedy_ItemChoose(int *start, int *end, int *greedy){
    int index = 0, loop = 0;
    int *ret = greedy;
    *(greedy++) = 1;
    index = 1;
    for(loop = 2; loop < SIZE; loop++){
        if(start[loop] >= end[index]){
            *(greedy++) = loop;
            index = loop;
        }
    }
    for(index = 0; index < (SIZE - 1); index++){
        if(0 != ret[index])
            printf("a%d ", ret[index]);
    }
}

void main(){
    int index = 0;
    int start[] = {-1, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
    int end[] = {-1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    int collect[SIZE][SIZE] = {0};
    int ret[SIZE][SIZE] = {0};
    int Greedy[SIZE - 1] = {0};
    Greedy_ItemChoose(start, end, Greedy);
}
