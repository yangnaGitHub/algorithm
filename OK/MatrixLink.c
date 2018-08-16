#include <stdio.h>
#include <stdlib.h>

#define SIZE 6
#define MAXVALUE 1000000
/***********************************************************************
n个矩阵构成的一个链<A1,A2,A3,.......An>，其中i=1,2,...n，矩阵A的维数为pi-1 * pi，对乘积 A1A2...An 以一种最小化标量乘法次数的方式进行加全部括号
在矩阵链乘问题中，实际上并没有把矩阵相乘，目的是确定一个具有最小代价的矩阵相乘顺序。找出这样一个结合顺序使得相乘的代价最低
要计算AiAi+1....Aj的值，计算Ai...j过程当中肯定会存在某个k值（i<=k<j）将Ai...j分成两部分，使得Ai...j的计算量最小。分成两个子问题Ai...k和Ak+1...j，需要继续递归寻找这两个子问题的最优解
设m[i,j]为计算机矩阵Ai...j所需的标量乘法运算次数的最小值，对此计算A1..n的最小代价就是m[1,n]
当i==j时：m[i,j] = 0，（此时只包含一个矩阵）
当i<j 时：从步骤1中需要寻找一个k（i≤k＜j）值，使得m[i,j] ＝min{m[i,k]+m[k+1,j]+pi-1pkpj} （i≤k＜j）  [pi-1 pi][pi pi+1]...[pk-1 pk]+[pk pk+1]...[pj-1 pj] pi-1 pk pj
矩阵Ai的维数为pi-1pi，i=1,2.....n。输入序列为：p=<p0，p1,...pn>，length[p] = n+1。使用m[n][n]保存m[i,j]的代价，s[n][n]保存计算m[i,j]时取得最优代价处k的值，最后可以用s中的记录构造一个最优解
***********************************************************************/
void MatrixLink(int *Dim, int (*Value)[SIZE + 1], int (*Save)[SIZE + 1], int Size){
    int xindex = 0, yindex = 0, zindex = 0, Tag = 0;
    for(xindex = 0; xindex <= Size; ++xindex) Value[xindex][xindex] = 0;
    for(zindex = 2; zindex <= Size; zindex++){
        for(xindex = 1; xindex <= Size - zindex + 1; xindex++){
            yindex = xindex + zindex - 1;
            Value[xindex][yindex] = MAXVALUE;
            for(Tag = xindex; Tag <= yindex - 1; Tag++){
                //printf("%d %d %d\n", xindex, yindex, Tag);
                int Temp = Value[xindex][Tag] + Value[Tag + 1][yindex] + Dim[xindex - 1] * Dim[Tag] * Dim[yindex];
                if(Temp < Value[xindex][yindex]){
                    Value[xindex][yindex] = Temp;
                    Save[xindex][yindex] = Tag;
                }
            }
        }
    }
}

void MyMatrixLink(int *Dim, int (*Value)[SIZE + 1], int (*Save)[SIZE + 1], int Size){
    int xindex = 0, yindex = 0, zindex = 0, Temp = 0;
    for(xindex = 0; xindex <= Size; ++xindex) Value[xindex][xindex] = 0;
    xindex = 1;
    while(xindex <= Size){
        yindex = xindex + 1;
        while(yindex <= Size){
            Value[xindex][yindex] = MAXVALUE;
            zindex = xindex;
            while(zindex < yindex){
                //printf("%d %d %d\n", xindex, yindex, zindex);
                int Temp = Value[xindex][zindex] + Value[zindex + 1][yindex] + Dim[xindex - 1] * Dim[zindex] * Dim[yindex];
                if(Temp < Value[xindex][yindex]){
                    Value[xindex][yindex] = Temp;
                    Save[xindex][yindex] = zindex;
                }
                zindex++;
            }
            yindex++;
        }
        xindex++;
    }
}

void ShowPriority(int (*Save)[SIZE + 1], int Start, int End){
    if(Start == End)
        printf("A%d", Start);
    else{
        printf("(");
        ShowPriority(Save, Start, Save[Start][End]);
        ShowPriority(Save, Save[Start][End] + 1, End);
        printf(")");
    }
}

void main(){
    int Dim[SIZE + 1] = {30, 35, 15, 5, 10, 20, 25};
    int Value[SIZE + 1][SIZE + 1] = {0};
    int Save[SIZE + 1][SIZE + 1] = {0};
    int xindex = 0, yindex = 0;
    MatrixLink(Dim, Value, Save, SIZE);
    ShowPriority(Save, 1, SIZE);
}
