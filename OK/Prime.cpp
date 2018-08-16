#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;
#define INF (1 << 28)

int tree[10][10], lowcost[10];
bool visit[10];
int Sum = 0;
/**********************************************
带权图分为有向和无向,无向图的最短路径又叫做最小生成树(prime算法和kruskal算法)
有向图的最短路径算法有dijkstra算法和floyd算法
联通图G的一个子图如果是一棵包含G的所有顶点的树，则该子图称为G的生成树 生成树是联通图的极小连通子图
所谓极小是指：若在树中任意增加一条边，则 将出现一个回路；若去掉一条边，将会使之编程非连通图
生成树各边的权 值总和称为生成素的权。权最小的生成树称为最小生成树
最短路径问题旨在寻找图中两节点之间的最短路径，常用的算法有：floyd算法和dijkstra算法
构造最小生成树一般使用贪心策略，有prime算法和kruskal算法
************************************************/
void prime(int num){
    int temp = 0, key = 0;
    Sum = 0;
    visit[1] = 1;
    for(int index = 2; index <= num; ++index){
        lowcost[index] = tree[1][index];
    }
    for(int index = 2; index <= num; ++index){
        temp = INF;
        for(int other = 2; other <= num; ++other){
            if(!visit[other] && (temp > lowcost[other])){
                temp = lowcost[other];
                key = other;
            }
        }
        visit[key] = 1;
        Sum += temp;
        getchar();
        for(int other = 2; other <= num; ++other){
            if((lowcost[other] > tree[key][other]) && !visit[other])
                lowcost[other] = tree[key][other];
        }
    }
}

int main(){
    int num = 0, cost = 0, posx = 0, posy = 0, tmp = 0;
    memset(tree, 0, sizeof(tree));
    memset(lowcost, 0, sizeof(lowcost));
    memset(visit, 0, sizeof(visit));
    cin >> num >> cost;
    for(int index = 1; index <= cost; ++index){
        cin >> posx >> posy >> tmp;
        tree[posy][posx] = tree[posx][posy] = tmp;
    }
    int MinNum = INF, temp = 0;
    for(int index = 1; index <= num; ++index){
        cin >> temp;
        if(MinNum > temp)
            MinNum = temp;
    }
    prime(num);
    printf("Sum + MinNum = %d\n", Sum + MinNum);
    return 0;
}
