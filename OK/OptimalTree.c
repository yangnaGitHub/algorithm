#include <stdio.h>
#include <stdlib.h>

#define MAX 999999.99999
/***********************************************************************
查找的关键字是有一定的概率的，就是说有的关键字可能经常被搜索，而有的很少被搜索，而且搜索的关键字可能不存在
比如中文输入法字库中各词条（单字、词组等）的先验概率，针对用户习惯可以自动调整词频——所谓动态调频、高频先现原则

description:一个由n个互异的关键字组成的有序序列K={k1<k2<k3<,……,<kn}和它们被查询的概率P={p1,p2,p3,……,pn}，要求构造一棵二叉查找树T，使得查询所有元素的总的代价最小
对于一个搜索树，当搜索的元素在树内时，表示搜索成功。当不在树内时，表示搜索失败。
用一个“虚叶子节点”来标示搜索失败的情况，因此需要n+1个虚叶子节点{d0<d1<……<dn}，对于应di的概率序列是Q={q0,q1,……,qn}
d0表示搜索元素小于k1的失败结果，dn表示搜索元素大于kn的失败情况。di（0<i<n）表示搜索节点在ki和k(i+1)之间时的失败情况
pi的和 + qi的和 = 1
樹種的搜索代價：（（ki的深度 + 1）的和）*概率 + （（di的深度 + 1）的和）*概率
一棵最优二叉查找树不一定是一棵整体高度最小的树，也不一定总是把最大概率的关键字放在根部

求解過程：一棵最优二叉查找树T有一棵包含关键字ki，……，kj的子树T'，那么这棵子树T’对于对于关键字ki，……kj和虚拟键di-1，……，dj的子问题也必定是最优的
***********************************************************************/
void MyOptimalTree(float *pTree, float *qTree, int Size, float (*eTree)[Size + 2], int (*root)[Size + 1]){
    int xindex = 0, yindex = 0, kindex = 0, Tag = 0;
    float Allp = 0, Temp = 0;
    for(xindex = 1; xindex <= Size + 1; xindex++)
        eTree[xindex][xindex - 1] = qTree[xindex - 1];
    for(xindex = 1; xindex <= Size; xindex++){
        for(yindex = xindex; yindex <= Size; yindex++){
            eTree[xindex][yindex] = MAX;
            Tag = xindex;
            Allp = qTree[xindex - 1];
            while(Tag <= yindex){
                Allp += pTree[Tag];
                Allp += qTree[Tag++];
            }
            printf("%d %d %f\n", xindex, yindex, Allp);
            for(kindex = xindex; kindex <= yindex; kindex++){
                 Temp = eTree[xindex][kindex - 1] + eTree[kindex + 1][yindex] + Allp;
                 if(Temp < eTree[xindex][yindex]){
                    eTree[xindex][yindex] = Temp;
                    root[xindex][yindex] = kindex;
                 }
            }
        }
    }
    for(xindex = 1; xindex <= Size + 1; xindex++){
        for(yindex = xindex - 1; yindex <= Size; yindex++)
            printf("%f ", eTree[xindex][yindex]);
        printf("\n");
    }
}

void OptimalTree(float *pTree, float *qTree, int Size, float (*eTree)[Size + 1], int (*root)[Size]){
    int xindex = 0, yindex = 0, kindex = 0, Tempindex = 0;
    float Temp = 0;
    float DJ[Size + 2][Size + 1];
    for(xindex = 1; xindex <= Size + 1; xindex++){
        eTree[xindex][xindex - 1] = qTree[xindex - 1];
        DJ[xindex][xindex - 1] = qTree[xindex - 1];
    }
    for(kindex = 1; kindex <= Size; kindex++){
        for(xindex = 1; xindex <= Size - kindex + 1; xindex++){
            yindex = xindex + kindex - 1;
            eTree[xindex][yindex] = MAX;
            DJ[xindex][yindex] = DJ[xindex][yindex - 1] + pTree[yindex] + qTree[yindex];
            for(Tempindex = xindex; Tempindex <= yindex; Tempindex++){
                Temp = eTree[xindex][Tempindex - 1] + eTree[Tempindex + 1][yindex] + DJ[xindex][yindex];
                if(Temp < eTree[xindex][yindex]){
                    eTree[xindex][yindex] = Temp;
                    root[xindex][yindex] = Tempindex;
                }
            }
        }
    }
}

void CreateOptimalTree(int parent, int start, int end, int (*root)[5]){
    int Kvalue = root[start][end];
    if(!parent)
        printf("Root is K%d\n", Kvalue);
    else if(parent && parent != start && parent != end){
        if(parent > start)
            printf("K%d :Left  K%d\n", parent, Kvalue);
        else if(parent < start)
            printf("K%d :Right K%d\n", parent, Kvalue);
    }
    if(start == end){
        printf("K%d :Left  V%d\n", start, start - 1);
        printf("K%d :Right V%d\n", start, start);
        return ;
    }
    if(parent == start){
        printf("K%d :Left  V%d\n", start, start - 1);
        return ;
    }
    if(parent == end){
        printf("K%d :Right V%d\n", end, end);
        return ;
    }
    CreateOptimalTree(Kvalue, start, Kvalue - 1, root);
    CreateOptimalTree(Kvalue, Kvalue + 1, end, root);
}

void main(){
    float pTree[] = {0, 0.15, 0.10, 0.05, 0.10, 0.20};
    float qTree[] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
    int SIZE = sizeof(pTree) / sizeof(float), Size = SIZE - 1;
    float eTree[SIZE + 1][SIZE];
    int root[SIZE][SIZE];
    OptimalTree(pTree, qTree, Size, eTree, root);
    CreateOptimalTree(0, 1, Size, root);
    printf("OptimalTree %f", eTree[1][Size]);
}
