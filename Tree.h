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

template <class T, class S>
class Tree : public Node<S> {
public:
	Tree(S* val);
	virtual ~Tree();
	void print();
	void printClass();
	void print(T* root, int depth);
	void printClass(T* root, int depth);
};

template <class T, class S>
Tree<T,S>::Tree(S* val)  : T(val) {

}

template <class T, class S>
Tree<T,S>::~Tree() {
	//cout << "delete the tree" << endl;
}

template <class T, class S>
void Tree<T,S>::print() {
	print((T*)this, 0);
}

template <class T, class S>
void Tree<T,S>::printClass() {
        printClass((T*)this, 0);
}

template <class T, class S>
void Tree<T,S>::print(T* root, int depth) {
	if (root == NULL) return;

	cout << " d: " << depth;

	if (root->parent)
		cout << " parent: " << *(root->parent->getValue());

	cout << " node: " << *(root->getValue());

	T* temp = root->getChildren();

	while (temp != NULL) {
		print(temp, depth+1);
		temp = temp->getNext();
	}

	cout << endl;
}

template <class T, class S>
void Tree<T,S>::printClass(T* root, int depth) {
        if (root == NULL) return;

        cout << "d: " << depth;

        if (root->parent)
                cout << " parent: " << (root->parent->getClassValue());
        cout << endl;

        cout << " node: " << (root->getClassValue()) << endl;
	
        T* temp = root->getChildren();

        while (temp != NULL) {
                printClass(temp, depth+1);
                temp = temp->getNext();
        }
}

#endif /* TREE_H_ */
