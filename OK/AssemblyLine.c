#include <stdio.h>
#include <stdlib.h>

/***********************************************************************
动态规划（dynamic programming）是通过组合子问题的解而解决整个问题的
分治算法是指将问题划分为一些独立的子问题，递归的求解各个问题，然后合并子问题的解而得到原问题的解
动态规划与此不同，适用于子问题不是独立的情况，也就是说各个子问题包含有公共的子问题
（1）描述最优解的结构
（2）递归定义最优解的值
（3）按自低向上的方式计算最优解的值
（4）由计算出的结果构造一个最优解
Description:一个汽车公司在有2条装配线的工厂内生产汽车，每条装配线有n个装配站，不同装配线上对应的装配站执行的功能相同，但是每个站执行的时间是不同的
            在装配汽车时，为了提高速度，可以在这两天装配线上的装配站中做出选择，即可以将部分完成的汽车在任何装配站上从一条装配线移到另一条装配线上
            进入装配线时间e、每装配线上各个装配站执行时间a、从一条装配线移到另外一条装配线的时间t、离开最后一个装配站时间x

Record[0]: 1 1 2 1 1 2
Record[1]: 2 1 2 1 2 2
           1 2 1 2 2 1 ==> Find[0][5] (Record[0][5] = 2) = Find[1][4] + xxx  2
                           Find[1][4] (Record[1][4] = 2) = Find[1][3] + xxx  2
                           Find[1][3] (Record[1][3] = 1) = Find[0][2] + xxx  1
                           Find[0][2] (Record[0][2] = 2) = Find[1][1] + xxx  2
                           Find[1][1] (Record[1][1] = 1) = Find[0][0] + xxx  1 ==> 1 2 1 2 2 (1)Exit
***********************************************************************/
void AssemblyLine(int *Enter, int *Exit, int (*Line)[6], int (*Transfer)[5], int (*Find)[6], int (*Record)[6], int Size, int *LastLine){
    int yindex = 1, MinTime = 0;
    Find[0][0] = Enter[0] + Line[0][0];
    Find[1][0] = Enter[1] + Line[1][0];
    Record[0][0] = 1;
    Record[1][0] = 2;
    while(yindex < Size){
        if(Find[0][yindex - 1] < Find[1][yindex - 1] + Transfer[1][yindex - 1]){
            Find[0][yindex] = Find[0][yindex - 1] + Line[0][yindex];
            Record[0][yindex] = 1;
        }else{
            Find[0][yindex] = Find[1][yindex - 1] + Transfer[1][yindex - 1] + Line[0][yindex];
            Record[0][yindex] = 2;
        }
        if(Find[1][yindex - 1] < Find[0][yindex - 1] + Transfer[0][yindex - 1]){
            Find[1][yindex] = Find[1][yindex - 1] + Line[1][yindex];
            Record[1][yindex] = 2;
        }else{
            Find[1][yindex] = Find[0][yindex - 1] + Transfer[0][yindex - 1] + Line[1][yindex];
            Record[1][yindex] = 1;
        }
        yindex++;
    }
    if(Find[0][Size - 1] + Exit[0] < Find[1][Size - 1] + Exit[1]){
        MinTime = Find[0][Size - 1] + Exit[0];
        *LastLine = 1;
    }else{
        MinTime = Find[1][Size - 1] + Exit[1];
        *LastLine = 2;
    }
    printf("MinTime = %d LastLine = %d\n", MinTime, *LastLine);
}



void main(){
    int Enter[2] = {2, 4};
    int Exit[2] = {3, 2};
    int Line[2][6] = {{7, 9, 3, 4, 8, 4}, {8, 5, 6, 4, 5, 7}};
    int Transfer[2][5] = {{2, 3, 1, 3, 4}, {2, 1, 2, 2, 1}};
    int Find[2][6] = {0};
    int Record[2][6] = {0};
    int LastLine = 0, index = 0;
    AssemblyLine(Enter, Exit, Line, Transfer, Find, Record, 6, &LastLine);
    //Notice:Print Path
}
