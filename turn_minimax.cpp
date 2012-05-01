#include <iostream>
#include <climits>

#include "Node.h"
#include "turn_minimax.h"
#include "Turn.h"

using namespace std;

int turn_minimax(Node<Turn> *tree) {
	int *useMove = new int(0);
	int *depth = new int(0);
        int v = max_value(tree, INT_MIN, INT_MAX);
        return v;
}


int max_value(Node<Turn> *tree, int alpha, int beta) {
        if (!tree->hasChildren()) return tree->getValue()->getValue();

        Node<Turn> *temp = tree->getChildren();
        int v = INT_MIN;
        while (temp != NULL) {
                v = max(v, min_value(temp, alpha, beta));
                if (v <= alpha) {
			return v;
		}
                beta = min(beta, v);
                temp = temp->getNext();
        }
	cout << "Setting minimax value " << endl;
        cout << v << endl;
	int *i = new int(v);
	tree->setMinimaxValue(i);
	delete i;
        return v;
}

int min_value(Node<Turn> *tree, int alpha, int beta) {
        if (!tree->hasChildren()) return tree->getValue()->getValue();

        Node<Turn> *temp = tree->getChildren();
        int v = INT_MAX;
        while (temp != NULL) {
                v = min(v, max_value(temp, alpha, beta));
                if (v <= alpha) {
			return v;
		}
                beta = max(beta, v);
                temp = temp->getNext();
        }
	cout << "Setting minimax value " << endl;
	cout << v << endl;
	int *i = new int(v);
	tree->setMinimaxValue(i);
	delete i;
        return v;
}

