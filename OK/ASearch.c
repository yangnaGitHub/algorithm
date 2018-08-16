#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10000
#define SIZE 6

typedef struct Node{
    int nodeNo;
    int nodeValue;
}NODEINFO, *NODE;
/*******************************************
A*搜寻算法，还得从启发式搜索算法开始谈起
启发式搜索，就在于当前搜索结点往下选择下一步结点时，可以通过一个启发函数来进行选择
选择代价最少的结点作为下一步搜索结点而跳转其上
如果遇到有一个以上代价最少的结点，不妨选距离当前搜索点最近一次展开的搜索点进行下一步搜索
DFS和BFS在展开子结点时均属于盲目型搜索，也就是说，它不会选择哪个结点在下一次搜索中更优而去跳转到该结点进行下一步的搜索
一个经过仔细设计的启发函数，往往在很快的时间内就可得到一个搜索问题的最优解
关键就是如何设计这个启发函数

A*搜寻算法，俗称A星算法，作为启发式搜索算法中的一种，这是一种在图形平面上，有多个节点的路径，求出最低通过成本的算法
常用于游戏中的NPC的移动计算，或线上游戏的BOT的移动计算上
A*算法最为核心的部分，就在于它的一个估值函数的设计上：
        f(n)=g(n)+h(n)
f(n)是每个可能试探点的估值，它有两部分组成
g(n)，它表示从起始搜索点到当前点的代价（通常用某结点在搜索树中的深度来表示）
h(n)，它表示启发式搜索中最为重要的一部分，即当前结点到目标结点的估值
h(n)设计的好坏，直接影响着具有此种启发式函数的启发式算法的是否能称为A*算法

具有f(n)=g(n)+h(n)策略的启发式算法能成为A*算法的充分条件是
  搜索树上存在着从起始点到终了点的最优路径。
  问题域是有限的。
  所有结点的子结点的搜索代价值>0。
  h(n)=<h*(n) （h*(n)为实际问题的代价值）
  当此四个条件都满足时，一个具有f(n)=g(n)+h(n)策略的启发式算法能成为A*算法，并一定能找到最优解
一个好的h(n)的评价是：h(n)在h*(n)的下界之下，并且尽量接近h*(n)
A*算法最为核心的过程，就在每次选择下一个当前搜索点时，是从所有已探知的但未搜索过点中(可能是不同层，亦可不在同一条支路上)，选取f值最小的结点进行展开
A*算法与广度、深度优先和Dijkstra 算法的联系就在于：当g(n)=0时，该算法类似于DFS，当h(n)=0时，该算法类似于BFS

A* (使用曼哈顿距离)
A* (采用欧氏距离)
A* (利用切比雪夫距离)
Bi-Directional Breadth-First-Search(双向广度优先搜索)
A*算法与广度、深度优先和Dijkstra 算法的联系就在于：当g(n)=0时，该算法类似于DFS，当h(n)=0时，该算法类似于BFS
*******************************************/
//A*搜索算法需要在進一步看看，有3中方式曼哈顿距离 && 欧氏距离 && 切比雪夫距离
void ASearch(int (*node)[SIZE], NODE Open, NODE Close){
    int PointFlag[SIZE] = {0};
    int Openindex = 0, Closeindex = 0, index = 0;
    int MinNo = 0, MinValue = MAX, Recordindex = 0;
    Open[Openindex].nodeNo = 0;
    Open[Openindex++].nodeValue = node[0][0];
    while(1){
        //Choose Minimize and Fill Close
        index = 0;
        MinNo = Open[index].nodeNo;
        MinValue = Open[index++].nodeValue;
        Recordindex = index;
        while(index < Openindex){
            if(Open[index].nodeValue < MinValue){
                MinValue = Open[index].nodeValue;
                MinNo = Open[index].nodeNo;
                Recordindex = index + 1;
            }
            index++;
        }
        //避免重复
        if(1 != PointFlag[MinNo]){
            Close[Closeindex].nodeNo = MinNo;
            Close[Closeindex++].nodeValue = MinValue;
            PointFlag[MinNo] = 1;
        }
        if(5 == MinNo)
            break;
        if(Recordindex < Openindex){
            Open[Recordindex - 1].nodeNo = Open[Openindex - 1].nodeNo;
            Open[Recordindex - 1].nodeValue = Open[Openindex - 1].nodeValue;
        }
        Openindex--;
        //Fill Open
        index = 0;
        while(index < 6){
            if((MAX != node[MinNo][index]) && 0 != node[MinNo][index]){
                Open[Openindex].nodeNo = index;
                Open[Openindex].nodeValue = MinValue + node[MinNo][index];
                Openindex++;
            }
            index++;
        }
    }
    index = 0;
    while(index < Closeindex){
        printf("V0->V%d:%02d\n", Close[index].nodeNo, Close[index].nodeValue);
        index++;
    }
}

void main(){
    int MyNode[SIZE][SIZE] = {{0, MAX, 10, MAX, 30, 100}, {MAX, 0, 5, MAX, MAX, MAX}, {MAX, MAX, 0, 50, MAX, MAX}, {MAX, MAX, MAX, 0, MAX, 10}, {MAX, MAX, MAX, 20, 0, 60}, {MAX, MAX, MAX, MAX, MAX, 0}};
    NODE Open = malloc(sizeof(NODEINFO) * SIZE);
    NODE Close = malloc(sizeof(NODEINFO) * SIZE);
    memset(Open, 0, sizeof(NODEINFO) * SIZE);
    memset(Close, 0, sizeof(NODEINFO) * SIZE);
    ASearch(MyNode, Open, Close);
}
