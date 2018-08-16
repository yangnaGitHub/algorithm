#include <stdio.h>
#include <dos.h>
#include <stdlib.h>

/**************************************************************************************************************
#include <iostream>
#include <string>
#include <cstdlib>

队列是一种满足先进先出（FIFO）的数据结构，数据从队列头部取出，新的数据从队列尾部插入，数据之间是平等的，不存在优先级的
优先级队列可以理解为在队列的基础上给每个数据赋一个权值，代表数据的优先级
优先级队列用在操作系统中的多任务调度，任务优先级越高，任务优先执行
优先级队列有两种：最大优先级队列和最小优先级队列，这两种类别分别可以用最大堆和最小堆实现
一个最大优先级队列支持的操作如下操作：
INSERT(S,x)：把元素x插入到集合S
MAXIMUM(S)：返回S中具有最大关键字的元素
EXTRACT_MAX(S)：去掉并返回S中的具有最大关键字的元素
INCREASE_KEY(S,x,k)：将元素x的关键字的值增加到k，这里k值不能小于x的原关键字的值。

using namespce std;

const static int QUEUESIZE = 100;

class Event{
public:
	Event():EventName(""), EventPriority(-1){};
	Event(const string &name, const int pro):EventName(name), EventPriority(pro){};
	Event(const Event &en):EventName(en.EventName), EventPriority(en.EventPriority){};

	~Event();
	int Get_Event_Priority()const{
		return EventPriority;
	}
	string Get_Event_Name()const{
		return EventName;
	}
	void Increase_Priority(const int AddValue){
		EventPriority = EventPriority + AddValue;
	}
	void Decrease_Priority(const int DesValue){
		EventPriority = EventPriority - DesValue;
	}
	void Show_Event()const{
		cout << "EventName is: (" << EventName <<") + EventPriority is: " << EventPriority << endl;
	}
private:
	string EventName;
	int EventPriority;
};

class PriorityQueue{
public:
	PriorityQueue();
	void Adjust_Event(int index);
	Event Get_Event()const;
	void Insert_Event(const Event &en);
	void Increase_Priority(int pos, int pro);
	Event Delete_Event(int pos);
	void Show_Events()const;

	~PriorityQueue();
private:
	Event *events;
	int length;
};

PriorityQueue::PriorityQueue(){
	events = new Event[QUEUESIZE];
	length = 0;
}
PriorityQueue::~PriorityQueue(){
	if(!events)
		delete [] events;
	length = 0;
}

void PriorityQueue::Adjust_Event(int index){
	int left, right, largest;
	Event temp;
    while(1)
    {
        left = index*2;
        right = index*2+1;
		if(left <= length &&
			events[left].get_event_priority() > events[index].get_event_priority())
			largest = left;
		else
			largest = index;
		if(right <= length &&
			events[right].get_event_priority() > events[largest].get_event_priority())
 			largest = right;
		if(largest != index)
		{
 			temp = events[index];
			events[index] = events[largest];
			events[largest] = temp;
			index = largest;
		}
		else
 			break;
	}
}
Event PriorityQueue::Get_Event()const{
	if(length != 0)
		return events[1];
	else return Event();
}
void PriorityQueue::Insert_Event(const Event &en){
	length++;
	events[length] = en;
	Increase_Priority(length, 0);
}
void PriorityQueue::Increase_Priority(int pos, int pro){
	int index = 0, parent = 0;
	Event temp;
	if(pos > length){
		cout << "ERROR(Increase_Priority)" << endl;
		return ;
	}
	events[pos].Increase_Priority(pro);
	index = pos;
	parent = index / 2;
	while(index > 1 && events[parent].Get_Event_Priority() < events[index].Get_Event_Priority()){
		temp = events[index];
		events[index] = events[parent];
		events[parent] = temp;
		index = parent;
		parent = index / 2;
	}
}
Event PriorityQueue::Delete_Event(int pos){
	Event reten;
	if(pos > length){
		cout << "ERROR(Delete_Event)" << endl;
		return reten;
	}
	reten = events[pos];
	events[pos] = events[length];
	length--;
	Adjust_Event(pos);
	return reten;
}
void PriorityQueue::Show_Events()const{
	if(!length)
		cout << "Not Have Any Events In Queue" << endl;
	else{
		cout << "There Are " << length << " Events In Queue" << endl;
		for(int index = 1; index < length; index++)
			events[index].Show_Event();
	}
}
****************************************************************************************************************/
void OtherStackSort(int *Array, int ArraySize, int End){
	int EndTag = End / 2 - 1;
	int LeftRightMax = 0, Left = 0, Right = 0, Self = 0, MaxFlag = 0;
	if(End < 2)
		return ;
	while(EndTag >= 0){
		Self = Array[EndTag];
		Left = 0;
		Right = 0;
		if((2 * EndTag + 2) < End){
			Left = Array[2 * EndTag + 1];
			Right = Array[2 * EndTag + 2];

		}else{
			if((2 * EndTag + 1) < End)
				Left = Array[2 * EndTag + 1];
		}
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
			Array[2 * EndTag + 1] = Self;
			Array[EndTag] = LeftRightMax;
		}else if(2 == MaxFlag){
			Array[2 * EndTag + 2] = Self;
			Array[EndTag] = LeftRightMax;
		}
		EndTag--;
	}
}

void PriorityQueue(int *Array, int ArraySize){
	int MaxTag = ArraySize;
	while(1){
		//KeepStack
    	OtherStackSort(Array, ArraySize, MaxTag);
		printf("%d ", Array[0]);
		Array[0] = Array[MaxTag - 1];
		MaxTag--;
		if(!MaxTag)
			break;
	}
}

int main(){
	int Array[] = {5, 4, 8, 1, 3, 6, 9, 2, 7};
	PriorityQueue(Array, sizeof(Array) / sizeof(int));
	return 0;
}
