#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 3
/*******************************************
八数码的下一个格局中每个棋子移动到正确位置所需要的步数要少于当前格局中每个棋子移动到正确位置所需要的步数
*******************************************/
int EachCalculate(int Target, int Source, int flag){
    int step = 0;
    if((0 > Source) || (8 < Source))
        return 0;
    if(Target == Source)
        return 1;
    if(flag){
        step += EachCalculate(Target, Source - 1, 1);
        step += EachCalculate(Target, Source - 3, 1);
    }
    else{
        step += EachCalculate(Target, Source + 1, 0);
        step += EachCalculate(Target, Source + 3, 0);
    }
    //printf("%d\n", step);
    return step;
}

int CalculateStep(int Target, int Source){
    int step = 0;
    step += EachCalculate(Target, Source - 1, 1);
    //printf("here %d %d %d\n", Target, Source - 1, step);
    step += EachCalculate(Target, Source + 1, 0);
    //printf("%d %d %d\n", Target, Source + 1, step);
    step += EachCalculate(Target, Source - 3, 1);
    //printf("%d %d %d\n", Target, Source - 3, step);
    step += EachCalculate(Target, Source + 3, 0);
    //printf("%d %d %d\n", Target, Source + 3, step);
    printf("%d\n", step);
    return step;
}
int GainStep(int (*num)[SIZE]){
    int xindex = 0, yindex = 0, temp = 0, step = 0;
    int good[9] = {4, 0, 1, 2, 5, 8, 7, 6, 3};
    /*for(xindex = 0; xindex < SIZE; xindex++){
        for(yindex = 0; yindex < SIZE; yindex++){
            temp = num[xindex][yindex];
            if((xindex * SIZE + yindex) != good[temp])
                printf("%d %d\n", xindex * SIZE + yindex, good[temp]);
                step += CalculateStep(good[temp], xindex * SIZE + yindex);
        }
    }*/

    printf("%d\n", CalculateStep(3, 1));
    return step;
}

void EightPuzzle(int (*num)[SIZE]){
    int goodStep = GainStep(num);
    /*while(goodStep){
        //MovePoint()
    }*/
}

void main(){
    int num[][SIZE] = {{2, 8, 3}, {1, 6, 4}, {7, 0, 5}};
    EightPuzzle(num);
}
