#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;
/***********************
��ʲ���ȣ�Bash Game��:
A��Bһ������ÿ����ÿ�����ٱ�һ��,��౨4������������,��˭�ȱ���30
��Ҫ������n, ÿ����౨��m��, ���ٱ���1��
n = k*(1+m)+r
n = 31; m = 4;
==>r = 1; k = 6

�������ȣ�Wythoff Game��:
�����ѻ���,ÿ�ο��Դ�ĳһ��ȡ����1������(������)�����ߴ�����ȡ��ͬ�Ļ����������ȡ�����ʤ����

��ķ���ȣ�Nimm Game����
�����ʯ�ӣ�ÿ��ʯ�Ӹ���Ҳ������ģ�˫����������ȡ��ʯ��
  ÿһ��Ӧȡ������һöʯ�ӣ�ÿһ��ֻ�ܴ�ĳһ����ȡ�߲��ֻ�ȫ��ʯ��
  ���˭ȡ�����һöʯ�Ӿ�ʤ
************************/
int main(){
    /*int num = 0; limit = 0;
    cin >> num >> limit;
    if(num % (limit + 1))
        cout << "WIN" << endl;
    else cout << "LOSE" << endl;*/

    /*int vari = 0, varj = 0, tmp = 0;
    cin >> vari >> varj;
    if(vari > varj)
        swap(vari, varj);
    tmp = floor((varj - vari) * (1 + sqrt(5.0)) / 2.0);//�ƽ�ָ� floor����ȡ��
    if(tmp == vari) cout << "LOSE" << endl;
    else cout << "WIN" << endl;*/

    int index = 0, num = 0, minnum = 0;
    int temp[20];
    while(cin >> num){
        for(index = 0; index < num; index++)
            cin >> temp[index];
        minnum = temp[0];
        for(index = 1; index < num; index++)
            minnum = minnum ^ temp[index];
        if(minnum) cout << "WIN" << endl;
        else cout << "LOSE" << endl;
    }
}
