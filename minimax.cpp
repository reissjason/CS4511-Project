#include <iostream>
#include "minimax.h"


using namespace std;

int minimax(Node<int> *tree) {

	int v = max_value(tree, INT_MIN, INT_MAX);
	return v;
}


int max_value(Node<int> *tree, int alpha, int beta) {
	if (!tree->hasChildren()) return *tree->getValue();

	Node<int> *temp = tree->getChildren();
	int v = INT_MIN;
	while (temp != NULL) {
		v = max(v, min_value(temp, alpha, beta));
		if (v <= alpha) return v;
		beta = min(beta, v);
		temp = temp->getNext();
	}
	return v;
}

int min_value(Node<int> *tree, int alpha, int beta) {
	if (!tree->hasChildren()) return *tree->getValue();

	Node<int> *temp = tree->getChildren();
	int v = INT_MAX;
	while (temp != NULL) {
		v = min(v, max_value(temp, alpha, beta));
		if (v <= alpha) return v;
		beta = max(beta, v);
		temp = temp->getNext();
	}
	return v;
}
