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
��Ȩͼ��Ϊ���������,����ͼ�����·���ֽ�����С������(prime�㷨��kruskal�㷨)
����ͼ�����·���㷨��dijkstra�㷨��floyd�㷨
��ͨͼG��һ����ͼ�����һ�ð���G�����ж�������������ͼ��ΪG�������� ����������ͨͼ�ļ�С��ͨ��ͼ
��ν��С��ָ������������������һ���ߣ��� ������һ����·����ȥ��һ���ߣ�����ʹ֮��̷���ͨͼ
���������ߵ�Ȩ ֵ�ܺͳ�Ϊ�����ص�Ȩ��Ȩ��С����������Ϊ��С������
���·������ּ��Ѱ��ͼ�����ڵ�֮������·�������õ��㷨�У�floyd�㷨��dijkstra�㷨
������С������һ��ʹ��̰�Ĳ��ԣ���prime�㷨��kruskal�㷨
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
