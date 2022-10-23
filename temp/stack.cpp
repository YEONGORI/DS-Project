#include <iostream>

using namespace std;

template<class T>
class Stack {
public:
	Stack(int stackCapacity = 10);
	~Stack() {delete [] stack};
	bool isempty() const;
	T& Top() const;
	void push(const T& item);
	void pop();
	void ChangeSize1D(T*& a, const int oldSize, const int newSize) {
		if (newSize < 0) throw "New length must be >= 0";
		T* temp = new T[newSize];
		int number = min(oldSize, newSize);
		copy(a, a+number, temp);
		delete []a;
		a = temp;
	}
private:
	T *stack;
	int top;
	int capacity;
};

template<class T>
Stack<T>::Stack(int stackCapacity): capacity(stackCapacity) {
	if (capacity < 1)
		throw "Stack capacity must be > 0";
	stack = new T[capacity];
	top = -1;
};

template<class T>
inline bool Stack<T>::isempty() const {
	return top == -1;
};

template<class T>
inline T& Stack<T>::Top() const {
	if (isempty())
		throw "empty";
	return stack[top];
}

template<class T>
void Stack<T>::push(const T& x) {
	if (top == capacity -1) {
		ChangeSize1D(stack, capacity, 2*capacity);
		capacity *= 2;
	}
	stack[++top] = x;
}

template<class T>
void Stack<T>::pop() {
	if (isempty()) throw "empty\n";
	stack[top--].~T();
}