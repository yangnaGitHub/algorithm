#pragma once
#include <iostream>

using namespace std;
class ACSearch{
public:
    void *next[26];
    void *parent;
    void *fail;
    char inputchar;
    int patterTag;
    int patterNo;
    ACSearch();
    ~ACSearch();
    static ACSearch* buildingTree();
    static void buildingFailPath(ACSearch *root);
    static void searchAC (ACSearch *root, char *str, int len);
    static void destoryTree(ACSearch *root);
};
