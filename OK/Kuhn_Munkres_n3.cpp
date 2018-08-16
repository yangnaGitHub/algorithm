#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

const int SIZE = 5;
const int INF = 1 << 28;

class graph{
private:
    bool xckd[SIZE], yckd[SIZE];
    int counter, edge[SIZE][SIZE], xmate[SIZE], ymate[SIZE];
    int lx[SIZE], ly[SIZE], slack[SIZE], prev[SIZE];
    queue<int> Myqueue;
    bool bfs();
    void agument(int);
public:
    bool make();
    int KMMatch();
};

bool graph::make(){
    int house[SIZE], child[SIZE], hin, win, cn = 0;
    char line[SIZE];
    cin >> hin >> win;
    if(!win) return false;
    counter = 0;
    for(int index = 0; index < hin; index++){
        gets(line);
        for(int xindex = 0; line[xindex]; xindex++){
            if('H' == line[xindex]) house[counter++] = index * SIZE + xindex;
            if('m' == line[xindex]) child[cn++] = index * SIZE + xindex;
        }
    }

    for(int xindex = 0; xindex < counter; xindex++){
        int cr = child[xindex] / SIZE, cc = child[xindex] % SIZE;
        for(int yindex = 0; yindex < counter; yindex++){
            int hr = house[yindex] / SIZE, hc = house[yindex] % SIZE;
            edge[xindex][yindex] = -abs(cr - hr) - abs(cc - hc);
        }
    }
    return true;
}

bool graph::bfs(){
    while(!Myqueue.empty()){
        int ptemp = Myqueue.front(), utemp = ptemp >> 1;
        Myqueue.pop();
        if(ptemp & 1){
            if(-1  == ymate[utemp]){
                agument(utemp);
                return true;
            }else{
                xckd[ymate[utemp]] = true;
                Myqueue.push(ymate[utemp] << 1);
            }
        }else{
            for(int index = 0; index < SIZE; index++){
                if(yckd[index]) continue;
                else if(lx[utemp] + ly[index] != edge[utemp][index]){
                    int ex = lx[utemp] + ly[index] - edge[utemp][index];
                    if(slack[index] > ex){
                        slack[index] = ex;
                        prev[index] = utemp;
                    }
                }else{
                    yckd[index] = true;
                    prev[index] = utemp;
                    Myqueue.push((index << 1) | 1);
                }
            }
        }
    }
    return false;
}

void graph::agument(int index){
    while(index != -1){
        int pv = xmate[prev[index]];
        ymate[index] = prev[index];
        xmate[prev[index]] = index;
        index = pv;
    }
}

int graph::KMMatch(){
    for(int index = 0; index < counter; index++){
        lx[index] = -INF;
        for(int xindex = 0; xindex < counter; xindex++)
            (lx[index] >= edge[index][xindex]) ? lx[index]:edge[index][xindex];
    }
    memset(ly, 0, sizeof(ly));
    memset(xmate, -1, sizeof(xmate));
    memset(ymate, -1, sizeof(ymate));
    bool agu = true;
    for(int mn = 0; mn < counter; mn++){
        if(agu){
            memset(xckd, false, sizeof(xckd));
            memset(yckd, false, sizeof(yckd));
            for(int index = 0; index < counter; index++) slack[index] = INF;
            while(!Myqueue.empty()) Myqueue.pop();
            xckd[mn] = true;
            Myqueue.push(mn << 1);
        }
        if(bfs()){
            agu = true;
            continue;
        }
        int ex = INF;
        mn--;
        agu = false;
        for(int index = 0; index < counter; index++){
            if(!yckd[index])
                (ex <= slack[index]) ? ex : slack[index];
        }
        for(int index = 0; index < counter; index++){
            if(xckd[index]) lx[index] -= ex;
            if(yckd[index]) ly[index] += ex;
            slack[index] -= ex;
        }
        for(int index = 0; index < counter; index++){
            if(!yckd[index] && (0 == slack[index])){
                yckd[index] = true;
                Myqueue.push((index << 1) | 1);
            }
        }
        int cost = 0;
        for(int index = 0; index < counter; index++)
            cost += edge[index][xmate[index]];
        return cost;
    }
}

int main(){
    graph gop;
    while(gop.make()) printf("%d\n", -gop.KMMatch());
    return 0;
}
