/*
 
*/

#include<iostream>

using namespace std;

/*
 A:私有化构造函数
   不可以在栈上创建对象,只可以在堆上创建对象
*/
class A{
public:
	int num;
	static A* Construct(int n){
		A* pa = new A;
		pa->num = n;
		return pa;
	}
	static void Destruct(A* pInstance){
		delete pInstance;
		pInstance = NULL;
	}
private:
	A(){}
	~A(){}
};

/*
 Base虚基类
 Finalclass继承于Base,是Base的友元,可以访问基类的私有的构造函数和析构函数
*/
template<class T>
class Base{
	friend T;
private:
	Base();
	~Base();
};
class Finalclass : virtual public Base<Finalclass>{
public:
	Finalclass();
	~Finalclass();
};
class Testclass : public Finalclass{
};

#if 0
int main(){
	A* p_a = A::Construct(100);
	cout << p_a->num << endl;
	A::Destruct(p_a);

	Finalclass* p_f = new Finalclass;//堆
	Finalcalss fc;//栈
	//Testclass tc;基类构造函数私有,不可以被继承
}
#endif