#ifndef MYACSEARCH_H
#define MYACSEARCH_H
#include <iostream>
#include <stdio.h>
#include <queue>
#include <malloc.h>
#include <string.h>

using namespace std;

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef struct Trie{
    struct Trie* next[26];
    struct Trie* Parent;
    struct Trie* Fail;
    char word;
    bool LastWord;
    int order;
}TRIE, *TRIETREE;

class MyACSearch
{
    public:
        MyACSearch();
        void BuildTrieTree();
        void CreateFailLink();
        void ACSearch(char *str, uint32_t len);
        void DestoryTrieTree(TRIETREE &root);
        virtual ~MyACSearch();
    private:
        TRIETREE ROOT;
};
#endif // MYACSEARCH_H
