#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;
/***********************
巴什博奕（Bash Game）:
A和B一起报数，每个人每次最少报一个,最多报4个。轮流报数,看谁先报到30
需要报数到n, 每次最多报数m个, 最少报数1个
n = k*(1+m)+r
n = 31; m = 4;
==>r = 1; k = 6

威佐夫博奕（Wythoff Game）:
有两堆火柴棍,每次可以从某一堆取至少1根火柴棍(无上限)，或者从两堆取相同的火柴棍数。最后取完的是胜利者

尼姆博奕（Nimm Game）：
任意堆石子，每堆石子个数也是任意的，双方轮流从中取出石子
  每一步应取走至少一枚石子；每一步只能从某一堆中取走部分或全部石子
  如果谁取到最后一枚石子就胜
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
    tmp = floor((varj - vari) * (1 + sqrt(5.0)) / 2.0);//黄金分割 floor向下取整
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
