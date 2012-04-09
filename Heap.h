/*
 * Heap.h
 *
 *  Created on: Apr 8, 2012
 *      Author: jason
 */
#include <iostream>
#include <cmath>

using namespace std;

#include "Node.h"

#ifndef HEAP_H_
#define HEAP_H_

#define MAX_SIZE 20

template <class T>
class Heap {
public:
	Heap();
	virtual ~Heap();
	virtual void addNode(T *node) = 0;
	int getSize() { return size; }
	void print();

protected:
	int size;
	T* getNode(int i);
	void heapify(int i);
	static int left(int i);
	static int right(int i);
	static int parent(int i);
	T** list;
};


template <class T>
class MinHeap : public Heap<T> {
public:
	MinHeap();
	~MinHeap();
public:
	void decreaseKey(int i, T* node);
	void addNode(T* node);
	T* getMin();
};

template <class T>
class MaxHeap : public Heap<T> {
public:
	MaxHeap();
	~MaxHeap();
public:
	void increaseKey(int i, T* node);
	void addNode(T* node);
	T* getMax();
};

template <class T>
Heap<T>::Heap() : size(0){
	cout << "create heap" << endl;
	list = new T*[MAX_SIZE];
}

template <class T>
Heap<T>::~Heap() {
	delete list;
	// TODO Auto-generated destructor stub
}

template <class T>
void Heap<T>::print()
{
	for (int i = 1; i <= this->size; i++)
		cout << this->list[i]->getValue() << " : " << ((this->list[Heap::parent(i)] != NULL) ? this->list[Heap::parent(i)]->getValue() : 0) << endl;
}


template <class T>
T* Heap<T>::getNode(int i) {
	return list[i];
}

template <class T>
void Heap<T>::heapify(int i) {
	cout << "heapify(" << i << ")" << endl;

	int l = left(i);
	int r = right(i);
	int smallest = 0;

	if (l <= this->size and list[l]->getValue() < list[i]->getValue()) {
		cout << list[l]->getValue() << " < " << list[i]->getValue() << endl;
		smallest = l;
	} else
		smallest = i;

	if (r <= this->size and list[r]->getValue() < list[smallest]->getValue()) {
		cout << list[r]->getValue() << " < " << list[smallest]->getValue() << endl;
		smallest = r;
	}

	cout << "largest " << list[smallest]->getValue() << " i " << list[i]->getValue() << endl;
	if (smallest != i) {
		T* temp = list[i];
		list[i] = list[smallest];
		list[smallest] = temp;
		heapify(smallest);
	}
}

template <class T>
int Heap<T>::left(int i) {
	return i*2;
}

template <class T>
int Heap<T>::right(int i) {
	return i*2 +1;
}

template <class T>
int Heap<T>::parent(int i) {
	return i / 2;
}

template <class T>
MinHeap<T>::MinHeap() { }

template <class T>
MinHeap<T>::~MinHeap() { }

template <class T>
void MinHeap<T>::decreaseKey(int i, T* node) {
	if (node->getValue() > this->list[i]->getValue()) {
		cout << "new key is larger than current key" << endl;
		return;
	}

	this->list[i] = node;
	while (i > 1 && this->list[this->parent(i)] < this->list[i]) {
		T* temp =  this->list[i];
		 this->list[i] =  this->list[this->parent(i)];
		 this->list[this->parent(i)] = temp;

		i = this->parent(i);
	}
}

template <class T>
void MinHeap<T>::addNode(T* node) {
	this->size++;
	cout << "add node : size " << this->size << endl;
	this->list[this->size] = new T((int)pow(2,30));
	decreaseKey(this->size, node);
}

template <class T>
T* MinHeap<T>::getMin() {
	return NULL;
}

template <class T>
void MaxHeap<T>::increaseKey(int i, T* node) {
	if (node->getValue() < this->list[i]->getValue()) {
		cout << "new key is smaller than current key" << endl;
		return;
	}

	this->list[i] = node;
	while (i > 1 && this->list[this->parent(i)] > this->list[i]) {
		Node* temp = this->list[i];
		this->list[i] = this->list[this->parent(i)];
		this->list[this->parent(i)] = temp;
		i = this->parent(i);
	}
}

template <class T>
void MaxHeap<T>::addNode(T* node) {
	this->size++;
	cout << "add node : size " << this->size << endl;
	this->list[this->size] = new Node(-(int)pow(2,30));
	increaseKey(this->size, node);
}

template <class T>
T* MaxHeap<T>::getMax() {
	return NULL;
}

template <class T>
MaxHeap<T>::MaxHeap() { }

template <class T>
MaxHeap<T>::~MaxHeap() { }



#endif /* HEAP_H_ */
