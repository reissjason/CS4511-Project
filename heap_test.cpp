//============================================================================
// Name        : cs4511.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>

#include "Heap.h"

using namespace std;

int main(int args, char** argv) {
	cout << "start Heap Test" << endl;

	int i = 1;
	MinHeap<Node> heap;
	MaxHeap<Node> maxHeap;

	srand ( time(NULL) );

	while (i < 10) {
		//cout << "step " << i << endl;
		Node* n = new Node(rand()%100);
		maxHeap.addNode(n);
		heap.addNode(n);
		//heap.print();
		i++;
	}

	cout << "final MinHeap:" << endl;
	heap.print();
	cout << "Min Value: " << heap.getMin()->getValue() << endl;

	cout << "final MaxHeap:" << endl;
	maxHeap.print();
	cout << "Max Value: " << maxHeap.getMax()->getValue() << endl;


	cout << "done" << endl;
	return 0;
}
