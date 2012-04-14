/*
 * Node.cpp
 *
 *  Created on: Apr 7, 2012
 *      Author: jason
 */

#include "Node.h"

Node::Node(int value) {
	this->children = NULL;
	this->value = value;
	this->next = NULL;
	this->parent = NULL;
}

Node::~Node() {
	Node* temp = this->children;
	while (temp != NULL) {
		Node* del = temp;
		temp = temp->next;
		delete del;
	}
	this->children = NULL;
	this->next = NULL;
}

Node* Node::getChildren() {
	return this->children;
}

void Node::addChild(Node* node) {
	dprint("adding child", 4);
	node->parent = this;

	Node* temp = this->getLastChild();
	if (temp)
		temp->next = node;
	else
		this->children = node;
	dprint("added child", 4);
}

Node* Node::getLastChild() {
	dprint("getting last child", 4);
	Node* temp = this->children;

	while (temp != NULL && temp->getNext() != NULL)
		temp = temp->getNext();

	return temp;
}

Node* Node::getParent() {
	return this->parent;
}

Node* Node::getNext() {
	return this->next;
}
