/* 
*   Turn.cpp
*  
*   Created on Apr 21, 2012
*        Author: alexander
*/

#include <ostream>

#include "Turn.h"

#define MY_TURN 0
#define HIS_TURN 1
#define INVALID -2

//WARNING: Pokemons are not currently instakilled if their health drops below zero.

Turn::Turn(State *s1, State *s2) {
	this->state1 = s1;
	this->state2 = s2;
}

bool Turn::isOver() {
	int myHealth1 = this->state1->myPokemon->getHealth();
	int myHealth2 = this->state2->myPokemon->getHealth();
	int hisHealth1 = this->state1->thatBastardsPokemon->getHealth();
	int hisHealth2 = this->state2->thatBastardsPokemon->getHealth();
	
	if(myHealth1 == 0 || myHealth2 == 0 || hisHealth1 == 0 || hisHealth2 == 0 ) {
		return true;
	}
	
	return false;
}

bool Turn::isValid() {
	int state1Valid = this->state1->whoseTurn;
	int state2Valid = this->state2->whoseTurn;

	if ( state1Valid == INVALID || state2Valid == INVALID ) {
		return false;
	}
	return true;
}

int Turn::getValue(){
	return state1->stateEval(); //state1 and state2 have the same value.
}

Turn* Turn::next(int myAction, int hisAction) {
	State* myTurn;
	State* hisTurn;
	State* newState1;
	State* newState2;
	
	int mySpeed;
	int hisSpeed;

	if(!this->state1->myPokemon->isAlive() || !this->state1->thatBastardsPokemon->isAlive() || !this->state2->myPokemon->isAlive() || !this->state2->thatBastardsPokemon->isAlive()) {
		return this;
	}
	
	if(state1->whoseTurn == MY_TURN && state2->whoseTurn == HIS_TURN) {
		mySpeed = this->state1->myPokemon->getAttack(myAction)->getSpeed();
		hisSpeed = this->state2->thatBastardsPokemon->getAttack(hisAction)->getSpeed();
		myTurn = this->state1;
		hisTurn = this->state2;
	}
	else if(state1->whoseTurn == HIS_TURN && state2->whoseTurn == MY_TURN) {
		mySpeed = this->state2->myPokemon->getAttack(myAction)->getSpeed();
                hisSpeed = this->state1->thatBastardsPokemon->getAttack(hisAction)->getSpeed();
		myTurn = this->state2;
                hisTurn = this->state1;
	}
	
	if(mySpeed > hisSpeed) {
		newState1 = myTurn->nextState(myAction);
		newState2 = newState1->nextState(hisAction);
	}
	else if (hisSpeed >= mySpeed) {
		newState1 = hisTurn->nextState(hisAction);
		newState2 = newState1->nextState(myAction);
	}
	
	Turn *nextTurn = new Turn(newState1, newState2);
	return nextTurn;
}

void Turn::print() {
	this->state1->print();
	cout << "===================================" << endl;
	this->state2->print();
}

