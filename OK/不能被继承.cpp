/*
 
*/

#include<iostream>

using namespace std;

/*
 A:˽�л����캯��
   ��������ջ�ϴ�������,ֻ�����ڶ��ϴ�������
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
 Base�����
 Finalclass�̳���Base,��Base����Ԫ,���Է��ʻ����˽�еĹ��캯������������
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

	Finalclass* p_f = new Finalclass;//��
	Finalcalss fc;//ջ
	//Testclass tc;���๹�캯��˽��,�����Ա��̳�
}
#endif