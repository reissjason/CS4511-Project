/*
 * State.h
 *
 *  Created on: Apr 12, 2012
 *      Author: alexander
 */

#include "TinyAttack.h"
#include "Pokeman.h"

using namespace std;

#ifndef STATE_H_
#define STATE_H_

class State {
public: 
	State(Pokeman *pokemon1, Pokeman *pokemon2, int turn);
	State(Pokeman *winner);
	State* nextState();
	State* nextState(int);
	void print();
	bool isOver;
	Pokeman* myPokemon;
	Pokeman* thatBastardsPokemon;
	int whoseTurn;
	int value;
};

#endif /* STATE_H_ */
