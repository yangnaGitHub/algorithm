#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
/*************************************
最小公倍数 = 两数之积 / 最大公约数
最大公约数 * 最小公倍数 = 两数之积
**************************************/

int gcd(int vara, int varb){
    return varb == 0 ? vara : gcd(b, a % b);
}
