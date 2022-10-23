#include <iostream>
#include <algorithm>
using namespace std;

template<class T>
class Stack
{
private:
	T *stack;
	int top;
	int capcity;
public:
	Stack(int stackCapacity = 10);
	~Stack() {delete[] stack;}

	bool isempty() const;
	T& Top() const;
	void push(const T& item);
	void pop();
};

template<class T>
Stack<T>::Stack(int stackCapacity):capacity(stackCapacity)
{
	if (capacity < 1)
		throw "Stack capacity must be > 0";
	stack = new T[capacity];
	top = -1;
}

template<class T>
inline bool Stack<T>::isempty() const
{
	return top == -1;
}

template<class T>
inline T& Stack<T>::Top() const
{
	if (isempty())
		throw "Stack is empty";
	return stack[top];
}

template<class T>
void Stack<T>::push(const T& x)
{
	if (top == capacity - 1) {
		ChanageSize1D(stack, capacity, 2*capacity);
		capcity *= 2;
	}
	stack[++top] = x;
}

template <class T>
void ChanageSize1D(T*& a, const int oldSize, const int newSize)
{
	if (newSize < 0) throw "NEw length must be >= 0";

	T* temp = new T[newSize];
	int number = min(oldSize, newSize);
	copy(a, a+number, temp);
	delete[] a;
	a = temp;
}

template<class T>
void Stack<T>::pop()
{
	if (isempty())
		throw "Stack is empty. Cannot delete.";
	stack[top--].~T();
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	
	return 0;
	
}