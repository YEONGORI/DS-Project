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
class treenode {
	T data;
	treenode<T> *leftchild, *rightchild;

	TreeNode() {
		leftchild = rightchild = NULL;
	}
};

template<class T>
void preorder(treenode<T> *t) {
	if (t != NULL) [
		visit(t);
		preorder(t->leftchild);
		preorder(t->rightchild);
	]
};

template<class T>
void inorder(treenode<T> *t) {
	if (t != NULL) {
		inorder(t->leftchild);
		visit(t);
		inorder(t->rightchild);
	}
}

template<class T>
void postorder(treenode<T> *t) {
	if (t != NULL) {
		postorder(t->leftchild);
		postorder(t->rightchild);
		visit(t);
	}
}

template<class T>
void levelorder(treenode<T> *t) {
	Queue<treenode<T> *> q;
	treenode<T> *curnode = root;
	while (curnode) {
		visit(curnode);
		if (curnode->leftchild) q.push(curnode->leftchild);
		if (curnode->rightchild) q.push(curnode->rightchild);
		if (q.isempty()) return;

		curnode = q.Front();
		q.pop();
	}
}


/*
*
*
*
*
*
*/

#include <iostream>

using namespace std;

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