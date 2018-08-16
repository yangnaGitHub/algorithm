#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;
#define SIZE 10
int FMAX[SIZE][SIZE];
int visit[SIZE][SIZE];

void DFS(int varm, int varn){
    if(visit[varm][varn] || !FMAX[varm][varn]) return;
    else{
        visit[varm][varn] = 1;
        DFS(varm - 1, varn - 1);
        DFS(varm - 1, varn);
        DFS(varm - 1, varn + 1);

        DFS(varm, varn - 1);
        DFS(varm, varn + 1);

        DFS(varm + 1, varn - 1);
        DFS(varm + 1, varn);
        DFS(varm + 1, varn + 1);
    }
}

int main(){
    int counter = 0, num = 0;
    cin >> num;
    memset(FMAX, 0, sizeof(FMAX));
    memset(visit, 0, sizeof(visit));
    for(int vari = 1; vari <= num; ++vari){
        for(int varj = 1; varj <= num; ++varj)
            cin >> FMAX[vari][varj];
    }

    for(int vari = 1; vari <= num; ++vari){
        for(int varj = 1; varj <= num; ++varj){
            if(!visit[vari][varj] && FMAX[vari][varj]){
                counter++;
                DFS(vari, varj);
            }
        }
    }
    cout << counter << endl;
}
