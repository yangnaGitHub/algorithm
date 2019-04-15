#include "common.h"

template<class T>
class Allsort{
private:
	vector<T> results;
	T result;
	char method;
	print_class<T> print_obj;
public:
	Allsort();
	Allsort(char ch):method(ch){};
	void allsort(T temp, unsigned int len);
	generator<T> get_results(){
		generator<T> gen_vec(results);
		return gen_vec;
	};
	void print_results(){
		generator<T> gen_vec = get_results();
		print_class<T> print_obj;
		while(!gen_vec.is_end())
			print_obj.print_singal(gen_vec.get_next(), " ");
	};
};

//排列组合
//数字的话还可以用减的方式,比如说4321-1234之间的数字,对于过大的无能为力
//重复怎么处理
template<class T>
void Allsort<T>::allsort(T temp, unsigned int len){
	if(0 == len){
		//组合添加
		/*print_class<list<int>> print_obj;
		print_obj.print_singal(result, " # ");*/
		if('A' == method){
			vector<T>::iterator iter = find(results.begin(), results.end(), result);
			if(results.end() == iter){
				results.push_back(result);
			}
		}else if('C' == method){
			T temp_res(result);
			temp_res.sort();
			//sort(temp_res.begin(), temp_res.end());//这边要注意==>string的排序
			vector<T>::iterator iter = find(results.begin(), results.end(), temp_res);
			if(results.end() == iter){
				results.push_back(temp_res);
			}
		}
		return ;
	}

	T next(temp);
	for(T::iterator iter = temp.begin(); iter != temp.end(); iter++){
		for(T::iterator new_iter = next.begin(); new_iter != next.end(); new_iter++){
			if(*new_iter == *iter){
				next.erase(new_iter);//重复
				break;
			}
		}

		/*print_class<list<int>> print_obj;
		print_obj.print_singal(next, " ");*/

		result.push_back(*iter);
		allsort(next, len - 1);
		result.pop_back();
		next.push_back(*iter);
	}
}

#if 0
//#define TYPE_1 1
//#define TYPE_2 1
#ifdef TYPE_1
void get_input(string& user, string& mother, unsigned int& len){
	cout<<"username:";
	cin>>user;
	cout<<"mothername:";
	cin>>mother;
	cout<<"length:";
	cin>>len;
}

void get_map(string& str, map<char, int>& str_map){
	char key_char = '\0';
	map<char, int>::iterator iter;
	for(unsigned int index = 0; index < str.size(); index++){
		key_char = str.at(index) | 0x20;
		iter = str_map.find(key_char);
		if(iter != str_map.end()){
			iter->second += 1;
		}else{
			str_map.insert(pair<char, int>(key_char, 1));
		}
	}
}

list<char> get_same_list(string& user, string& mother){
	map<char, int> user_map;
	map<char, int> mother_map;
	get_map(user, user_map);
	get_map(mother, mother_map);
	
	map<char, int>::iterator iter;
	list<char> same_list;
	for(iter = user_map.begin(); iter != user_map.end(); iter++){
		if(mother_map.end() != mother_map.find(iter->first)){
			same_list.push_back(iter->first);
		}
	}
	return same_list;
}
#endif

#ifdef TYPE_2
void get_input(list<int>& weight, int &capacity){
	int input_val = 0;
	cout << "weight:";
	while(1){
		cin >> input_val;
		if(!cin.fail()){//cin.fail()
			if(0 == input_val)
				break;
			if(0 < input_val)
				weight.push_back(input_val);
		}
	}
	cout << "capacity:";
	cin >> capacity;
	if(cin.fail() || (0 >= capacity))
		capacity = 0;
}

void get_output(generator<list<int>> gen_vec, int capacity, int maxsize){
	int mincount = maxsize;
	vector<list<int>> results;
	while(!gen_vec.is_end()){
		list<int> temp = gen_vec.get_next();
		int total = 0;
		int count = 1;
		for(list<int>::iterator iter = temp.begin(); iter != temp.end(); iter++){
			total += *iter;
			if(total > capacity){
				total = *iter;
				count += 1;
			}
		}
		if(mincount < count)
			continue;

		results.push_back(temp);
		if(mincount > count)
			mincount = count;
	}

	generator<list<int>> res_vec(results);
	print_class<list<int>> print_obj;
	while(!res_vec.is_end())
		print_obj.print_singal(res_vec.get_next(), " ");
	cout << mincount << endl;
}
#endif

int main(){
#ifdef TYPE_1
	string username;
	string mothername;
	unsigned int len = 0;
	get_input(username, mothername, len);
	list<char> same_list = get_same_list(username, mothername);
	if(len > same_list.size()){
		return -1;
	}

	Allsort<list<char>> run('C');//排列'A', 组合'C'
	run.allsort(same_list, len);
	run.print_results();
#endif

#ifdef TYPE_2
	list<int> weight;
	int capacity = 0;
	get_input(weight, capacity);
	
	print_class<list<int>> print_obj;
	print_obj.print_singal(weight, " ");

	Allsort<list<int>> run('A');
	run.allsort(weight, weight.size());
	generator<list<int>> gen_vec = run.get_results();
	get_output(gen_vec, capacity, weight.size());
#endif
	return 0;
}
#endif