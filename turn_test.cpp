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
#define NUM_OF_ACTIONS 2
#define INVALID -2


using namespace std;

void generateSuccessors(Node<Turn>* parent) {
	if (parent == NULL) {
		cout << "NULL value passed to Successor Generation" << endl;
	}
	int mySelectedAction;
	int hisSelectedAction;
	
	for (mySelectedAction = USE_ATTACK_1; mySelectedAction <= NUM_OF_ACTIONS; mySelectedAction++) {
		for(hisSelectedAction = USE_ATTACK_1; hisSelectedAction <= NUM_OF_ACTIONS; hisSelectedAction++) {
			Turn *nextTurn = parent->getValue()->next(mySelectedAction, hisSelectedAction);
			if (nextTurn != NULL) {
				Node<Turn>* child = new Node<Turn>(nextTurn);
				if( child->getValue()->isValid() ) {
					parent->addChild(child);
					if(!child->getValue()->isOver()) {
						generateSuccessors(child);
					}
				}
			}
		}
	}
}
int main(int args, char** argv) {
	TinyAttack* ta = new TinyAttack("damage", -2, 2, 4);
	TinyAttack* ta2 = new TinyAttack("damage", -4, 2, 2);
	Pokeman *p = new Pokeman(20,20,ta,ta2,ta,ta);
	Pokeman *p2 = new Pokeman(*p);
	State *s = new State(p, p2, 0);
	State *s2 = new State(p, p2, 1);
	Turn *t = new Turn(s, s2);
	t->print();
	State *newS = s->nextState(1);
	State *newS2 = newS->nextState(2);
	Turn *newT = new Turn(newS, newS2);
	newT->print();
	cout << "*********************************************************************************************************************" << endl;
	t->next(1,2)->print();
	Tree<Node<Turn>, Turn> tree(t);
	generateSuccessors(&tree);
	tree.printClass();
	cout << "Minimax Returns: " << turn_minimax(&tree) << endl;

	return 1;
}
