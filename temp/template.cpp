#include <iostream>

using namespace std;

template <class T>
class Test
{
public:
	Test();
	~Test();
	T Data(T);
}; 

template<class T>
Test<T>::Test() {
	cout << "생성자\n";
};

template<class T>
Test<T>::~Test() {
	cout << "소멸자\n";
};

template<class T>
T Test<T>::Data(T v) {
	return v;
}

int main(void) {
	Test<int> Var1;
	Test<double> Var2;
	Test<char> Var3;

	cout << Var1.Data(100);
	cout << Var2.Data(20);
	cout << Var3.Data(30);
}