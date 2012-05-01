/*
 * Node.h
 *
 *  Created on: Apr 7, 2012
 *      Author: jason
 */

#include <iostream>

#include "debug_print.h"
using namespace std;

#ifndef NODE_H_
#define NODE_H_

template <class T>
class Node {
public:
	Node();
	Node(T* value);
	virtual ~Node();
	void addChild(Node<T> *node);
	Node* getChildren();
	Node* getParent();
	Node* getNext();
	Node* getRoot();
	int compare(Node<T>&, Node<T>&);
	T* getValue() { return value; }
	int getMinimaxValue() {return *minimaxValue;}
	void setMinimaxValue(int *i);
	Node<T>* getThis() { return this; }
	int getClassValue() { return value->getValue(); }
	bool hasChildren() { return children != NULL; }
	Node* parent;

protected:
	T* value;
	Node* getLastChild();
	int* minimaxValue;
	Node* next;
	Node* children;
};

template <class T>
Node<T>::Node() {
	this->children = NULL;
	this->value = NULL;
	this->next = NULL;
	this->parent = NULL;
	this->minimaxValue = new int(0);
}

template <class T>
Node<T>::Node(T* value) {
	dprint("construct node", 4);
	this->children = NULL;
	this->value = value;
	this->next = NULL;
	this->parent = NULL;
	this->minimaxValue = new int(0);
	dprint("node constructed", 4);
}

template <class T>
void Node<T>::setMinimaxValue(int *i) {
	*minimaxValue = *i;
}

template <class T>
Node<T>::~Node() {
	Node* temp = this->children;
	while (temp != NULL) {
		Node* del = temp;
		temp = temp->next;
		delete del;
	}
	delete this->value;
	this->value = NULL;
	this->children = NULL;
	this->next = NULL;
}

template <class T>
Node<T>* Node<T>::getChildren() {
	return this->children;
}

template <class T>
void Node<T>::addChild(Node<T>* node) {
	dprint("adding child", 4);
	node->parent = this;

	Node<T>* temp = this->getLastChild();
	if (temp)
		temp->next = node;
	else
		this->children = node;
	dprint("added child", 4);
}

template <class T>
Node<T>* Node<T>::getLastChild() {
	dprint("getting last child", 4);
	Node<T>* temp = this->children;

	while (temp != NULL && temp->getNext() != NULL)
		temp = temp->getNext();

	return temp;
}

template <class T>
Node<T>* Node<T>::getParent() {
	return this->parent;
}

template <class T>
Node<T>* Node<T>::getRoot() {
	Node<T>* temp = this;
	while(temp->getParent() != NULL) {
		temp = temp->getParent();
	}
        return temp;
}

template <class T>
Node<T>* Node<T>::getNext() {
	return this->next;
}



#endif /* NODE_H_ */
