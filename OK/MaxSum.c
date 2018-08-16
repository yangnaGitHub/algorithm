#include <stdio.h>
#include <stdlib.h>

int Max(int Mid, int left, int right){
    int Temp = left > right ? left : right;
    return Mid > Temp ? Mid : Temp;
}

int MaxSum(int *Array, int ArraySize){
    int Mid = ArraySize / 2, Index = Mid - 2;
    int LeftMax = Array[Mid - 1], RightMax = Array[Mid], Sum = LeftMax;
    if(0 == ArraySize)
        return 0;
    if(1 == ArraySize)
        return Array[0];
    while(Index >= 0){
        Sum += Array[Index--];
        LeftMax = LeftMax < Sum ? Sum : LeftMax;
    }
    Index = Mid + 1;
    Sum = RightMax;
    while(Index < ArraySize){
        Sum += Array[Index++];
        RightMax = RightMax < Sum ? Sum : RightMax;
    }
    return Max(LeftMax + RightMax, MaxSum(Array, Mid), MaxSum(Array + Mid, (ArraySize - Mid)));
}

int BestMaxSum(int *Array, int ArraySize){
    int MaxEnd = 0, MaxFar = 0;
    int index = 0;
    while(index < ArraySize){
        MaxEnd = (MaxEnd + Array[index]) > 0 ? (MaxEnd + Array[index]) : 0;
        MaxFar = MaxEnd > MaxFar ? MaxEnd : MaxFar;
        printf("%d %d\t", MaxEnd, MaxFar);
        index++;
    }
    return MaxFar;
}

void main(){
    int Array[] = {31, -41, 59, 26, -53, 58, 97, -93, -23, 84};
    printf("%d", BestMaxSum(Array, sizeof(Array) / sizeof(int)));
}
