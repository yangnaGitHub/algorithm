#include <stdio.h>
#include <stdlib.h>

/*********************************************************************
（1）决定问题的最优子结构
（2）设计出一个递归解
（3）证明在递归的任一阶段，最优选择之一总是贪心选择。保证贪心选择总是安全的。
（4）证明通过贪心选择，所有子问题（除一个意外）都为空。
（5）设计出一个实现贪心策略的递归算法。
（6）将递归算法转换成迭代算法。
贪心算法：
（1）贪心算法中，作出的每步贪心决策都无法改变，因为贪心策略是由上一步的最优解推导下一步的最优解，而上一部之前的最优解则不作保留；
（2）由（1）中的介绍，可以知道贪心法正确的条件是：每一步的最优解一定包含上一步的最优解。
动态规划算法：
（1）全局最优解中一定包含某个局部最优解，但不一定包含前一个局部最优解，因此需要记录之前的所有最优解 ；
（2）动态规划的关键是状态转移方程，即如何由以求出的局部最优解来推导全局最优解 ；
（3）边界条件：即最简单的，可以直接得出的局部最优解。
description:有一个窃贼在偷窃一家商店时发现有n件物品，第i件物品价值为vi元，重量为wi，假设vi和wi都为整数。他希望带走的东西越值钱越好，但他的背包中之多只能装下W磅的东西，W为一整数。他应该带走哪几样东西
  01背包的状态转换方程 f[i,j] = Max{f[i-1,j-Wi]+Pi(j >= Wi), f[i-1,j]}
  f[i,j]表示在前i件物品中选择若干件放在承重为 j 的背包中，可以取得的最大价值。
name weight	value	1	2	3	4	5	6	7	8	9	10
   a	   2	6	0	6	6	9	9	12	12	15	15	15
   b	   2	3	0	3	3	6	6	9	9	9	10	11
   c	   6	5	0	0	0	6	6	6	6	6	10	11
   d	   5	4	0	0	0	6	6	6	6	6	10	10
   e	   4	6	0	0	0	6	6	6	6	6	6	6
e2单元格表示e行2列的单元格，这个单元格的意义是用来表示只有物品e时，有个承重为2的背包，那么这个背包的最大价值是0，因为e物品的重量是4
a8=15,是怎么得出的呢？根据01背包的状态转换方程(f[i,j] = Max{f[i-1,j-Wi]+Pi(j >= Wi), f[i-1,j]})，需要考察两个值
   f[i-1,j]表示我有一个承重为8的背包，当只有物品b,c,d,e四件可选时，这个背包能装入的最大价值
   f[i-1,j-Wi]表示我有一个承重为6的背包(等于当前背包承重减去物品a的重量),当只有物品b,c,d,e四件可选时，这个背包能装入的最大价值
     f[i-1,j-Wi]就是指单元格b6,值为9，Pi指的是a物品的价值，即6
**********************************************************************/
typedef struct Item{
    int weight;
    int value;
}ITEMINFO, *ITEM;

int OpValue(int *Full, int xindex, int yindex, int flag, int value){
    int index = xindex * 11 + yindex;
    if(flag)
        return *(Full + index);
    else
        *(Full + index) = value;
    return 0;
}

void BackPack(ITEM iteminfo, int *Full, int * Record, int SIZE){
    int xindex = 0, yindex = 0, starttemp = 0, endtemp = 0, temp = 0;
    for(xindex = 0; xindex < SIZE; xindex++){
        OpValue(Full, xindex, 0, 0, 0);
        OpValue(Full, xindex, 1, 0, 0);
    }
    for(yindex = 1; yindex < 11; yindex++){
        for(xindex = 1; xindex < SIZE; xindex++){
            starttemp = endtemp = 0;
            starttemp = OpValue(Full, xindex - 1, yindex, 1, 0);
            if(0 <= yindex - (iteminfo[xindex]).weight)
                endtemp = OpValue(Full, xindex - 1, yindex - (iteminfo[xindex]).weight, 1, 0) + (iteminfo[xindex]).value;
            //temp = starttemp > endtemp ? starttemp : endtemp;
            if(starttemp > endtemp){
                OpValue(Full, xindex, yindex, 0, starttemp);
                OpValue(Record, xindex, yindex, 0, 0);
            }
            else{
                OpValue(Full, xindex, yindex, 0, endtemp);
                OpValue(Record, xindex, yindex, 0, 1);
            }
        }
    }
    /*for(xindex = 1; xindex < SIZE; xindex++){
        for(yindex = 1; yindex < 11; yindex++)
            printf("%2d ", OpValue(Full, xindex, yindex, 1, 0));
        printf("\n");
    }
    for(xindex = 1; xindex < SIZE; xindex++){
        for(yindex = 1; yindex < 11; yindex++)
            printf("%2d ", OpValue(Record, xindex, yindex, 1, 0));
        printf("\n");
    }*/
}

void ParseRecord(ITEM iteminfo, int *Record, int SIZE){
    int xindex = SIZE - 1, yindex = 10, KeyPoint = 0;
    while(xindex){
        KeyPoint = OpValue(Record, xindex, yindex, 1, 0);
        if(KeyPoint){
            printf("Item %d: Weight %d Value %d\n", xindex, (iteminfo[xindex]).weight, (iteminfo[xindex]).value);
            yindex -= (iteminfo[xindex]).weight;
        }
        xindex--;
    }
}

void main(){
    ITEMINFO iteminfo[] = {{0, 0}, {2, 6}, {2, 3}, {6, 5}, {5, 4}, {4, 6}};//a b c d e
    int ITEMSIZE = sizeof(iteminfo) / sizeof(ITEMINFO);
    int *Full = malloc(ITEMSIZE * 11 * sizeof(int));
    int *Record = malloc(ITEMSIZE * 11 * sizeof(int));
    //Full[0][1]==>weight(1)+item(1)
    BackPack(iteminfo, Full, Record, ITEMSIZE);
    ParseRecord(iteminfo, Record, ITEMSIZE);
}





















