#include <iostream>
#include <cstdio>

using namespace std;

int maxvalue[11][6];

void pre_deal(int counter){
    for(int yindex = 1; yindex < 20; yindex++){
        for(int xindex = 1; xindex < counter; xindex++){
            if((xindex + (1 << yindex) - 1) <= counter)
                maxvalue[xindex][yindex] = max(maxvalue[xindex][yindex - 1], maxvalue[xindex + (1 << (yindex - 1))][yindex - 1]);
        }
    }
}

void RMQ(){
    maxvalue[1][0] = 3;
    maxvalue[2][0] = 2;
    maxvalue[3][0] = 4;
    maxvalue[4][0] = 5;
    maxvalue[5][0] = 6;
    maxvalue[6][0] = 8;
    maxvalue[7][0] = 1;
    maxvalue[8][0] = 2;
    maxvalue[9][0] = 9;
    maxvalue[10][0] = 7;
    pre_deal(11);
    for(int xindex = 1; xindex < 11; xindex++){
        for(int yindex = 0; yindex < 6; yindex++)
            cout << maxvalue[xindex][yindex] << " ";
        cout << endl;
    }
}

int main(){
    RMQ();
    return 0;
}
