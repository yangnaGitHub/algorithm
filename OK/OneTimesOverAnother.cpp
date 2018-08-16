#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define SIZE 100
int pre[SIZE];//父节点
bool flag[SIZE];//顶点的奇偶性（很巧妙）

//查找根结点+路径压缩
int findpre(int root){
    return (root == pre[root]) ? root : findpre(pre[root]);
}

//合并
void join(int root1, int root2){
    int xres = findpre(root1);
    int yres = findpre(root2);
    if(xres != yres)
        pre[xres] = yres;
}

int main(){
    int ver = 0, edge = 0, start = 0, pend = 0;
    int sum_root = 0, sum_vcount = 0;//根结点的个数，记录奇度顶点个数
    cin >> ver >> edge;
    for(int index = 1; index <= ver; ++index)//初始化
        pre[index] = index;
    memset(flag, false, sizeof(flag));
    sum_root = 0;
    sum_vcount = 0;
    for(int index = 1; index <= edge; ++index){
        cin >> start >> pend;
        join(start, pend);
        flag[start] = !flag[start];//只记录奇偶性，1为奇度，0为偶度
        flag[pend] = !flag[pend];
    }

    for(int index = 1; index <= ver; ++index){
        if(pre[index] == index) sum_root++;//根结点个数
        if(flag[index]) sum_vcount++;//奇度顶点个数
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
