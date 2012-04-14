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
	MinHeap<Node<int> > minHeap;
	MaxHeap<Node<int> > maxHeap;

	srand ( time(NULL) );

	while (i < 10) {
		cout << "step " << i << endl;
		int* in = new int(rand()%100);

		Node<int>* n = new Node<int>(in);
		cout << "made node" << endl;
		maxHeap.addNode(n);
		cout << "added to maxHeap" << endl;
		minHeap.addNode(n);
		cout << "added to minHeap" << endl;
		//heap.print();
		i++;
	}

	cout << "final MinHeap:" << endl;
	minHeap.print();
	cout << "Min Value: " << *(minHeap.getMin()->getValue()) << endl;

	cout << "final MaxHeap:" << endl;
	maxHeap.print();
	cout << "Max Value: " << *(maxHeap.getMax()->getValue()) << endl;


	cout << "done" << endl;
	return 0;
}
