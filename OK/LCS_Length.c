#include <stdio.h>
#include <stdlib.h>

#define XSIZE 7
#define YSIZE 6
/***********************************************************************
给定两个序列X和Y，如果Z既是X的一个子序列又是Y的一个子序列，则称序列Z是X和Y的公共子序列
X={A,B,C,B,D,A,B}，Y={B,D,C,A,B,A}，则序列{B,C,A}是X和Y的一个公共子序列

设X={x1，x2，……，xm}和Y={y1，y2，……，yn}为两个序列，并设Z={z1、z2、……，zk}为X和Y的任意一个LCS
（1）如果xm=yn，那么zk=xm=yn，而且Zk-1是Xm-1和Yn-1的一个LCS。
（2）如果xm≠yn，那么zk≠xm蕴含Z是是Xm-1和Yn的一个LCS。
（3）如果xm≠yn，那么zk≠yn蕴含Z是是Xm和Yn-1的一个LCS。
          0                             if((0 == i) || (0 == j))
c[i][j] = c[i - 1, j - 1] + 1           if(0 < i && 0 < j && x[i] == y[j])
          max(c[i, j - 1], c[i - 1, j]) if(0 < i && 0 < j && x[i] != y[j])
***********************************************************************/
void LCS_Length(char *Xstr, char *Ystr, int (*Length)[YSIZE + 1], int (*Status)[YSIZE + 1]){
    int xindex = 0, yindex = 0;
    for(xindex = 0; xindex <= XSIZE; xindex++)
        Length[xindex][0] = 0;
    for(yindex = 0; yindex <= YSIZE; yindex++)
        Length[0][yindex] = 0;
    for(xindex = 0; xindex <= XSIZE; xindex++){
        for(yindex = 0; yindex <= YSIZE; yindex++){
            if(Xstr[xindex] == Ystr[yindex]){
                Length[xindex][yindex] = Length[xindex - 1][yindex - 1] + 1;
                Status[xindex][yindex] = 0;
            }
            else if(Length[xindex - 1][yindex] >= Length[xindex][yindex - 1]){
                Length[xindex][yindex] = Length[xindex - 1][yindex];
                Status[xindex][yindex] = 1;
            }
            else{
                Length[xindex][yindex] = Length[xindex][yindex - 1];
                Status[xindex][yindex] = 2;
            }
        }
    }
}
void ShowLcs(int (*Status)[YSIZE + 1], char *Xstr, int Xsize, int Ysize){
    if(0 == Xsize || 0 == Ysize)
        return ;
    if(!Status[Xsize][Ysize]){
        ShowLcs(Status, Xstr, Xsize - 1, Ysize - 1);
        printf("%c ", Xstr[Xsize]);
    }
    else if(1 == Status[Xsize][Ysize])
        ShowLcs(Status, Xstr, Xsize - 1, Ysize);
    else ShowLcs(Status, Xstr, Xsize, Ysize - 1);
}

void main(){
    char Xstr[] = {' ', 'A', 'B', 'C', 'B', 'D', 'A', 'B'};
    char Ystr[] = {' ', 'B', 'D', 'C', 'A', 'B', 'A'};
    int Length[XSIZE + 1][YSIZE + 1] = {0};
    int Status[XSIZE + 1][YSIZE + 1] = {0};
    LCS_Length(Xstr, Ystr, Length, Status);
    ShowLcs(Status, Xstr, XSIZE, YSIZE);
}
