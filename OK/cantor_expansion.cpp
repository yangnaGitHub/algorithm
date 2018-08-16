#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
/**************************************
����չ��
����X ==> X=a[n]*(n-1)!+a[n-1]*(n-2)!+...+a[i]*(i-1)!+...+a[2]*1!+a[1]*0!
DBAC ==> (3 * 3!) + (1 * 2!) + (0 * 1!) + (0 * 0!) = 20
��DС�ĺ�����3��,��BС�ĺ�����1��,��AС�ĺ�����0��,��CС�ĺ�����0��

ͨ��������չ������ȫ����
ʹ��շת����ķ����õ� ai
*********************************************/
int GetKeyValue(char *str, int key){
    int ret = 0, counter = 0;
    while(ret < 12){
        if(str[ret]){
            ret++;
            continue;
        }
        if(counter == key)
            break;
        if(str[ret] == '\0')
            counter++;
        ret++;
    }
    if(str[ret] == '\0')
        str[ret] = 'a';
    return ret;
}

int Recursive(int index){
    if(1 == index)
        return 1;
    return index * Recursive(index - 1);
}

int main(){
    int num = 302715242, index = 11, div = Recursive(index);
    int key = 0, other = 0, temp = 0;
    char str[13] = "\0";
    char flag[13] = "\0";
    while(index){
        key = num / div;
        other = num % div;

        temp = GetKeyValue(flag, key);
        str[11 - index] = temp + 'a';

        div = div / index;
        num = other;
        index--;
    }
    index = 0;
    while(index < 12){
        if(flag[index] == '\0')
            break;
        index++;
    }
    str[11] = index + 'a';
    cout << str << endl;
}
