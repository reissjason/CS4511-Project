/*
 * Tree.h
 *
 *  Created on: Apr 7, 2012
 *      Author: jason
 */
#include "Node.h"
#include <stdlib.h>

#ifndef TREE_H_
#define TREE_H_

class Tree : public Node{
public:
	Tree(int val);
	virtual ~Tree();
	void print();
	void print(Node* root, int depth);
};

#endif /* TREE_H_ */
