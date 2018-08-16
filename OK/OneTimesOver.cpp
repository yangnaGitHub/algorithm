#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

int pre[100];

int unionsearch(int root){
    int son = 0, temp = 0;
    son = root;
    while(root != pre[root])
        root = pre[root];
    while(son != root){
        temp = pre[son];
        pre[son] = root;
        son = temp;
    }
    return root;
}

int unionsearchrec(int root){
    return (pre[root] == root) ? root : unionsearchrec(pre[root]);
}

void join(int root1, int root2){
    int xres = unionsearchrec(root1), yres = unionsearchrec(root2);
    cout << root1 << " " << xres << " " << root2 << " " << yres;
    getchar();
    //int xres = unionsearch(root1), yres = unionsearch(root2);
    if(xres != yres)
        pre[xres] = yres;
}

int main(){
    int flag = 1, ver = 0, edge = 0;
    memset(pre, 0, sizeof(pre));
    vector<int> res[100];
    cin >> ver >> edge;
    for(int index = 1; index <= ver; ++index)
        pre[index] = index;
    int start = 0, pend = 0;
    for(int index = 0; index < edge; ++index){
        cin >> start >> pend;
        res[start].push_back(pend);
        res[pend].push_back(start);
        join(start, pend);
        //join(unionsearch(start), unionsearch(pend));
    }
    for(int index = 2; index <= ver; ++index){//判断是否为连通图
        if(unionsearch(1) != unionsearch(index)){
            flag = 0;
            break;
        }
    }
    if(!flag)
        cout << "NO" << endl;
    else{//连通图
        int counter = 0;
        for(int index = 1; index <= 90; ++index){
            if(res[index].size() & 1)//奇度顶点个数
                counter++;
        }
        if((0 == counter) || (2 == counter))//奇度顶点为0或者2可以一笔画
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}
