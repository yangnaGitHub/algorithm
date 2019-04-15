#include<iostream>
#include<map>
#include<string>
#include<list>
#include<vector>
#include<algorithm>
#include<typeinfo.h>

using namespace std;

/*各种数据结构
  vector:存放各种数据类型的容器动态数组
  queue:队列,先进先出
  stack:栈,先进后出
  set:集合
  unordered_set:
  bitset:比特位的集合
  map:映射
  unordered_map:
  priority_queue:优先队列,优先访问级别高的元素
  list:双向链表
*/

template<class T>
class print_class{
public:
	void print_singal(T temp, string sep);
	void print_pair(T temp, string mid_sep, string sep);
};

template<class T>
void print_class<T>::print_singal(T temp, string sep){
	for(T::iterator iter = temp.begin(); iter != temp.end(); iter++)
		cout << *iter << sep;
	cout << endl;
}

template<class T>
void print_class<T>::print_pair(T temp, string mid_sep, string sep){
	for(T::iterator iter = temp.begin(); iter != temp.end(); iter++)
		cout << iter->first << mid_sep << iter->second << sep;
	cout << endl;
}

template<class T>
class generator{
private:
	unsigned int index;
	vector<T> obj;
public:
	generator(vector<T> init_obj):obj(init_obj){
		index = 0;
	};
	T get_next();
	bool is_end(){
		if(obj.size() <= index)
			return true;
		return false;
	};
};

template<class T>
T generator<T>::get_next(){
	if(is_end()){
		T temp;
		return temp;
	}
	index += 1;
	return obj[index - 1];
}
