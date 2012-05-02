/*
 * State.h
 *
 *  Created on: Apr 12, 2012
 *      Author: alexander
 */

#include "TinyAttack.h"
#include "Pokeman.h"
#include "Tree.h"
#include "Node.h"

using namespace std;

#ifndef STATE_H_
#define STATE_H_

class State {
public: 
	State(Pokeman *pokemon1, Pokeman *pokemon2, int turn);
	State(Pokeman *winner);
	State(State &s);
	State(int *);
	State* nextState(int);
	~State();
	int stateEval();
	void print();
	Pokeman* getActivePokemon();
	Pokeman* getPassivePokemon();
	bool isOver;
	Pokeman* myPokemon;
	Pokeman* thatBastardsPokemon;
	int whoseTurn;
	int value;
	void setActionUsed(int);
	int getActionUsed();
protected:
	int actionUsed;
};

#endif /* STATE_H_ */
