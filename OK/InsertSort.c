#include <stdio.h>
#include <stdlib.h>

void insertsort(int *Array, int Size){
    int xindex = 0, yindex = 0, zindex = 0, arraytemp = 0, moveindex = 0;
    int *temp = malloc(sizeof(int) * Size);
    if(NULL == temp){
        printf("malloc error\n");
        return ;
    }
    while(xindex < Size){
        arraytemp = Array[xindex++];
        if(0 == yindex)
            temp[yindex++] = arraytemp;
        else{
            zindex = yindex - 1;
            while(0 <= zindex){
                if(arraytemp > temp[zindex])
                    break;
                zindex--;
            }
            zindex = zindex + 1;
            moveindex = yindex;
            while(zindex < moveindex){
                temp[moveindex] = temp[moveindex - 1];
                moveindex--;
            }
            temp[zindex] = arraytemp;
            yindex++;
        }
    }
    xindex = 0;
    while(xindex < yindex)
        printf("%d ", temp[xindex++]);
    free(temp);
    if(NULL != temp)
        temp = NULL;
}

void main(){
    int Array[10] = {5, 8, 7, 3, 1, 2, 4, 6, 9, 0};
    insertsort(Array, 10);
}
