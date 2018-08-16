#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 3
int MovePoint(int (*num)[SIZE], int dirction);
/*******************************************
BFS && DFS(深度和廣度優先遍歷圖認為他的子節點都是一樣的)
啟發式搜索中會有一個估值函數（評價函數），判斷某個子節點優於其他的子節點
代價==>排序(排序就是對Open表的整體排序，就是對後續展開的子節點排序，使得程序有啟發性，可以更快的搜索出目標解)
估值函数只考虑结点的某种性能上的价值，而不考虑深度，比较有名的就是有序搜索（Ordered-Search），它着重看好能否找出解，而不看解离起始结点的距离
估值函数考虑了深度，或者是带权距离（从起始结点到目标结点的距离加权和），那就是A*
简单的来说A*就是将估值函数分成两个部分，一个部分是路径价值，另一个部分是一般性启发价值，合在一起算估整个结点的价值。
八数码问题一般使用搜索法来解。搜索法有广度优先搜索法、深度优先搜索法、A*算法
2 8 3      1 2 3
1 6 4  ==> 8   4
7   5      7 6 5
2 8 3      2 8 3     2 8 3     2 8 3
1 6 4  ==> 1   4  +  1 6 4  +  1 6 4
7   5      7 6 5     7 5         7 5
启发式搜索：启发式搜索就是在状态空间中的搜索对每一个搜索的位置进行评估，得到最好的位置，再从这个位置进行搜索直到目标。这样可以省略大量无谓的搜索路径，提高了效率
每次移动的时候，正确位置数码的个数要大于交换前正确位置数码个数
*******************************************/
int IsGoodState(int (*num)[SIZE]){
    int xindex = 0, yindex = 0, count = 0;
    int good[][SIZE] = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};
    for(xindex = 0; xindex < SIZE; xindex++){
        for(yindex = 0; yindex < SIZE; yindex++){
            if(good[xindex][yindex] == num[xindex][yindex])
                count++;
        }
    }
    return count;
}

int ActualMove(int (*num)[SIZE], int dirction, int ZXindex, int ZYindex, int flag){
    int Xtemp = ZXindex, Ytemp = ZYindex, result = 0;
    switch(dirction){
    case 1:Xtemp--;break;
    case 2:Xtemp++;break;
    case 3:Ytemp--;break;
    case 4:Ytemp++;break;
    default:printf("MOVE DIRCTION ERROR\n");
    }
    num[ZXindex][ZYindex] = num[Xtemp][Ytemp];
    num[Xtemp][Ytemp] = 0;
    result = IsGoodState(num);
    if(!flag){
        num[Xtemp][Ytemp] = num[ZXindex][ZYindex];
        num[ZXindex][ZYindex] = 0;
    }
    return result;
}

/*void InitTemp(int (*num)[SIZE], int (*Temp)[SIZE]){
    int xindex = 0, yindex = 0;
    for(xindex = 0; xindex < SIZE; xindex++){
        for(yindex = 0; yindex < SIZE; yindex++)
            Temp[xindex][yindex] = num[xindex][yindex];
    }
}
int ComTemp1[SIZE][SIZE] = {0};
int ComTemp2[SIZE][SIZE] = {0};
int temp1 = 0, temp2 = 0;
if(MaxMove == Move){
    //Step 2 MaxDirction xindex + 1
    InitTemp(num, ComTemp1);
    InitTemp(num, ComTemp2);
    ActualMove(ComTemp1, MaxDirction, ZXindex, ZYindex, 1);
    ActualMove(ComTemp2, xindex + 1, ZXindex, ZYindex, 1);
    temp1 = MaxDirction;
    temp2 = xindex + 1;
    while(1){
        temp1 = MovePoint(ComTemp1, (12 / temp1) % 5);
        temp2 = MovePoint(ComTemp2, (12 / temp2) % 5);
        if(IsGoodState(ComTemp1) != IsGoodState(ComTemp2)){
            if(IsGoodState(ComTemp1) < IsGoodState(ComTemp2)){
                MaxMove = Move;
                MaxDirction = xindex + 1;
            }
            break;
        }
    }
    //MovePoint
}*/
int AccrodDirctionMovePoint(int (*num)[SIZE], int *MoveDirction, int ZXindex, int ZYindex){
    int xindex = 0, yindex = 0, Move = 0, MaxMove = 0, MaxDirction = 0;
    for(xindex = 0; xindex < 4; xindex++){
        if(!MoveDirction[xindex])
            continue;
        Move = ActualMove(num, xindex + 1, ZXindex, ZYindex, 0);
        if(MaxMove < Move){
            MaxMove = Move;
            MaxDirction = xindex + 1;
        }
    }
    ActualMove(num, MaxDirction, ZXindex, ZYindex, 1);
    return MaxDirction;
}
//forbid state
//Last Move Direction
//ZeroYindex == 0 Left(X) = SIZE - 1 Right(X)
//ZeroXindex == 0 Up(X) = SIZE - 1 Down(X)
int MovePoint(int (*num)[SIZE], int Lastdirction){
    int ZeroXindex = 0, ZeroYindex = 0, xindex = 0, yindex = 0, BreakFlag = 0;
    int MoveDirction[4] = {1, 1, 1, 1};
    for(xindex = 0; xindex < SIZE; xindex++){
        for(yindex = 0; yindex < SIZE; yindex++){
            if(0 == num[xindex][yindex]){
                ZeroXindex = xindex;
                ZeroYindex = yindex;
                BreakFlag = 1;
                break;
            }
        }
        if(BreakFlag)
            break;
    }
    if(Lastdirction)
        MoveDirction[Lastdirction - 1] = 0;
    if(0 == ZeroXindex)
        MoveDirction[0] = 0;
    else if((SIZE - 1) == ZeroXindex)
        MoveDirction[1] = 0;
    if(0 == ZeroYindex)
        MoveDirction[2] = 0;
    else if((SIZE - 1) == ZeroYindex)
        MoveDirction[3] = 0;
    return AccrodDirctionMovePoint(num, MoveDirction, ZeroXindex, ZeroYindex);

}

void ListNum(int (*num)[SIZE], int dirction){
    int xindex = 0, yindex = 0;
    switch(dirction){//Zero Move Status
    case 1: printf("Up    Move\n");break;
    case 2: printf("Down  Move\n");break;
    case 3: printf("Left  Move\n");break;
    case 4: printf("Right Move\n");break;
    default:printf("MOVE DIRCTION ERROR\n");return ;
    }
    for(xindex = 0; xindex < SIZE; xindex++){
        for(yindex = 0; yindex < SIZE; yindex++)
            printf("%d ", num[xindex][yindex]);
        printf("\n");
    }
}

void Heuristic(int (*num)[SIZE]){
    int goodpoint = IsGoodState(num);
    int dirction = 0;
    while(9 != goodpoint){
        dirction = MovePoint(num, dirction);
        ListNum(num, dirction);
        dirction = (12 / dirction) % 5;
        goodpoint = IsGoodState(num);
    }
}

void main(){
    int num[][SIZE] = {{2, 8, 3}, {1, 6, 4}, {7, 0, 5}};
    Heuristic(num);
}
