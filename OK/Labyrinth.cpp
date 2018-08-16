#include <iostream>
#include <cstdio>
#include <stdlib.h>

using namespace std;

/***********************************
迷宫地图
X:墙壁
S:小狗所处的位置
D:迷宫的门
.:空的方格

4 4 5
S.X.
..X.
..XD
....

3 4 5
S.X.
..X.
...D

给定你起点S，和终点D，问你是否能在 T 时刻恰好到达终点D

奇偶剪枝:起点到终点需要偶数步，如果计算步数不为偶数则是不可达的，可以被剪掉
************************************/
#define SIZE 9
char Mymap[SIZE][SIZE];
int Nnum = 0, Mnum = 0, Tnum = 0, Si = 0, Sx = 0, Di = 0, Dx = 0, wall = 0;//(Si, Sx) begin + (Di, Dx) end
bool escape = false;

//int dir[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}}; //left right down up
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; //left right down up

void DFS(int before, int after, int counter){//深搜
    if(before > Nnum || after > Mnum || before <= 0 || after <= 0)//出界
        return ;
    if(before == Di && after == Dx && counter == Tnum){
        escape = 1;
        return ;
    }
    for(int xindex = 0; xindex < Nnum; xindex++){
        for(int yindex = 0; yindex < Mnum; yindex++)
            printf("%c ", Mymap[xindex + 1][yindex + 1]);
        printf("\n");
    }
    printf("\n");
    getchar();
    int temp = (Tnum - counter) - abs(before - Di) - abs(after - Dx);
    if(temp < 0 || temp & 1)
        return ;
    for(int index = 0; index < 4; ++index){
        if(Mymap[before + dir[index][0]][after + dir[index][1]] != 'X'){
            Mymap[before + dir[index][0]][after + dir[index][1]] = 'X';//走过的地方变为墙
            DFS(before + dir[index][0], after + dir[index][1], counter + 1);
            if(escape)
                return ;
            Mymap[before + dir[index][0]][after + dir[index][1]] = '.';//迷宫还原，以便下次广搜
        }
    }
    return ;
}

int main(){
    while(scanf("%d %d %d", &Nnum, &Mnum, &Tnum) && Nnum && Mnum && Tnum){
        wall = 0;
        for(int index = 1; index <= Nnum; ++index){
            for(int Xindex = 1; Xindex <= Mnum; ++Xindex){
                cin >> Mymap[index][Xindex];
                if('X' == Mymap[index][Xindex]) wall++;
                if('S' == Mymap[index][Xindex]){
                    Si = index;
                    Sx = Xindex;
                }
                if('D' == Mymap[index][Xindex]){
                    Di = index;
                    Dx = Xindex;
                }
            }
        }

        if(Nnum * Mnum - wall <= Tnum){//t是代表要走的步数，步数加墙数必须小于总格子数的，因为所有格子中还包括了S和D，这是剪枝
            printf("NO\n");
            continue;
        }else{
            escape = 0;
            Mymap[Si][Sx] = 'X';//出发点是不可能再走的了，变为墙
            DFS(Si, Sx, 0);
            if(escape) printf("YES\n");
            else printf("NO\n");
        }
    }
    return 0;
}
