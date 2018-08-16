#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define SIZE 5
/***********************************
通過給每一個頂點一個標號（頂標）把求最大權匹配的問題轉化為求完備匹配的問題
頂點Xi的頂標是A[i],頂點Yi的頂標是B[i],頂點Xi和Yj之間的邊權為w[i,j]
由二分图中所有满足A[i]+B[j]=w[i,j]的边(i,j)构成的子图（称做相等子图（概念很重要））有完备匹配，那么这个完备匹配就是二分图的最大权匹配。
问题就是求d值了。为了使A[i]+B[j]>=w[i,j]始终成立，且至少有一条边进入相等子图，d应该等于min{A[i]+B[j]-w[i,j]|Xi在交错树中，Yi不在交错树中}。
Tutte定理：一个图G有完备匹配，其充要条件是，对于图中任意点集U，去掉U后剩下的具有奇数个顶点的连通分量个数（记作o(G-U)）不超过U中的顶点数
  ==>(A:5 U:2 5-U:3) 5-U中的连通分量（具有奇数个顶点）的个数 <= U(完备分配) （连通分量：一条线可以把点连起来）
***********************************/
const int INF = 0x7fffffff;

bool mymap[SIZE][SIZE];// 二分图的相等子图, map[i][j] = true 代表Xi与Yj有边
bool xckd[SIZE], yckd[SIZE];// 标记在一次DFS中，Xi与Yi是否在交错树上
int match[SIZE]; // 保存匹配信息，其中i为Y中的顶点标号，match[i]为X中顶点标号

bool DFS(int ps, const int counter){
    for(int index = 0; index < counter; index++)
        printf("%d ", yckd[index]);
    printf("\n");
    getchar();
    for(int index = 0; index < counter; index++){
        if(!yckd[index] && mymap[ps][index]){
            printf("PS = %d %d %d %d\n", yckd[index], ps, index, mymap[ps][index]);
            getchar();
            yckd[index] = true;
            int temp = match[index];
            match[index] = ps;
            if(-1 == temp || DFS(temp, counter))
                return true;
            match[index] = temp;
            if(-1 == temp) xckd[temp] = true;
        }
    }
    return false;
}

void KM_Perfect_Match(const int counter, const int edge[][SIZE]){
    int lx[SIZE], ly[SIZE];

    for(int xindex = 0; xindex < counter; xindex++){
        for(int yindex = 0; yindex < counter; yindex++)
            printf("%d ", edge[xindex][yindex]);
        printf("\n");
    }
    getchar();
    for(int xindex = 0; xindex < counter; xindex++){
        lx[xindex] = -INF;
        ly[xindex] = 0;
        for(int yindex = 0; yindex < counter; yindex++){
            lx[xindex] = max(lx[xindex], edge[xindex][yindex]);
        }
        printf("%d ", lx[xindex]);
    }
    printf("\n");
    getchar();
    bool perfect = false;
    while(!perfect){
        //初始化邻接矩阵
        for(int xindex = 0; xindex < counter; xindex++){
            for(int yindex = 0; yindex < counter; yindex++){
                if(lx[xindex] + ly[yindex] == edge[xindex][yindex]) mymap[xindex][yindex] = true;
                else mymap[xindex][yindex] = false;
                printf("%d ", mymap[xindex][yindex]);
            }
            printf("\n");
        }
        getchar();
        //匹配过程
        int live = 0;
        memset(match, -1, sizeof(match));
        for(int index = 0; index < counter; index++){
            memset(xckd, false, sizeof(xckd));
            memset(yckd, false, sizeof(yckd));
            if(DFS(index, counter)) live++;
            else{
                printf("xckd[index] = %d\n", xckd[index]);
                xckd[index] = true;
                break;
            }
        }
        if(live == counter) perfect = true;
        else{
            //修改标号过程
            int ex = INF;
            for(int xindex = 0; xindex < counter; xindex++){
                for(int yindex = 0; xckd[xindex] && yindex < counter; yindex++){
                    if(!yckd[yindex]){
                        ex = min(ex, lx[xindex] + ly[yindex] - edge[xindex][yindex]);
                        printf("ex = %d %d\n", yindex, ex);
                    }
                }
            }
            getchar();
            for(int index = 0; index < counter; index++){
                if(xckd[index]) lx[index] -= ex;
                if(yckd[index]) ly[index] += ex;
                printf("MOD = %d %d %d\n", index, lx[index], ly[index]);
            }
            getchar();
        }
    }
}

int main(){
    int counter = 0, edge[SIZE][SIZE] = {{3, 5, 5, 4, 1}, {2, 2, 0, 2, 2}, {2, 4, 4, 1, 0}, {0, 1, 1, 0, 0}, {1, 2, 1, 3, 3}};

    /***************************************************
    *       在此处要做的工作 :
    *       读取二分图每两点间边的权并保存在edge[][]中,
    * 若X与Y数目不等，应添加配合的顶点
    *       保存二分图中X与Y的顶点数n,若上一步不等应保
    * 存添加顶点完毕后的n
    ***************************************************/
    counter = SIZE;

    KM_Perfect_Match(counter, edge);
    int cost = 0; //cost为最大匹配的总和, match[]中保存匹配信息
    for(int index = 0; index < counter; index++){
        printf("Y%d==>X%d\n", index + 1, match[index] + 1);
        cost += edge[match[index]][index];
    }

    printf("cost = %d\n", cost);
    return 0;
}
