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

<<<<<<< HEAD
template<class T>
class maxheap {
=======
template <class T>
class MaxHeap
{
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
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
<<<<<<< HEAD
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
=======

	MaxHeap(int theCapacity = 10);
	void Push(const T &e);
	void ChangeSize1D(T *&a, const int oldSize, const int newSize);
	void Pop(void);
};

template <class T>
MaxHeap<T>::MaxHeap(int theCapacity = 10)
{
	if (theCapacity < 1)
		throw "Capacity must be >= 1.";
	capacity = theCapacity;
	heapSize = 0;
	heap = new T[capacity + 1];
}

template <class T>
void MaxHeap<T>::Push(const T &e)
{
	if (heapSize == capacity)
	{
		ChangeSize1D(heap, capacity, 2 * capacity);
		capacity *= 2;
	}
	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] < e)
	{
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
	}
	heap[curnod] = e;
};

<<<<<<< HEAD
template<class T>
void maxheap<T>::pop(void) {
	if (isempty()) throw "힙힙비어씀";
=======
template <class T>
void ChangeSize1D(T *&a, const int oldSize, const int newSize)
{
	if (newSize < 0)
		throw "New length must be >= 0";

	T *temp = new T[newSize];
	int number = min(oldSize, newSize);
	copy(a, a + number, temp);
	delete[] a;
	a = temp;
}

template <class T>
void MaxHeap<T>::Pop(void)
{
	if (IsEmpty())
		throw "Heap is empty. Cannot delete.";
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
	heap[1].~T();

	T lastelement = heap[heapsize--];

	int curnod = 1;
	int child = 2;
<<<<<<< HEAD
	while (child <= heapsize) {
		if (child < heapsize && heap[child] < heap[child + 1])
=======

	while (child <= heapSize)
	{
		if (child < heapSize && heap[child] < heap[child + 1])
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
			child++;
		if (lastelement >= heap[child])
			break;

<<<<<<< HEAD
		heap[curnod] = heap[child];
		curnod = child;
		child *= 2;
	}
	heap[curnod] = lastelement;
=======
		heap[currentNode] = heap[child];
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = lastE;
}

int main(void)
{

	return 0;
>>>>>>> 44e83976ce347a0322c23b3329fdd2e590356ba5
}