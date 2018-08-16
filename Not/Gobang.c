#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int GetPosition(int size, char (*matrix)[size], int xposition, int yposition, int UpToDown, int LeftToRight, char Unverify){
    int xindex = 0, yindex = 0;
    int PointSum = 1;
    char ch = '\0';
    //UpToDown(1 0) && LeftToRight(0 1) && UpLeftToDownRight(1 1) && UpRightToDownLeft(0 0)
    xindex = xposition;
    yindex = yposition;
    while(1){
        if(1 == LeftToRight){
            --yindex;
            if(0 > yindex)
                break;
        }
        if(1 == UpToDown){
            --xindex;
            if(0 > xindex)
                break;
        }
        if((0 == UpToDown) && (0 == LeftToRight)){
            --xindex;
            ++yindex;
            if(0 > xindex || size <= yindex)
                break;
        }
        ch = matrix[xindex][yindex];
        if(Unverify == ch){
            PointSum += (1 << 4);
            break;
        }
        if('\0' == ch)
            break;
        PointSum++;
    }//up && Left
    xindex = xposition;
    yindex = yposition;
    while(1){
        if(1 == LeftToRight){
            ++yindex;
            if(size <= yindex)
                break;
        }
        if(1 == UpToDown){
            ++xindex;
            if(size <= xindex)
                break;
        }
        if((0 == UpToDown) && (0 == LeftToRight)){
            ++xindex;
            --yindex;
            if(0 > yindex || size <= xindex)
                break;
        }
        ch = matrix[xindex][yindex];
        if(Unverify == ch){
            PointSum += (1 << 3);
            break;
        }
        if('\0' == ch)
            break;
        PointSum++;
    }//Down && Right
    return PointSum;
}

int Veritf(int size, char (*matrix)[size], int xposition, int yposition, char Unverify){
    int PointSum = 0, status = 0;
    PointSum = GetPosition(size, matrix, xposition, yposition, 1, 0, Unverify);
    printf("%d ", PointSum);
    if(5 == (PointSum & 0x7))
        status = 1;
    PointSum = GetPosition(size, matrix, xposition, yposition, 0, 1, Unverify);
    printf("%d ", PointSum);
    if(5 == (PointSum & 0x7))
        status = 1;
    PointSum = GetPosition(size, matrix, xposition, yposition, 1, 1, Unverify);
    printf("%d ", PointSum);
    if(5 == (PointSum & 0x7))
        status = 1;
    PointSum = GetPosition(size, matrix, xposition, yposition, 0, 0, Unverify);
    printf("%d\n", PointSum);
    if(5 == (PointSum & 0x7))
        status = 1;
    return status;
}

void MachineOperation(int size, char (*matrix)[size], int xposition, int yposition, int *Mxposition, int *Myposition){
    int UpToDown = 0, LeftToRight = 0, UpLeftToDownRight = 0, UpRightToDownLeft = 0, middle = (size / 2) - 1;
    int MUpToDown = 0, MLeftToRight = 0, MUpLeftToDownRight = 0, MUpRightToDownLeft = 0, index = 0, min = size * size / 4, tag = 0, zone = 0;
    int NUM[4] = {0};
    memset(NUM, 0, 4 * sizeof(int));
    if(0 == xposition || 0 == yposition){
        //隨機生成兩個在0到7的點
        *Mxposition = 3;
        *Myposition = 3;
        return ;
    }
    xposition = xposition - 1;
    yposition = yposition - 1;
    UpToDown = GetPosition(size, matrix, xposition, yposition, 1, 0, '@');
    LeftToRight = GetPosition(size, matrix, xposition, yposition, 0, 1, '@');
    UpLeftToDownRight = GetPosition(size, matrix, xposition, yposition, 1, 1, '@');
    UpRightToDownLeft = GetPosition(size, matrix, xposition, yposition, 0, 0, '@');
    if((1 == UpToDown) && (1 == LeftToRight) && (1 == UpLeftToDownRight) && (1 == UpRightToDownLeft)){//first bang
        if((-1 != *Mxposition) && (-1 != *Myposition)){
            MUpToDown = GetPosition(size, matrix, *Mxposition, *Myposition, 1, 0, '#');
            MLeftToRight = GetPosition(size, matrix, *Mxposition, *Myposition, 0, 1, '#');
            MUpLeftToDownRight = GetPosition(size, matrix, *Mxposition, *Myposition, 1, 1, '#');
            MUpRightToDownLeft = GetPosition(size, matrix, *Mxposition, *Myposition, 0, 0, '#');
            if((1 == MUpToDown) && (1 == MLeftToRight) && (1 == MUpLeftToDownRight) && (1 == MUpRightToDownLeft)){
                //評價動作，哪個區最優化，然後排除已經佔有的地方
                NUM[0] = GainNum(0, middle, 0, middle, '#');
                NUM[1] = GainNum(middle, size, 0, middle, '#');
                NUM[2] = GainNum(0, middle, middle, size, '#');
                NUM[3] = GainNum(middle, size, middle, size, '#');
                if(middle >= *Mxposition){
                    if(middle >= *Myposition)
                        zone = 0;
                    else zone = 1;
                }else{
                    if(middle >= *Myposition)
                        zone = 2;
                    else zone = 3;
                }
                index = 0;
                while(1){
                    if(min > NUM[index % 4]){
                        min = NUM[index % 4];
                        tag = index;
                    }
                    index++;
                    if(16 == index){
                        printf("Algorithm Error\n");
                        return ;
                    }
                    if(0 == index % 4){
                        index = 0;
                        NUM[tag] = size * size / 4;
                        if(zone == tag){

                        }else{
                        }
                    }
                }
            }else MyFunc(MUpToDown, MLeftToRight, MUpLeftToDownRight, MUpRightToDownLeft, 0);
        }
        else{
            if(middle >= xposition)
                *Mxposition = xposition + 1;
            else *Mxposition = xposition - 1;
            if(middle >= yposition)
                *Myposition = yposition + 1;
            else *Myposition = yposition - 1;
        }
    }else MyFunc(UpToDown, LeftToRight, UpLeftToDownRight, UpRightToDownLeft, 1);
}

void ListAllMatrix(int size, char (*matrix)[size]){
    int xindex = 0, yindex = 0;
    char temp = 0;
    for(xindex = 0; xindex < size; xindex++){
        printf("|");
        for(yindex = 0; yindex < size; yindex++){
            temp = matrix[xindex][yindex];
            if(0 == temp)
                printf(" |");
            else printf("%c|", temp);
        }
        printf("\n");
    }
}

void FillBang(int size, char (*matrix)[size]){
    char person = '\0';
    int firstflag = 0, xposition = 0, yposition = 0, Mxposition = -1, Myposition = -1;
    printf("Enter First Person(I M) > ");
    scanf("%c", &person);
    if('I' == person)
        firstflag = 0;
    else if('M' == person)
        firstflag = 1;
    else{
        printf("Who First? I Don`t Know\n");
        return ;
    }
    printf("Notice: Your Simple Is #, My Simple Is @\nLet`s Start!!!!!!!!\n");
    ListAllMatrix(size, matrix);
    while(1){
        if(firstflag){
            MachineOperation(size, matrix, xposition, yposition, &Mxposition, &Myposition);
            matrix[Mxposition][Myposition] = '@';
            ListAllMatrix(size, matrix);
            if(Veritf(size, matrix, Mxposition, Myposition, '#'))
                break;
            firstflag = 0;
        }
        printf("Enter Your Bang Position > ");
        scanf("%d%d", &xposition, &yposition);
        if((0 < xposition) && (9 > xposition) && (0 < yposition) && (9 > yposition))
            if('\0' == matrix[xposition - 1][yposition - 1])
                matrix[xposition - 1][yposition - 1] = '#';
            else{
                printf("Your Position Error\n");
                return ;
            }
        else{
            printf("Your Position Error\n");
            return ;
        }
        //ListAllMatrix(size, matrix);
        if(Veritf(size, matrix, xposition - 1, yposition - 1, '@'))
            break;
        firstflag = 1;
    }
}

void main(){
    char matrix[8][8] = {"\0"};
    memset(matrix, '\0', 8 * 8 * sizeof(char));
    FillBang(8, matrix);
}
