#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <iterator>

using namespace std;

/*************************************************************************
请给出一个时间为O(nlgk)、用来将k个已排序链表合并为一个排序链表的算法
用一个最小堆来做k路合并
思路1：创建一个大小为k的数组，将k个链表中的第一个元素依次存放到数组中，然后将数组调整为最小堆，这样保证数组的第一个元素是最小的，假设为min，将min从最小堆取出并存放到最终结果的链表中，此时将min所在链表的下一个元素到插入的最小堆中，继续上面的操作，直到堆中没有元素为止。
思路2：將所有的元素放在一個為n的數組中然後堆排序
http://www.cnblogs.com/Anker/archive/2013/01/24/2874569.html
const的對象不能使用非const成員函數
**************************************************************************/
template <class T> class MinHeap{
public:
    MinHeap();
    MinHeap(const size_t size);
    ~MinHeap();
    T get_min() const;//函數後面加const,代表在此函數中不能修改成員數據成員(heap && heap_size)
    void delete_min();
    void insert_element(const T& data);
    void adjust_min_heap(const size_t index);
    size_t get_heap_size() const;
    int compare(const T& data1, const T& data2);
private:
    T *heap;
    size_t heap_size;
};

template <class T>
MinHeap<T>::MinHeap():heap(NULL), heap_size(0){}

template <class T>
MinHeap<T>::MinHeap(const size_t size){
    if(!heap)
        delete[] heap;
    heap  = new T[size + 1];
    heap_size = 0;
}

template <class T>
MinHeap<T>::~MinHeap(){
    if(!heap)
        delete[] heap;
    heap_size = 0;
}

template <class T>
T MinHeap<T>::get_min() const{
    if(heap_size > 0)
        return heap[1];
    else return T();
}

template <class T>
void MinHeap<T>::delete_min(){
    if(heap_size > 0){
        heap[1] = heap[heap_size];
        heap_size = heap_size - 1;
        adjust_min_heap(1);
    }else{
        cout << "The Min Heap Is Empty" << endl;
    }
}

template <class T>
void MinHeap<T>::insert_element(const T& data){
    size_t index = 0, parent = 0;
    T temp;
    heap_size++;
    heap[heap_size] = data;
    index = heap_size;
    parent = index / 2;
    while(index > 1 && compare(heap[parent], heap[index]) > 0){
        temp = heap[parent];//a = a + b; b = a - b; a = a - b;
        heap[parent] = heap[index];
        heap[index] = temp;
        index = parent;
        parent = index / 2;
    }
}

template <class T>
void MinHeap<T>::adjust_min_heap(const size_t index){
    size_t left = 0, right = 0, least = 0;
    T temp;
    left = index * 2;
    right = left + 1;
    if(left <= heap_size && compare(heap[left], heap[index]) < 0)
        least = left;
    else least = index;
    if(right <= heap_size && compare(heap[right], heap[least]) < 0)
        least = right;

    if(least != index){
        temp = heap[least];
        heap[least] = heap[index];
        heap[index] = temp;
        adjust_min_heap(least);
    }
}

template <class T>
size_t MinHeap<T>::get_heap_size() const{
    return heap_size;
}

template <class T>
int MinHeap<T>::compare(const T& data1, const T& data2){
    return (*data1 - *data2);
}

const static int SIZE = 3;

int main(){
    char index = 0, counter = 0;
    list<int> lists[SIZE];
    list<int>::iterator iters[SIZE];
    list<int> retlist;
    list<int>::iterator retiter;
    list<int>::iterator iter;
    MinHeap<list<int>::iterator> minheap(SIZE);
    int DATA[SIZE][4] = {{12, 24, 52, -1}, {9, 32, -1, -1}, {34, 42, 78, -1}};//每一组都是有序的下面的算法才是OK的

    while(index < SIZE){
        counter = 0;
        while(1){
            if(-1 == DATA[index][counter])
                break;
            lists[index].push_back(DATA[index][counter]);
            cout << DATA[index][counter] << "->";
            counter++;
        }
        cout << "NULL" << endl;
        index++;
    }

    index = 0;
    while(index < SIZE){
        iters[index] = lists[index].begin();
        minheap.insert_element(iters[index]);
        index++;
    }

    while(minheap.get_heap_size()){
        iter = minheap.get_min();
        retlist.push_back(*iter);
        minheap.delete_min();
        ++iter;
        if(iter != lists[0].end() && iter != lists[1].end() && iter != lists[2].end())
            minheap.insert_element(iter);
    }

    cout << "Merge List: " << endl;
    for(retiter = retlist.begin(); retiter != retlist.end(); retiter++)
        cout << *retiter << "->";
    cout << "NULL" << endl;
    exit(0);
}


