#include "MyACSearch.h"
#define PATTERN_ROW 4
#define PATTERN_COL 30
char pattern[PATTERN_ROW][PATTERN_COL] = {"nihao", "hao", "hs", "hsr"};

void InitTriePointer(TRIETREE &Pointer){
    uint8_t index = 0;
    Pointer = (TRIETREE)malloc(sizeof(TRIE));
    Pointer->Fail = NULL;
    Pointer->Parent = NULL;
    Pointer->order = 0;
    Pointer->LastWord = 0;
    Pointer->word = 0;
    while(index < 26)
        Pointer->next[index++] = NULL;
}

MyACSearch::MyACSearch()
{
    InitTriePointer(ROOT);
}

MyACSearch::~MyACSearch()
{
    if(ROOT){
        free(ROOT);
        ROOT = NULL;
    }
}

void MyACSearch::BuildTrieTree(){
    uint32_t xindex = 0, yindex = 0;
    TRIETREE ptr = NULL, qtr = NULL;
    for(xindex = 0; xindex < PATTERN_ROW; xindex++){
        ptr = ROOT;
        for(yindex = 0; yindex < strlen(pattern[xindex]); yindex++){
            if(!(ptr->next[pattern[xindex][yindex] - 'a'])){
                InitTriePointer(qtr);
                qtr->Parent = ptr;
                qtr->word = pattern[xindex][yindex];
                ptr->next[pattern[xindex][yindex] - 'a'] = qtr;
                ptr = qtr;
            }else{
                ptr = ptr->next[pattern[xindex][yindex] - 'a'];
            }
        }
        ptr->LastWord = 1;
        ptr->order = xindex;
    }
}

void AddToQueue(TRIETREE ptr, queue<TRIETREE> &ACSearchQueue){
    uint8_t index = 0;
    while(index < 26){
        if(ptr->next[index]){
            ACSearchQueue.push(ptr->next[index]);
        }
        index++;
    }
}

void MyACSearch::CreateFailLink(){
    uint8_t index = 0, charWord = 0;
    queue<TRIETREE> ACSearchQueue;
    TRIETREE ptr = ROOT, qtr = NULL;
    ROOT->Fail = ROOT;
    while(index < 26){
        if(ptr->next[index]){
            AddToQueue(ptr->next[index], ACSearchQueue);
            (ptr->next[index])->Fail = ROOT;
        }
        index++;
    }

    while(!ACSearchQueue.empty()){
        ptr = ACSearchQueue.front();
        ACSearchQueue.pop();
        AddToQueue(ptr, ACSearchQueue);
        charWord = ptr->word;
        qtr = ptr->Parent;
        while(1){
            if((qtr->Fail)->next[charWord - 'a']){
                ptr->Fail = (qtr->Fail)->next[charWord - 'a'];
                break;
            }else{
                if(ROOT == qtr->Fail){
                    ptr->Fail = ROOT;
                    break;
                }else{
                    qtr = qtr->Fail->Parent;
                }
            }
        }
    }
}

void MyACSearch::ACSearch(char *str, uint32_t len){
    uint32_t index = 0;
    TRIETREE ptr = ROOT;
    while(index < len){
        if(ptr->next[str[index] - 'a']){
            ptr = ptr->next[str[index] - 'a'];
            if(ptr->LastWord)
                cout << index - strlen(pattern[ptr->order]) + 1 << '\t' << ptr->order << '\t' << pattern[ptr->order] << endl;
            index++;
        }else{
            if(ROOT == ptr) index++;
            else{
                ptr = ptr->Fail;
                if(ptr->LastWord)
                    cout << index - strlen(pattern[ptr->order]) << '\t' << ptr->order << '\t' << pattern[ptr->order] << endl;
            }
        }
    }
    while(ROOT != ptr){
        ptr = ptr->Fail;
        if(ptr->LastWord)
            cout << index - strlen(pattern[ptr->order]) << '\t' << ptr->order << '\t' << pattern[ptr->order] << endl;
    }
}

void MyACSearch::DestoryTrieTree(TRIETREE &root){
    uint8_t index = 0;
    TRIETREE ptr = root;
    if(!root)
        ptr = ROOT;
    while(index < 26){
        if(ptr->next[index])
            DestoryTrieTree(ptr->next[index]);
        index++;
    }
    if(root){
        free(root);
        root = NULL;
    }
}
