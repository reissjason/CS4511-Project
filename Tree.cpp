/*
 * Tree.cpp
 *
 *  Created on: Apr 7, 2012
 *      Author: jason
 */

#include "Tree.h"

Tree::Tree(int val) : Node(val) {

}

Tree::~Tree() {
	// TODO Auto-generated destructor stub
}

void Tree::print() {
	print((Node*)this, 0);
}

void Tree::print(Node* root, int depth) {
	if (root == NULL) return;

	cout << "d: " << depth;

	if (root->parent)
		cout << " parent: " << root->parent->getValue();
	cout << endl;

	cout << "node: " << root->getValue() << endl;

	Node* temp = root->getChildren();

	while (temp != NULL) {
		print(temp, depth+1);
		temp = temp->getNext();
	}
}
