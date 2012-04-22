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
#include "Node.h"
#include "minimax.h"

using namespace std;

int main(int args, char** argv) {

	cout << "start Tree Test" << endl;

	int i = 5;

	int* x = new int(10);
	Tree<Node<int>,int> tree(x);

	srand ( time(NULL) );

	while (i > 0) {
		//cout << "step " << i << endl;
		int* in = new int(rand()%100);
		Node<int>* n = new Node<int>(in);
		tree.addChild(n);

		for (int j = 0; j < 3; j++) {
			int* inn = new int(rand()%100);
			Node<int>* m = new Node<int>(inn);
			n->addChild(m);
		}
		i--;
	}

	int value = minimax(&tree);

	tree.print();

	cout << "minimax returned: " << value << endl;


	cout << "done" << endl;
	return 0;
}
