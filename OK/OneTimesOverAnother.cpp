#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define SIZE 100
int pre[SIZE];//���ڵ�
bool flag[SIZE];//�������ż�ԣ������

//���Ҹ����+·��ѹ��
int findpre(int root){
    return (root == pre[root]) ? root : findpre(pre[root]);
}

//�ϲ�
void join(int root1, int root2){
    int xres = findpre(root1);
    int yres = findpre(root2);
    if(xres != yres)
        pre[xres] = yres;
}

int main(){
    int ver = 0, edge = 0, start = 0, pend = 0;
    int sum_root = 0, sum_vcount = 0;//�����ĸ�������¼��ȶ������
    cin >> ver >> edge;
    for(int index = 1; index <= ver; ++index)//��ʼ��
        pre[index] = index;
    memset(flag, false, sizeof(flag));
    sum_root = 0;
    sum_vcount = 0;
    for(int index = 1; index <= edge; ++index){
        cin >> start >> pend;
        join(start, pend);
        flag[start] = !flag[start];//ֻ��¼��ż�ԣ�1Ϊ��ȣ�0Ϊż��
        flag[pend] = !flag[pend];
    }

    for(int index = 1; index <= ver; ++index){
        if(pre[index] == index) sum_root++;//��������
        if(flag[index]) sum_vcount++;//��ȶ������
    }
    if(sum_root > 1)
        cout << "NO" << endl;
    else{
        if((sum_vcount == 0) || (2 == sum_vcount))
            cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
