#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;
/*******************************************
f(1) = 0;
f(i) = (f(i - 1) + m) % i; (i > 1)
i = 8 ==> f(8) = (f(7) + m) % i;Ҫ�ߵõ�7���� + ��m = Ҫ�ߵĵ�8����

********************************************/

int main(){
    int num = 0, varm = 0, ans = 0;
    cin >> num >> varm;
    for(int index = 2; index <= num; index++){
        cout << ans << " " << varm << " " << index << endl;
        getchar();
        ans = (ans + varm) % index;
    }
    cout << ans + 1;
}
