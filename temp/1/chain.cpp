#include <iostream>
#include <algorithm>
using namespace std;

template <class K>
class ChainNode;

template <class T>
class Chain
{
private:
	ChainNode<T> *last;
	ChainNode<T> *first;

public:
	Chain(void);
	virtual ~Chain();
	void StackPush(T data);
	void StackPop(void);
	void QueuePush(T data);
	void QueuePop(void);
	void Print(void);
	bool IsEmpty(void);
};

template <class T>
Chain<T>::Chain(void)
{
	first = NULL;
	last = NULL;
}

template <class T>
Chain<T>::~Chain(void)
{
	ChainNode<T> *next = NULL;

	while (first != NULL)
	{
		next = first->link;
		cout << "Delete: " << first->data << endl;
		delete first;
		first = next;
	}
};

template <class T>
bool Chain<T>::IsEmpty(void)
{
	return first == NULL;
};

template <class T>
void Chain<T>::Print(void)
{
	ChainNode<T> *current = first;
	cout << "Print: ";

	while (current != NULL)
	{
		cout << current->data << ' ';
		current = current->link;
	}
	cout << endl;
};

template <class T>
void Chain<T>::StackPush(T data)
{
	first = new ChainNode<T>(data, first);
	cout << "StackPush: " << data << endl;
};

template <class T>
void Chain<T>::StackPop(void)
{
	ChainNode<T> *top = first;

	if (IsEmpty())
	{
		cout << "StackPop: empty!" << endl;
	}
	else
	{
		cout << "StackPop: " << top->data << endl;
		first = top->link;
		delete top;
	}
}

template <class T>
void Chain<T>::QueuePush(T data)
{
	if (IsEmpty())
		first = last = new ChainNode<T>(data, NULL);
	else
		last = last->link = new ChainNode<T>(data, NULL);
	cout << "QueuePush: " << data << endl;
}

template <class T>
void Chain<T>::QueuePop(void)
{
	ChainNode<T> *front = first;

	if (IsEmpty())
	{
		cout << "QueuePop: empty!" << endl;
	}
	else
	{
		cout << "QueuePop: " << front->data << endl;
		first = front->link;
		delete front;
	}
};

template <class K>
class ChainNode
{
	template <class T>
	friend class Chain;

public:
	ChainNode(const K data, ChainNode<K> *link = NULL);

private:
	K data;
	ChainNode<K> *link;
};

template <class K>
ChainNode<K>::ChainNode(const K data, ChainNode<K> *link)
{
	this->data = data;
	this->link = link;
};

int main(void)
{
	Chain<int> chain;

	chain.StackPush(1);
	chain.StackPush(2);
	chain.StackPush(3);

	chain.Print();

	chain.StackPop();
	chain.StackPop();
	chain.StackPop();
	chain.StackPop();

	chain.QueuePush(1);
	chain.QueuePush(2);
	chain.QueuePush(3);

	chain.Print();

	chain.QueuePop();
	chain.QueuePop();
	chain.QueuePop();
	chain.QueuePop();

	return 0;
}

// class Base
// {
// public:
// 	~Base() {
// 		cout << "Base desturctor!" << endl;
// 	}
// };

// class Derived: public Base
// {
// public:
// 	char *largebuffer;
// 	Derived() {
// 		largebuffer = new char[3000];
// 	}
// 	~Derived() {
// 		cout << "Derived destructor!" << endl;
// 		delete[] largebuffer;
// 	};
// };