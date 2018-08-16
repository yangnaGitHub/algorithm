#include <stdio.h>
#include <stdlib.h>

/**********************************************************************
快速排序采用的是分治算法思想
快速排序关键过程是对数组进行划分，划分过程需要选择一个主元素（pivot element）作为参照

***********************************************************************/
int TwoSideSort(int *Array, int ArraySize){
	int Base = Array[0], BaseTag = 0;
	int StartFlag = 0, EndTag = ArraySize - 1, Temp = 0;
	if(1 == ArraySize){
		printf("%d ", Array[0]);
		return 0;
	}
	while(EndTag >= 0){
        if(Array[EndTag] < Base){
            if(BaseTag < EndTag){
				Temp = Array[BaseTag];
				Array[BaseTag] = Array[EndTag];
				Array[EndTag] = Temp;
				BaseTag = EndTag;
				StartFlag = 1;
			}
		}
		else if(Array[EndTag] > Base){
            if(BaseTag > EndTag){
				Temp = Array[BaseTag];
				Array[BaseTag] = Array[EndTag];
				Array[EndTag] = Temp;
				BaseTag = EndTag;
				StartFlag = 1;
			}
		}
		EndTag--;
	}
	if(!StartFlag){
		printf("%d ", Array[0]);
		TwoSideSort(Array + 1, ArraySize - 1);
		return 0;
	}
	TwoSideSort(Array, BaseTag + 1);
	TwoSideSort(Array + BaseTag + 1, ArraySize - BaseTag - 1);
	return 0;
}

void FastSort(int *Array, int ArraySize){
	TwoSideSort(Array, ArraySize);
}

int main(){
	int Array[] = {24, 15, 27, 5, 43, 87, 34};
	FastSort(Array, sizeof(Array) / sizeof(int));
}
