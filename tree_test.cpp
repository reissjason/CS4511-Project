//============================================================================
// Name        : cs4511.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>

#include "Tree.h"

using namespace std;

int main(int args, char** argv) {
	cout << "start Tree Test" << endl;

	int i = 5;

	Tree tree(10);

	srand ( time(NULL) );

	while (i > 0) {
		//cout << "step " << i << endl;
		Node* n = new Node(rand()%100);
		tree.addChild(n);

		for (int j = 0; j < 3; j++) {
			Node* m = new Node(rand()%100);
			n->addChild(m);
		}
		i--;
	}

	tree.print();

	cout << "done" << endl;
	return 0;
}
