#include "MyACSearch.h"

int main()
{
    char str[] = "sdmfhsgnshejfgnihaofhsrnihao";
    TRIETREE root = NULL;
    MyACSearch ACSearch;
    ACSearch.BuildTrieTree();
    ACSearch.CreateFailLink();
    ACSearch.ACSearch(str, strlen(str));
    ACSearch.DestoryTrieTree(root);
    return 0;
}
