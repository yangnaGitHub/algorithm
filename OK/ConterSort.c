#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>

//计数排序不是比较排序，排序的速度快于任何比较排序算法
//计数排序对于数据范围很大的数组，需要大量时间和内存
//计数排序是用来排序0到100之间的数字的最好的算法，但是它不适合按字母顺序排序人名
//计数排序可以用在基数排序中的算法来排序数据范围很大的数组
//对于每一个输入元素x，确定出小于x的元素个数。有了这一信息，就可以吧x直接放到它在最终输出数组中的位置上
/************************************************************
A: | 5 | 1 | 4 | 5 | 2 | 3 | 2 | ==> max = 5, min = 1;
B: | 1 | 2 | 1 | 1 | 2 | ==> record counter
C: | 1 | 2 | 2 | 3 | 4 | 5 | 5 |
*************************************************************/

int CounterSort(int *SortArray, int Size){
	int index = 0x0, Diff = 0x0, count = 0x0;
	int Max = SortArray[0], Min = SortArray[0];
	int *TempSize = NULL, *NewArray = NULL;
	while(index < Size){
		if(Max < SortArray[index])
			Max = SortArray[index];
		if(Min > SortArray[index])
			Min = SortArray[index];
		index++;
	}
	Diff = Max - Min + 1;
	TempSize = malloc(sizeof(int) * Diff);
	NewArray = malloc(sizeof(int) * Size);
	memset(NewArray, 0, sizeof(int) * Size);
	memset(TempSize, 0, sizeof(int) * Diff);
	index = 0x0;
	while(index < Size)
		TempSize[SortArray[index++] - Min]++;
	index = 0x0;
	while(index < Diff){
		NewArray[count] = index + Min;
		count += TempSize[index++];
	}
	index = 0x0;
	while(index < Diff){
		count = TempSize[index];
		if(0 == count)
			continue;
		while(count--)
			printf("%d ", Min + index);
		index++;
	}
	return 0;
}

void main(){
	int array[] = {5, 8, 3, 6, 2, 4, 9, 1, 7};
	CounterSort(array, sizeof(array) / sizeof(int));
}
