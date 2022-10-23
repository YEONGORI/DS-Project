#include <iostream>

using namespace std;

<<<<<<< HEAD
template<class T>
class Stack {
public:
	Stack(int stackCapacity = 10);
	~Stack() {delete [] stack};
=======
template <class T>
class Stack
{
private:
	T *stack;
	int top;
	int capcity;

public:
	Stack(int stackCapacity = 10);
	~Stack() { delete[] stack; }

>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
	bool isempty() const;
	T &Top() const;
	void push(const T &item);
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

<<<<<<< HEAD
template<class T>
Stack<T>::Stack(int stackCapacity): capacity(stackCapacity) {
=======
template <class T>
Stack<T>::Stack(int stackCapacity) : capacity(stackCapacity)
{
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
	if (capacity < 1)
		throw "Stack capacity must be > 0";
	stack = new T[capacity];
	top = -1;
};

<<<<<<< HEAD
template<class T>
inline bool Stack<T>::isempty() const {
=======
template <class T>
inline bool Stack<T>::isempty() const
{
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
	return top == -1;
};

<<<<<<< HEAD
template<class T>
inline T& Stack<T>::Top() const {
=======
template <class T>
inline T &Stack<T>::Top() const
{
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
	if (isempty())
		throw "empty";
	return stack[top];
}

<<<<<<< HEAD
template<class T>
void Stack<T>::push(const T& x) {
	if (top == capacity -1) {
		ChangeSize1D(stack, capacity, 2*capacity);
		capacity *= 2;
=======
template <class T>
void Stack<T>::push(const T &x)
{
	if (top == capacity - 1)
	{
		ChanageSize1D(stack, capacity, 2 * capacity);
		capcity *= 2;
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
	}
	stack[++top] = x;
}

<<<<<<< HEAD
template<class T>
void Stack<T>::pop() {
	if (isempty()) throw "empty\n";
	stack[top--].~T();
=======
template <class T>
void ChanageSize1D(T *&a, const int oldSize, const int newSize)
{
	if (newSize < 0)
		throw "NEw length must be >= 0";

	T *temp = new T[newSize];
	int number = min(oldSize, newSize);
	copy(a, a + number, temp);
	delete[] a;
	a = temp;
}

template <class T>
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
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
}