//============================================================================
// Name        : turn_test.cpp
// Author      : alexander koenen
// Version     : 0
// Copyright   : 
// Description : Test turns 
//============================================================================


#include <iostream>
#include <cstdlib>

#include "Turn.h"
#include "Node.h"
#include "Tree.h"
#include "turn_minimax.h"

#define USE_ATTACK_1 1
#define USE_ATTACK_2 2
#define USE_ATTACK_3 3
#define USE_ATTACK_4 4
#define SWITCH 5
#define NUM_OF_ACTIONS 4
#define INVALID -2
#define MAX_DEPTH 2 


using namespace std;
int count = 0;
void generateSuccessors(Node<Turn>* parent, int depth) {
	if (depth > MAX_DEPTH) { return; }
	if (parent == NULL) {
		cout << "NULL value passed to Successor Generation" << endl;
	}
	int mySelectedAction = 1;
	int hisSelectedAction = 1;
	
	for (mySelectedAction = USE_ATTACK_1; mySelectedAction <= NUM_OF_ACTIONS; mySelectedAction++) {
		for(hisSelectedAction = USE_ATTACK_1; hisSelectedAction <= NUM_OF_ACTIONS; hisSelectedAction++) {
			count++;
			cout << count << ": " << "Using " << mySelectedAction << ", " << hisSelectedAction << " at depth " << depth << endl;
			Turn *nextTurn = parent->getValue()->next(mySelectedAction, hisSelectedAction);
			if (nextTurn != NULL) {
				Node<Turn>* child = new Node<Turn>(nextTurn);
				if( child->getValue()->isValid() ) {
					parent->addChild(child);
					if(!child->getValue()->isOver()) {
						generateSuccessors(child, depth + 1);
					}
				}
				else delete child; //Invalid children are deleted, as is the Spartan tradition.
			}
		}
	}
}
int main(int args, char** argv) {
	TinyAttack* ta = new TinyAttack("damage", -12, 2, 2);
	TinyAttack* ta2 = new TinyAttack("damage", -14, 2, 3);
	TinyAttack *ta3 = new TinyAttack("heal", 2, 2, 5);
	TinyAttack *ta4 = new TinyAttack(*ta);
	TinyAttack *ta5 = new TinyAttack(*ta);
	TinyAttack *ta6 = new TinyAttack(*ta);
        TinyAttack *ta7 = new TinyAttack(*ta);
	TinyAttack *ta8 = new TinyAttack(*ta);
	Pokeman *p = new Pokeman(40,40,ta2,ta,ta5,ta6);
	Pokeman *p2 = new Pokeman(20,20,ta3,ta4,ta7,ta8);
	Pokeman *p3 = new Pokeman(*p);
	Pokeman *p4 = new Pokeman(*p2);
	State *s = new State(p, p2, 0);
	State *s2 = new State(p3, p4, 1);
	Turn *t = new Turn(s, s2);
	//t->print();
	State *newS = s->nextState(1);
	State *newS2 = newS->nextState(2);
	Turn *newT = new Turn(newS, newS2);
	//newT->print();
	cout << "*********************************************************************************************************************" << endl;
	//t->next(1,2)->print();
	Tree<Node<Turn>, Turn> tree(t);
	generateSuccessors(&tree, 0);
	tree.printClass();
	cout << "Minimax Returns: " << turn_minimax(&tree) << endl;
	Node<Turn>* temp = tree.getChildren();
	while(temp != NULL) {
		cout << "Minimax Value: " << endl;
		cout << temp->getMinimaxValue() << endl;
		temp = temp->getNext();
	}

	return 1;
}
