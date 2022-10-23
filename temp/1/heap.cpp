#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class MaxHeap {
public:
	T *heap;
	int heapSize;
	int capacity;

	MaxHeap(int theCapacity = 10);
	void Push(const T& e);
	void ChangeSize1D(T*& a, const int oldSize, const int newSize);
	void Pop(void);
}

template<class T>
MaxHeap<T>::MaxHeap (int theCapacity = 10) {
	if (theCapacity < 1)
		throw "Capacity must be >= 1.";
	capacity = theCapacity;
	heapSize = 0;
	heap = new T[capacity + 1];
}

template<class T>
void MaxHeap<T>::Push(const T& e) {
	if (heapSize == capacity) {
		ChangeSize1D(heap, capacity, 2 * capacity);
		capacity *= 2;
	}
	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] < e) {
		heap[currentNode] = heap[currentNode/2];
		currentNode /= 2;
	}
	heap[currentNode] = e;
}

template<class T>
void ChangeSize1D(T*& a, const int oldSize, const int newSize) {
	if (newSize < 0) throw "New length must be >= 0";

	T *temp = new T[newSize];
	int number = min(oldSize, newSize);
	copy(a, a+number, temp);
	delete [] a;
	a = temp;
}

template<class T>
void MaxHeap<T>::Pop(void) {
	if (IsEmpty()) throw "Heap is empty. Cannot delete.";
	heap[1].~T();

	T lastE = heap[heapSize--];

	int currentNode = 1;
	int child = 2;

	while (child <= heapSize) {
		if (child < heapSize && heap[child] < heap[child + 1])
			child++;
		if (lastE >= heap[child])
			break;
	
		heap[currentNode] = heap[child];
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = lastE;
}

int main(void)
{
	
	return 0;
}