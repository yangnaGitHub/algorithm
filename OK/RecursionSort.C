#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>

void MySort(int *array, int size){
	int *SortTemp = NULL;
	int BaseNum = array[0], Upper = size, Lower = size;
	int index = 1;
	if(0 == size)
		return ;
	if(1 == size){
		printf("%d ", BaseNum);
		return ;
	}
	SortTemp = (int *)malloc(2 * size * sizeof(int));
	memset(SortTemp, 0, 2 * size * sizeof(int));
	SortTemp[size] = BaseNum;
	while(index < size){
		if(array[index] < BaseNum)
			SortTemp[--Lower] = array[index];
		else if(array[index] >= BaseNum)
			SortTemp[++Upper] = array[index];
		index++;
	}
	MySort((SortTemp + Lower), size - Lower);
	printf("%d ", BaseNum);
	MySort((SortTemp + size + 1), Upper - size);
	free(SortTemp);
}

void main()
{
	int sortArray[] = {4, 7, 2, 8, 5, 3, 9, 6, 1, 20, 15, 17, 19, 14, 11, 13};
	MySort(sortArray, sizeof(sortArray) / sizeof(int));
}