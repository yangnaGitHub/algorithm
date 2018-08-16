#include <iostream>
#include <string.h>
#include <queue>
#include "AcSearch.hpp"

using namespace std;
char pattern[4][30] = {"nihao", "hao", "hs", "hsr"};

ACSearch::ACSearch(){
    int index = 0;
    while(index < 26)
        this->next[index++] = NULL;
    this->fail = NULL;
    this->parent = NULL;
    this->patterTag = 0;
}

ACSearch::~ACSearch(){
}

ACSearch* ACSearch::buildingTree(){
    int Iindex = 0, Jindex = 0;
    ACSearch *root = new ACSearch();
    ACSearch *ptr = NULL, *qtr = NULL;
    for(Iindex = 0; Iindex < 4; Iindex++){
        ptr = root;
        for(Jindex = 0; Jindex < strlen(pattern[Iindex]); Jindex++){
            if(!(ptr->next[pattern[Iindex][Jindex] - 'a'])){
                qtr = new ACSearch();
                qtr->inputchar = pattern[Iindex][Jindex];
                qtr->parent = (void *)ptr;
                ptr->next[pattern[Iindex][Jindex] - 'a'] = (void *)qtr;
                ptr = qtr;
            }else
                ptr = (ACSearch *)ptr->next[pattern[Iindex][Jindex] - 'a'];
        }
        ptr->patterTag = 1;
        ptr->patterNo = Iindex;
    }
    return root;
}

void needtoqueue(ACSearch *root, queue<ACSearch *> &myqueue){
    int index = 0;
    for(index = 0; index < 26; index++){
        if(root->next[index])
            myqueue.push((ACSearch *)(root->next[index]));
    }
}

void ACSearch::buildingFailPath(ACSearch *root){
    int index = 0;
    char inputchar;
    queue<ACSearch *> myqueue;
    root->fail = (void *)root;
    for(index = 0; index < 26; index++){
        if(root->next[index]){
            needtoqueue((ACSearch *)(root->next[index]), myqueue);
            ((ACSearch *)(root->next[index]))->fail = (void *)root;
        }
    }

    ACSearch *ptr = NULL, *qtr = NULL;
    while(!myqueue.empty()){
        ptr = myqueue.front();
        myqueue.pop();
        needtoqueue(ptr, myqueue);
        inputchar = ptr->inputchar;
        qtr = (ACSearch *)(ptr->parent);
        while(1){
            if(((ACSearch *)(qtr->fail))->next[inputchar - 'a']){
                ptr->fail = ((ACSearch *)(qtr->fail))->next[inputchar - 'a'];
                break;
            }else{
                if(root == qtr->fail){
                    ptr->fail = (void *)root;
                    break;
                }else qtr = (ACSearch *)((ACSearch *)(qtr->fail))->parent;
            }
        }
    }
}

void ACSearch::searchAC(ACSearch *root, char *str, int len){
    ACSearch *ptr = root;
    int index = 0;
    while(index < len){
        int pos = str[index] - 'a';
        if(ptr->next[pos]){
            ptr = (ACSearch *)(ptr->next[pos]);
            if(ptr->patterTag)
                cout << index - strlen(pattern[ptr->patterNo]) + 1 << '\t' << ptr->patterNo << '\t' << pattern[ptr->patterNo] << endl;
            index++;
        }else{
            if(root == ptr) index++;
            else{
                ptr = (ACSearch *)(ptr->fail);
                if(ptr->patterTag)
                    cout << index - strlen(pattern[ptr->patterNo]) << '\t' << ptr->patterNo << '\t' << pattern[ptr->patterNo] << endl;
            }
        }
    }
    while(root != ptr){
        ptr = (ACSearch *)(ptr->fail);
        if(ptr->patterTag)
            cout << index - strlen(pattern[ptr->patterNo]) << '\t' << ptr->patterNo << '\t' << pattern[ptr->patterNo] << endl;
    }
}

void ACSearch::destoryTree(ACSearch *root){
    if(!root)
        return ;
    queue<ACSearch *> myqueue;
    ACSearch *ptr = NULL;
    myqueue.push(root);
    root = NULL;
    while(!myqueue.empty()){
        ptr = myqueue.front();
        myqueue.pop();
        for(int index = 0; index < 26; index++){
            if(ptr->next[index])
                myqueue.push((ACSearch *)(ptr->next[index]));
        }
        delete(ptr);
    }
}
