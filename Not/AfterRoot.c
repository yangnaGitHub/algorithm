#include <stdio.h>
#include <dos.h>
#include <stdlib.h>


/******************************************************************
樹的廣度遍歷可以放到數組中直接輸出，也可以用隊列
         1
      2     3
    4   5 6   7   ==>   Array:1 2 3 4 5 6 7 8 9
  8   9
樹的先根+中根+后根遍歷的非遞歸方法是用棧
         9
      5     8
    3   4 6   7   ==>   Array:9 5 8 3 4 6 7 1 2
  1   2
*******************************************************************/

