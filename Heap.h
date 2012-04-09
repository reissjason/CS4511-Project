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
	int depth = (int)log2(size);

	for (int i = 0; i <= depth; i++) {
		for (int x = 1; x <= (depth-i); x++)
			cout << "  ";
		for (int j = 1; j <= pow(2, i); j++) {
			//cout << "index: " << (j+(int)pow(2,i))-1 << endl;
			int index = j+(int)pow(2,i)-1;
			if (this->list[index] != NULL)
				cout << this->list[index]->getValue() << " ";
		}
		cout << endl;
	}
		// cout << this->list[i]->getValue() << " : " << ((this->list[Heap::parent(i)] != NULL) ? this->list[Heap::parent(i)]->getValue() : 0) << endl;
}


template <class T>
T* Heap<T>::getNode(int i) {
	return list[i];
}

template <class T>
void Heap<T>::heapify(int i) {

	int l = left(i);
	int r = right(i);
	int smallest = 0;

	if (l <= this->size and list[l]->getValue() < list[i]->getValue()) {
		smallest = l;
	} else
		smallest = i;

	if (r <= this->size and list[r]->getValue() < list[smallest]->getValue()) {
		smallest = r;
	}

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
		return;
	}

	this->list[i] = node;
	while (i > 1 && this->list[this->parent(i)]->getValue() > this->list[i]->getValue()) {
		T* temp =  this->list[i];
		 this->list[i] =  this->list[this->parent(i)];
		 this->list[this->parent(i)] = temp;

		i = this->parent(i);
	}
}

template <class T>
void MinHeap<T>::addNode(T* node) {
	this->size++;
	this->list[this->size] = new T((int)pow(2,30));
	decreaseKey(this->size, node);
}

template <class T>
T* MinHeap<T>::getMin() {
	return this->list[1];
}

template <class T>
void MaxHeap<T>::increaseKey(int i, T* node) {
	if (node->getValue() < this->list[i]->getValue()) {
		return;
	}

	this->list[i] = node;
	while (i > 1 && this->list[this->parent(i)]->getValue() < this->list[i]->getValue()) {
		Node* temp = this->list[i];
		this->list[i] = this->list[this->parent(i)];
		this->list[this->parent(i)] = temp;
		i = this->parent(i);
	}
}

template <class T>
void MaxHeap<T>::addNode(T* node) {
	this->size++;
	this->list[this->size] = new Node(-(int)pow(2,30));
	increaseKey(this->size, node);
}

template <class T>
T* MaxHeap<T>::getMax() {
	return this->list[1];
}

template <class T>
MaxHeap<T>::MaxHeap() { }

template <class T>
MaxHeap<T>::~MaxHeap() { }



#endif /* HEAP_H_ */
