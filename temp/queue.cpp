#include <iostream>

using namespace std;

template <class T>
class Queue {
public:
	Queue(int queuecapacity = 10);
	virtual ~Queue();
	T& Front() const;
	T& Rear();
	bool isempty();
	void push(T& data);
	void pop();

private:
	T *queue;
	int front;
	int rear;
	int capacity;
};

template<class T>
Queue<T>::Queue(int queuecapacity): (capacity = queuecapacity) {
	queue = new Queue[capacity];
	front = 0;
	rear = 0;
};

template<class T>
Queue<T>::~Queue(void) {
	delete [] queue;
};

template<class T>
T& Queue<T>::Front(void) const {
	return queue[front];
};

template<class T>
T& Queue<T>::Rear(void) {
	return queue[rear];
};

template<class T>
bool Queue<T>::isempty(void) {
	return front == rear;
};

template<class T>
void Queue<T>::push(T& data) {
	if (rear == capacity) {
		changecapacity();
	}
	queue[++rear] = data;
};

template<class T>
void Queue<T>::pop(void) {
	if (!isempty()) {
		queue[front--].~T();
	}
}