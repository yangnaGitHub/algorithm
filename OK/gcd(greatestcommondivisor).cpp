#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
/*************************************
��С������ = ����֮�� / ���Լ��
���Լ�� * ��С������ = ����֮��
**************************************/

int gcd(int vara, int varb){
    return varb == 0 ? vara : gcd(b, a % b);
}
