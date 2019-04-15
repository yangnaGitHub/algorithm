#include<iostream>
#include<map>
#include<string>
#include<list>
#include<vector>
#include<algorithm>
#include<typeinfo.h>

using namespace std;

/*�������ݽṹ
  vector:��Ÿ����������͵�������̬����
  queue:����,�Ƚ��ȳ�
  stack:ջ,�Ƚ����
  set:����
  unordered_set:
  bitset:����λ�ļ���
  map:ӳ��
  unordered_map:
  priority_queue:���ȶ���,���ȷ��ʼ���ߵ�Ԫ��
  list:˫������
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
