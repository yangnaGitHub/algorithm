#include <stdio.h>
#include <dos.h>
#include <stdlib.h>

//调整最大堆和创建最大堆，接着着两个操作引进了堆排序，最后介绍了采用堆实现优先级队列
void MultiHeapSort(int *Array, int ArraySize, int MaxTag){
	int StartTag = MaxTag;
	int EndTag = (MaxTag + ArraySize) / 2 - 1;
	int LeftRightMax = 0, Left = 0, Right = 0, Self = 0, MaxFlag = 0;
	if((ArraySize - MaxTag) < 2)
		return ;
	while(EndTag >= StartTag){
		Self = Array[EndTag];
		Left = 0;Right = 0;
		if((2 * EndTag + 2 - MaxTag) < ArraySize){
			Left = Array[2 * EndTag + 1 - MaxTag];
			Right = Array[2 * EndTag + 2 - MaxTag];
		}else{
			if((2 * EndTag + 1 - MaxTag) < ArraySize)
				Left = Array[2 * EndTag + 1 - MaxTag];
		}
		//printf("%d %d %d %d\n", EndTag, Self, Left, Right);
		if(Left < Right){
			LeftRightMax = Right;
			MaxFlag = 2;
		}else{
			LeftRightMax = Left;
			MaxFlag = 1;
		}
		if(LeftRightMax <= Self){
			LeftRightMax = Self;
			MaxFlag = 0;
		}
		if(1 == MaxFlag){
			Array[2 * EndTag + 1 - MaxTag] = Self;
			Array[EndTag] = LeftRightMax;
		}else if(2 == MaxFlag){
			Array[2 * EndTag + 2 - MaxTag] = Self;
			Array[EndTag] = LeftRightMax;
		}
		EndTag--;
	}
    /*EndTag = MaxTag;
	while(EndTag < ArraySize)
        printf("%d ", Array[EndTag++]);
    printf("\n");*/
}

void HeapSort(int *Array, int ArraySize){
	int MaxTag = 0;
	while(1){
		//KeepHeap
    	MultiHeapSort(Array, ArraySize, MaxTag);
		printf("%d ", Array[MaxTag]);
		MaxTag++;
		if(MaxTag == ArraySize)
			break;
	}
}

void main(){
	int Array[] = {5, 4, 8, 1, 3, 6, 9, 2, 7};
	HeapSort(Array, sizeof(Array) / sizeof(int));
}
