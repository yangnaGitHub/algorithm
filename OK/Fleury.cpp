#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <stack>
#include <queue>

using namespace std;

/***********************************
欧拉通路 (欧拉迹)—通过图中每条边一次且仅一次，并且过每一顶点的通路
欧拉回路 (欧拉闭迹)—通过图中每条边一次且仅一次，并且过每一顶点的回路
欧拉回路的图。欧拉图就是从一顶出发每条边恰通过一次又能回到出发顶点的那种图，即不重复的行遍所有的边再回到出发点
通路和回路－称vie1e2…envj为一条从 vi到 vj且长度为n的通路，其中长度是指通路中边的条数．称起点和终点相同的通路为一条回路
简单图－不含平行边和自回路的图
混合图－既有有向边，也有无向边的图
平凡图－仅有一个结点的图
完全图－有n个结点的且每对结点都有边相连的无向简单图，称为无向完全图；有n个结点的且每对结点之间都有两条方向相反的边相连的有向简单图为有向完全图
无向图:
  G有欧拉通路的充分必要条件为：G 连通，G中只有两个奇度顶点(它们分别是欧拉通路的两个端点)
  G有欧拉回路(G为欧拉图)：G连通，G中均为偶度顶点
有向图:
  D有欧拉通路：D连通，除两个顶点外，其余顶点的入度均等于出度，这两个特殊的顶点中，一个顶点的入度比出度大1，另一个顶点的入度比出度小1
凡是由偶点组成的连通图，一定可以一笔画成。画时可以把任一偶点为起点，最后一定能以这个点为终点画完此图
凡是只有两个奇点的连通图（其余都为偶点），一定可以一笔画成。画时必须把一个奇点为起点，另一个奇点终点
D有欧拉回路(D为欧拉图)：D连通，D中所有顶点的入度等于出度。一个有向图是欧拉图，当且仅当该图所有顶点度数都是0  汉密尔顿图与欧拉图的区别只在于，边与顶点的区别，欧拉图是每边经过一次，汉密尔顿图是每顶经过一次
************************************/
int ver = 0, edge = 0;
void InputM1(int G[10][10]){
    int posx = 0, posy = 0;
    cout << ver << edge;
    for(int vari = 0; vari < ver; vari++){
        for(int varj = 0; varj < ver; varj++)
            G[vari][varj] = 0;
    }
    for(int vari = 0; vari < edge; vari++){
        cout << posx << posy;
        G[posx - 1][posy - 1] = G[posy - 1][posx - 1] = 1;
    }
}

int BFSTest(int G[10][10]){
    int Array[10], varx = 0, key = 0;
    queue<int> myque;
    myque.push(0);
    for(int vari = 0; vari < ver; ++vari)
        Array[vari] = 0;
    Array[0] = 1;
    while(!myque.empty()){
        varx = myque.front();
        myque.pop();
        for(int vari = 0; vari < ver; ++vari){
            if(G[varx][vari] > 0){
                if(Array[vari] != 1){
                    Array[vari] = 1;
                    myque.push(vari);
                }
            }
        }
    }
    for(int vari = 0; vari < ver; ++vari){
        if(!Array[vari]){
            key = 1;
            break;
        }
    }
    if(key)
        return 0;
    else return 1;
}

void DFS(int G[10][10], stack<int> mystack, int xstart, int cur){
    int key = 0, mid = 0, next = 0;
    mystack.push(xstart);
    for(int vari = 0; vari < ver; ++vari){
        if(G[vari][xstart] > 0){
            key = 1;
            G[vari][xstart] = 0;
            G[xstart][vari] = 0;
            DFS(G, mystack, vari, 0);
            break;
        }
    }
    if(!key){
        mystack.pop();
        mid = mystack.top();
        G[xstart][mid] = 1;
        G[mid][xstart] = 1;
        next = xstart + 1;
        if(mystack.size() != edge){
            mystack.pop();
            DFS(G, mystack, mid, next);
        }else mystack.push(xstart);
    }
}

void Euler(int G[10][10], int xstart){
    int mid = 0;
    stack<int> mystack;
    DFS(G, mystack, xstart, 0);
    while(!mystack.empty()){
        mid = mystack.top();
        mystack.pop();
        cout << "->%d" << mid;
    }
}

int main(){
    int vari = 0, varj = 0, sum = 0, key = 0;
    int G[10][10];
    InputM1(G);
    if(!BFSTest(G)){
        cout << "NO" << endl;
        return 0;
    }
    for(vari = 0; vari < ver; vari++){
        sum = 0;
        for(varj = 0; varj < ver; varj++)
            sum += G[vari][varj];
        if(sum % 2){//G中均为偶度顶点
            key = 1;
            break;
        }
    }
    if(key)
        cout << "NO" << endl;
    else Euler(G, 0);
    return 0;
}
