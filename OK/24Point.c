#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int Calculate(char *str){
    int len = strlen(str);
    int index = 0, Ptag =0, Ctag = 0, Poptag = 0;
    char Calculate[4];
    char ptr[10];
    char temp[10];
    char ch;
    memset(Calculate, '\0', 4);
    memset(ptr, '\0', 10);
    while(index < len){
        ch = str[index++];
        if(('1' <= ch) && ('9' >= ch))
            ptr[Ptag++] = ch;
        if(('*' == ch) || ('/' == ch))
            Calculate[Ctag++] = ch;
        else if(('+' == ch) || ('-' == ch)){
            Poptag = Ctag - 1;
            while(0 <= Poptag){
                if(('+' == Calculate[Poptag]) || ('-' == Calculate[Poptag]))
                    break;
                else{
                    ptr[Ptag++] = Calculate[Poptag];
                    Ctag--;
                }
                Poptag--;
            }
            Calculate[Ctag++] = ch;
        }
    }
    index = Ctag - 1;
    while(0 <= index)
        ptr[Ptag++] = Calculate[index--];
    printf("%s\t", ptr);
    index = 0;
    Ptag = 0;
    while(index < len){
        ch = ptr[index];
        if(('+' != ch) && ('-' != ch) && ('*' != ch) && ('/' != ch))
            temp[Ptag] = ch;
        else{
            Ctag = temp[--Ptag] - '0';
            Poptag = temp[--Ptag]- '0';
            switch(ch){
            case '+':Poptag = Poptag + Ctag;break;
            case '-':Poptag = Poptag - Ctag;break;
            case '*':Poptag = Poptag * Ctag;break;
            case '/':Poptag = Poptag / Ctag;break;
                default:printf("Error\n");
            }
            temp[Ptag] = Poptag + '0';
        }
        Ptag++;
        index++;
    }
    printf("%d\n", temp[0] - '0');
    return 0;
}

void PointTo24(int first, int second, int third, int four){
    int xindex = 0, yindex = 0, zindex = 0;
    char calculate[5] = {'+', '-', '*', '/', '\0'};
    char expression[10];
    for(xindex = 0; xindex < 4; xindex++){
        memset(expression, '\0', 10);
        sprintf(expression, "%d", first);
        expression[strlen(expression)] = calculate[xindex];
        for(yindex = 0; yindex < 4; yindex++){
            memset(expression + 2, '\0', 8);
            sprintf(expression + strlen(expression), "%d", second);
            expression[strlen(expression)] = calculate[yindex];
            for(zindex = 0; zindex < 4; zindex++){
                memset(expression + 4, '\0', 6);
                sprintf(expression + strlen(expression), "%d", third);
                expression[strlen(expression)] = calculate[zindex];
                sprintf(expression + strlen(expression), "%d", four);
                printf("%s\t", expression);
                if(24 == Calculate(expression))
                    printf("%s\n", expression);
            }
        }
    }
}

void main(){
    int num1, num2, num3, num4;
    printf("Enter The Four Number > ");
    scanf("%d%d%d%d", &num1, &num2, &num3, &num4);
    PointTo24(num1, num2, num3, num4);
}
