//============================================================================
// Name        : cs4511.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Heap.h"

using namespace std;

int main(int args, char** argv) {
	cout << "start" << endl;

	int i = 1;
	MinHeap<Node> heap;

	while (i < 10) {
		Node* n = new Node(10-i++);
		heap.addNode(n);
		heap.print();
	}

	heap.print();


	cout << "done" << endl;
	return 0;
}
