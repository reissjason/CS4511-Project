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

class Node {
public:
	Node() {};
	Node(int value);
	virtual ~Node();
	void addChild(Node *node);
	Node* getChildren();
	Node* getParent();
	Node* getNext();
	int compare(Node&, Node&);
	int getValue() { return value; }
	Node* parent;

protected:
	int value;
	Node* getLastChild();

	Node* next;
	Node* children;
};

#endif /* NODE_H_ */
