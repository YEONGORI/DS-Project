#include <iostream>

using namespace std;
template<class T>
class treenode {
	T data;
	treenode<T> *leftchild, *rightchild;

	TreeNode() {
		leftchild = rightchild = NULL;
	}
};

template<class T>
class maxheap {
public:
	maxheap(int cap = 10);
	~maxheap(){};
	void push(const T& e);
	void pop();
	void changesize(T*& a, const int oldsize, const int newsize) {
		if (newsize < 0) throw "0보다 크게 하자";
		T *temp = new T[newsize];
		int number = min(oldsize, newsize)l
		copy(a, a+number, temp);
		delete [] a;
		a = temp;
	}
private:
	T *heap;
	int heapsize;
	int capacity;
};

template<class T>
maxheap<T>::maxheap(int cap = 10) {
	if (cap < 1) throw "1이상으로하자";
	capacity = cap;
	heapsize = 0;s
	heap = new T[capacity];
};

template<class T>
void maxheap<T>::push(const T& e) {
	if (heapsize == capacity) {
		changesize(heap, capacity, capacity*2);
		capacity *= 2;
	}
	int curnod = ++heapsize;
	while (curnod != 1 heap[curnod/2] < e) {
		heap[curnod] = heap[curnod/2];
		curnod /= 2;
	}
	heap[curnod] = e;
};

template<class T>
void maxheap<T>::pop(void) {
	if (isempty()) throw "힙힙비어씀";
	heap[1].~T();

	T lastelement = heap[heapsize--];

	int curnod = 1;
	int child = 2;
	while (child <= heapsize) {
		if (child < heapsize && heap[child] < heap[child + 1])
			child++;
		if (lastelement >= heap[child])
			break;

		heap[curnod] = heap[child];
		curnod = child;
		child *= 2;
	}
	heap[curnod] = lastelement;
}