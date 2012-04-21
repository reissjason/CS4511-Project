//============================================================================
// Name        : state_tree_test.cpp
// Author      : alexander koenen
// Version     : 0
// Copyright   : 
// Description : Test construction of a state tree 
//============================================================================

#include <iostream>
#include <cstdlib>

#include "Tree.h"
#include "Node.h"
#include "State.h"

#define USE_ATTACK_1 1
#define USE_ATTACK_2 2
#define USE_ATTACK_3 3
#define USE_ATTACK_4 4
#define SWITCH 5
#define NUM_OF_ACTIONS 2

using namespace std;

void GWFS(Node<State>* root);

void generateSuccessors(Node<State>* parent){
	if (parent == NULL) {
		cout << "NULL value passed to Successor Generation" << endl;
	}
	int selectedAction;
	for(selectedAction = USE_ATTACK_1; selectedAction <= NUM_OF_ACTIONS; selectedAction++) {
		State* nextState = parent->getValue()->nextState(selectedAction);
		Node<State>* child = new Node<State>(nextState);
		parent->addChild(child);
		if(!child->getValue()->isOver) {
			generateSuccessors(child);
		}
	}
}

void GBFS(Node<State>* root){
	if (root == NULL) {
		cout << "Tried to search null tree" << endl;
	}
	
	int maxValue = -100000;
	
	Node<State>* children = root->getChildren();
	Node<State>* bestChild;
	if (children == NULL) {
		return;
	}
	while(children != NULL) {
		if (children->getValue()->value > maxValue) {
			maxValue = children->getValue()->value;
			bestChild = children;
		}
		children = children->getNext();
	}
	cout << "The best move is-----------------" << endl;
	bestChild->getValue()->print();
	GWFS(bestChild);
}

void GWFS(Node<State>* root){
        if (root == NULL) {
                cout << "Tried to search null tree" << endl;
        }

        int minValue = 100000;

        Node<State>* children = root->getChildren();
        Node<State>* bestChild;
        if (children == NULL) {
                return;
        }
        while(children != NULL) {
                if (children->getValue()->value < minValue) {
                        minValue = children->getValue()->value;
                        bestChild = children;
                }
                children = children->getNext();
        }
        cout << "The best move is-----------------" << endl;
        bestChild->getValue()->print();
        GBFS(bestChild);
}

int main(int args, char** argv) {
        cout << "start State Tree Test" << endl;
	int i = 1;
	int selectedAction = USE_ATTACK_1;
	int value;
	bool done = false;
	TinyAttack* ta1 = new TinyAttack("damage", -20);
	TinyAttack* ta2 = new TinyAttack("damage", -10);
	Pokeman* p1 = new Pokeman(25, 25, ta1, ta2);
	Pokeman* p2 = p1->clone();
	State* state = new State(p1,p2,0);
	Tree<Node<State>,State> tree(state);
	/*while (!state->isOver){
		for(selectedAction = USE_ATTACK_1; selectedAction <= NUM_OF_ACTIONS; selectedAction++){
			cout << "Action " << selectedAction << endl;
			State* nextState = state->nextState(selectedAction);
			state = nextState;
			Node<State>* newStateNode = new Node<State>(nextState);
			cout << "TTTTTTTTTTTTEEEEEEEEEEEESSSSSSSSSSSSSSTTTTTTTTTTTTT: " << newStateNode->getValue()->value << endl;
			tree.addChild(newStateNode);
		}
	}*/
	for(selectedAction = USE_ATTACK_1; selectedAction <= NUM_OF_ACTIONS; selectedAction++){
		State* nextState = state->nextState(selectedAction);
		Node<State>* newStateNode = new Node<State>(nextState);
		tree.addChild(newStateNode);
		generateSuccessors(newStateNode);
	}
	tree.printClass();
	GBFS(tree.getThis());
	return i;
}

int StateEval(State* state){
	if(state == NULL){
		cout << "Null state provided to State Evaluation function" << endl;
		return -1;
	}
	int myHealth = state->myPokemon->getHealth();
	int hisHealth = state->thatBastardsPokemon->getHealth();
	return myHealth - hisHealth;

}
