#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void ListAllArray(float *Array, int Size){
    int index = 0;
    float temp = 0;
    while(index < Size){
        temp = Array[index];
        if(0 > temp){
            if(-1 == temp)
                printf("+");
            else if(-2 == temp)
                printf("-");
            else if(-3 == temp)
                printf("*");
            else if(-4 == temp)
                printf("/");
            index++;
            continue;
        }
        printf("%1.0f", temp);
        index++;
    }
    printf("\t");
}

void Calculate24Point(float *Array, int Size){
    float Num[4] = {0};
    float Sign[3] = {0};
    float temp = 0, before = 0, after = 0, sign = 0;
    int index = 0, numindex = 0, signindex = 0, popindex = 0, calindex = 0, flag = 0;
    ListAllArray(Array, Size);
    while(index < Size){
        temp = Array[index];
        if((0 < temp) && (10 > temp)){
            if(flag){
                flag = 0;
                Num[numindex++] = 1 / temp;
            }
            else
                Num[numindex++] = temp;
        }
        else if((-3 == temp) || (-4 == temp)){
            if(-4 == temp){
                temp = -3;
                flag = 1;
            }
            Sign[signindex++] = temp;
        }
        else if((-1 == temp) || (-2 == temp)){
            popindex = signindex - 1;
            calindex = numindex - 1;
            while(0 <= popindex){
                sign = Sign[popindex];
                after = Num[calindex];
                before = Num[calindex - 1];
                if(-3 == sign)
                    before = before * after;
                else if(-4 == sign)
                    before = before / after;
                Num[calindex] = 0;
                Num[--calindex] = before;
                Sign[popindex] = 0;
                numindex--;
                signindex--;
                popindex--;
            }
            Sign[signindex++] = temp;
        }
        index++;
    }
    //ListAllArray(Num, numindex);
    //ListAllArray(Sign, signindex);
    popindex = signindex - 1;
    calindex = numindex - 1;
    while(0 <= popindex){
        sign = Sign[popindex];
        after = Num[calindex];
        before = Num[calindex - 1];
        if(-1 == sign)
            before = before + after;
        else if(-2 == sign)
            before = before - after;
        else if(-3 == sign)
            before = before * after;
        else if(-4 == sign)
            before = before / after;
        Num[calindex] = 0;
        Num[--calindex] = before;
        Sign[popindex] = 0;
        numindex--;
        signindex--;
        popindex--;
    }
    printf("%4.1f\n", Num[0]);
}

void PointTo24(float first, float second, float third, float four){
    //+(-1) -(-2) *(-3) /(-4)
    float Array[10] = {0};
    float Calcu[4] = {-1, -2, -3, -4};
    int xindex = 0, yindex = 0, zindex = 0;
    int globaltag = 0;
    memset(Array, 0, 10 * sizeof(float));
    Array[0] = first;
    Array[2] = second;
    Array[4] = third;
    Array[6] = four;
    for(xindex = 0; xindex < 4; xindex++){
        Array[1] = Calcu[xindex];
        for(yindex = 0; yindex < 4; yindex++){
            Array[3] = Calcu[yindex];
            for(zindex = 0; zindex < 4; zindex++){
                Array[5] = Calcu[zindex];
                Calculate24Point(Array, 7);
            }
        }
    }
}

void main(){
    float first, second, third, four;
    printf("Enter The Four Number > ");
    scanf("%f%f%f%f", &first, &second, &third, &four);
    PointTo24(first, second, third, four);
}
