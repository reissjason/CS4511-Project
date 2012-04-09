/*
 * Node.cpp
 *
 *  Created on: Apr 7, 2012
 *      Author: jason
 */

#include "Node.h"

Node::Node(int value) {
	this->value = value;
	this->next = NULL;
}

Node::~Node() {
	this->next = NULL;
	// TODO Auto-generated destructor stub
}

Node* Node::getChildren() {
	return this->children;
}

void Node::addChild(Node &node) {
	Node* temp = this->getLastChild();
	temp->next = &node;
}

Node* Node::getLastChild() {
	Node* temp = this->children;

	while (temp != NULL)
		temp = temp->getNext();

	return temp;
}

Node* Node::getParent() {
	return this->parent;
}

Node* Node::getNext() {
	return this->next;
}
