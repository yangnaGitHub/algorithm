#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	int data;
	struct Node *LChild;
	struct Node *RChild;
}NODEINFO, *NODE;

void ListChildNode(NODE ChildParent){
	if(NULL == ChildParent)
		return ;
	ListChildNode(ChildParent->LChild);
	printf("%d ", ChildParent->data);
	ListChildNode(ChildParent->RChild);
}

void ListAllNode(NODE Root, int BaseNodeCount){
	int index = 0x0;
	ListChildNode(Root->LChild);
	while(index < BaseNodeCount){
		printf("%d ", Root->data);
		index++;
	}
	ListChildNode(Root->RChild);
}

void AddNode(NODE Root, int AddItem, char Tag){
	NODE Add = (NODE)malloc(sizeof(NODEINFO));
	NODE TempNode = NULL;
	memset(Add, 0, sizeof(NODEINFO));
	if('L' == Tag){
		TempNode = Root->LChild;
		if(NULL != TempNode){
			if(AddItem > TempNode->data)
				AddNode(TempNode, AddItem, 'R');
			else if(AddItem < TempNode->data)
				AddNode(TempNode, AddItem, 'L');
		}
		else{
			Add->data = AddItem;
			Add->LChild = NULL;
			Add->RChild = NULL;
			Root->LChild = Add;
			return ;
		}
	}
	else if('R' == Tag){
		TempNode = Root->RChild;
		if(NULL != TempNode){
			if(AddItem > TempNode->data)
				AddNode(TempNode, AddItem, 'R');
			else if(AddItem < TempNode->data)
				AddNode(TempNode, AddItem, 'L');
		}
		else{
			Add->data = AddItem;
			Add->LChild = NULL;
			Add->RChild = NULL;
			Root->RChild = Add;
			return ;
		}
	}
}

void StackSort(int *array, int size){
	NODEINFO BaseNode;
	int index = 0x1, BaseNodeCount = 0x1;
	BaseNode.data = array[0];
	BaseNode.LChild = NULL;
	BaseNode.RChild = NULL;
	while(index < size){
		if(array[index] < array[0])
			AddNode(&BaseNode, array[index], 'L');
		else if(array[index] > array[0])
			AddNode(&BaseNode, array[index], 'R');
		else BaseNodeCount++;
		index++;
	}
	ListAllNode(&BaseNode, BaseNodeCount);
}

void main(){
	int SortArray[] = {4, 5, 2, 3, 9, 6, 1, 8, 7};
	StackSort(SortArray, sizeof(SortArray) / sizeof(int));
}