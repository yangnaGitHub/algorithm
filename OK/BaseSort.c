#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Link{
    int data;
    struct Link *next;
}LINKNODE, *LINK;
//基数排序的思想就是将待排数据中的每组关键字依次进行桶分配
//比如下面的待排序列：278、109、063、930、589、184、505、269、008、083
//我们将每个数值的个位，十位，百位分成三个关键字： 278 -> k1(个位)=8 ，k2(十位)=7 ，k3=(百位)=2
//然后从最低位个位开始(从最次关键字开始)，对所有数据的k1关键字进行桶分配(因为，每个数字都是 0-9的，因此桶大小为10)，再依次输出桶中的数据得到下面的序列。
//930、063、083、184、505、278、008、109、589、269
//再对上面的序列接着进行针对k2的桶分配，输出序列为：
//505、008、109、930、063、269、278、083、184、589
//最后针对k3的桶分配，输出序列为：
//008、063、083、109、184、269、278、505、589、930
//对比桶排序，基数排序每次需要的桶的数量并不多。而且基数排序几乎不需要任何“比较”操作，而桶排序在桶相对较少的情况下，桶内多个数据必须进行基于比较操作的排序。因此，在实际应用中，基数排序的应用范围更加广泛
//基数排序是借助“分配”和“收集”两种操作对单逻辑关键字进行排序的一种内部排序方法
//映射函数f(k)能够将N个数据平均的分配到M个桶中，这样每个桶就有[N/M]个数据量
//尽量的增大桶的数量。极限情况下每个桶只能得到一个数据，这样就完全避开了桶内数据的“比较”排序操作
void BaseSort(int *Array, int ArraySize){
    LINKNODE Bucket[10] = {0};
    LINK link = NULL;
    LINK plink = NULL;
    LINK AddNode = NULL;
    int KeyWord = 0, index = 0, BreakFlag = 0, BreakCount = 0, TenCount = -1, Temp = 0, Tag = 0;
    while(1){
        index = 0;
        BreakCount = 0;
        TenCount++;
        memset(Bucket, 0, 10 * sizeof(LINKNODE));
        while(index < ArraySize){
            Temp = Array[index];
            Tag = 0;
            while(Tag < TenCount){
                Temp /= 10;
                Tag++;
            }
            if(0 == Temp)
                BreakCount++;
            if(ArraySize == BreakCount)
                BreakFlag = 1;
            KeyWord = Temp % 10;
            if(0 == Bucket[KeyWord].data)
                Bucket[KeyWord].data = Array[index];
            else{
                link = &(Bucket[KeyWord]);
                while(NULL != link->next)
                    link = link->next;
                AddNode = (LINK)malloc(sizeof(LINKNODE));
                memset(AddNode, 0, sizeof(LINKNODE));
                AddNode->data = Array[index];
                link->next = AddNode;
            }
            index++;
        }
        if(BreakFlag)
            break;
        index = 0;
        Tag = 0;
        while(index < 10){
            if(0 == Bucket[index].data){
                index++;
                continue;
            }
            Array[Tag++] = Bucket[index].data;
            link = &(Bucket[index]);
            while(NULL != link->next){
                link = link->next;
                plink = link -> next;
                Array[Tag++] = link->data;
                free(link);
                if(NULL == plink)
                    break;
                link = plink;
                if(NULL == link->next){
                    Array[Tag++] = link->data;
                    free(link);
                    break;
                }
            }
            Bucket[index].data = 0;
            Bucket[index].next = NULL;
            index++;
        }
    }
    index = 0;
    while(index < ArraySize)
        printf("%d ", Array[index++]);
}

void main(){
    int *Array[] = {278, 109, 63, 920, 589, 184, 505, 269, 8, 83};
    BaseSort(Array, sizeof(Array) / sizeof(int));
}
