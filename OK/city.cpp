#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
vector<int> vec[100];
int pre[100];
#define INF 1<<28
#define SIZE 10
int cityRoad[10][10] = {{0, 1, INF, INF, INF, INF, INF, 1, 1, INF},
                        {1, 0, INF, INF, INF, INF, INF, INF, INF, INF},
                        {INF, INF, 0, INF, INF, INF, 1, INF, INF, 1},
                        {INF, INF, INF, 0, INF, INF, INF, INF, INF, 1},
                        {INF, INF, INF, INF, 0, INF, INF, INF, 1, INF},
                        {INF, INF, INF, INF, INF, 0, INF, 1, INF, INF},
                        {INF, INF, 1, INF, INF, INF, 0, INF, INF, INF},
                        {1, INF, INF, INF, INF, 1, INF, 0, INF, 1},
                        {1, INF, INF, INF, 1, INF, INF, INF, 0, INF},
                        {INF, INF, 1, 1, INF, INF, INF, 1, INF, 0},
                        };

void FindArrive(int xin, int yin){
    int ret = 0;
    for(int xindex = 0; xindex < 10; xindex++){
        if(xin == xindex)
            continue;
        if(cityRoad[yin][xindex] && (INF != cityRoad[yin][xindex])){
            if(INF == cityRoad[xin][xindex])
                cityRoad[xin][xindex] = yin;
            if(1 == cityRoad[yin][xindex])
                FindArrive(yin, xindex);
        }
    }
}

void city(){
    for(int xindex = 0; xindex < 10; xindex++){
        for(int yindex = 0; xindex != yindex, yindex < 10; yindex++){
            if(cityRoad[xindex][yindex] && (INF != cityRoad[xindex][yindex]))
                FindArrive(xindex, yindex);
        }
    }

    for(int xindex = 0; xindex < 10; xindex++){
        for(int yindex = 0; yindex < 10; yindex++)
            cout << cityRoad[xindex][yindex] << " ";
        cout << endl;
    }
}

void Dijkstra(){
    int Record[SIZE] = {0}, index = 0, Tag = 0, temp = 0, Value = 0;
    while(index < SIZE)
        Record[index] = cityRoad[0][index++];
    index = 1;
    while(index < SIZE){
        Tag = 1;
        while(Tag < SIZE){
            temp = cityRoad[index][Tag];
            if(0 != temp && INF != temp){
                Value = Record[index] + temp;
                if(Value < Record[Tag])
                    Record[Tag] = index;
            }
            Tag++;
        }
        index++;
    }
    Tag = 0;
    while(Tag < SIZE)
        printf("%d ", Record[Tag++]);
}

void DFS(int cur){
    for(int index = 0; index < vec[cur].size(); ++index){
        cout << cur << " " << index << " " << vec[cur][index] << " " << pre[vec[cur][index]];
        getchar();
        if(pre[vec[cur][index]]) continue;
        pre[vec[cur][index]] = cur;
        DFS(vec[cur][index]);
    }
}

int main(){
    int num = 0, cur = 0;
    memset(vec, 0, sizeof(vec));
    memset(pre, 0, sizeof(pre));
    cin >> num >> cur;
    pre[cur] = -1;
    for(int index = 0; index < num -1; ++index){
        int xnum = 0, ynum = 0;
        cin >> xnum >> ynum;
        vec[xnum].push_back(ynum);
        vec[ynum].push_back(xnum);
    }
    DFS(cur);
    for(int index = 1; index <= num; ++index)
        printf("%d ", pre[index]);
    return 0;
}
