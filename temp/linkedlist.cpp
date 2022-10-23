#include <iostream>

using namespace std;

template <class T>
class Chain;

template <class N>
class ChainNode;

template<class T>
class Chain {
public:
	Chain(void);
	virtual ~Chain();
	bool isempty(void);
	void stackpush(T data);
	void stackpop(void);
	void queuepush(T data);
	void queuepop(void);
	void print(void);
private:
	ChainNode<T> *first;
	ChainNode<T> *last;
};

template<class T>
Chain<T>::Chain(void) {
	first = NULL;
	last = NULL;
};

template<class T>
Chain<T>::~Chain() {
	ChainNode<T> *next = NULL;

	while (first != NULL) {
		next = first->link;
		delete first;
		first = next;
	}
};

template<class T>
bool Chain<T>::isempty(void) {
	return first == NULL;
};

template<class T>
void Chain<T>::print(void) {
	ChainNode<T> *current = first;
	while (current != NULL) {
		cout << current->data << ' ';
		current = current->link;
	}
};

template<class T>
void Chain<T>::stackpush(T data) {
	first = new ChainNode<T>(data, first);
};

template <class T>
void Chain<T>::stackpop(void) {
	ChainNode<T> *top = first;
	if (isempty())
		cout << "empty";
	else {
		first = top->link;
		delete top;
	}
};

template<class T>
void Chain<T>::queuepush(T data) {
	if (isempty())
		first = last = new ChainNode<T>(data, NULL);
	else
		last = last->link = new ChainNode<T>(data, NULL);
};

template<class T>
void Chain<T>::queuepop(void) {
	ChainNode<T> *front = first;
	if (isempty())
		cout << "empty";
	else {
		first = front->link;
		delete front;
	}
};

template <class N>
class ChainNode {
	template <class N> friend class Chain;
public:
	ChainNode(const N data, ChainNode<N>* link);
private:
	N data;
	ChainNode<N> *link;
};

template <class N>
ChainNode<N>::ChainNode(const N data, ChainNode<N>* link) {
	this->data = data;
	this->link = link;
}

int main(void) {

}