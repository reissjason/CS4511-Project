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

Turn::Turn(State *s1, State *s2) {
	this->state1 = s1;
	this->state2 = s2;
}

Turn::Turn(int *i) {
	this->state1 = new State(i);
	this->state2 = new State(i);
}

Turn::~Turn(){
	delete this->state1;
	delete this->state2;
}

State *Turn::getState1(){
	return this->state1;
}

State *Turn::getState2(){
        return this->state2;
}

bool Turn::isOver() {
	if(this->state2->myPokemon->isAlive() && this->state2->thatBastardsPokemon->isAlive())
	return false;
	else return true;
}

bool Turn::isValid() {
	int state1Valid = this->state1->whoseTurn;
	int state2Valid = this->state2->whoseTurn;

	if ( state1Valid == INVALID && state2Valid == INVALID ) {
		return false;
	}
	return true;
}

int Turn::getValue(){
	return state2->stateEval();
}

Turn* Turn::next(int myAction, int hisAction) {
	State* myTurn;
	State* hisTurn;
	State* newState1;
	State* newState2;
	Pokeman *active;
	Pokeman *passive;
	
	int mySpeed;
	int hisSpeed;
  int myPriority;
  int hisPriority;

  if(this->state1->whoseTurn == MY_TURN && this->state2->whoseTurn == HIS_TURN) {
    if(this->state1->myPokemon->get_status().compare("fainted") == 0){
      hisAction = 0;
    }
    if(this->state1->thatBastardsPokemon->get_status().compare("fainted") == 0){
      myAction = 0;
    }
  }
  else if(this->state1->whoseTurn == HIS_TURN && this->state2->whoseTurn == MY_TURN) {
    if(this->state2->myPokemon->get_status().compare("fainted") == 0){
      hisAction = 0;
    }
    if(this->state2->thatBastardsPokemon->get_status().compare("fainted") == 0){
      myAction = 0;
    }
  }

	if(this->state1->whoseTurn == MY_TURN && this->state2->whoseTurn == HIS_TURN) {
    mySpeed = this->state1->myPokemon->get_stat(5);
	  hisSpeed = this->state1->thatBastardsPokemon->get_stat(5);
//cout<<"his speed = " << hisSpeed << endl;
    if(myAction >= 5){
      myPriority = 8;
    }else myPriority = this->state1->myPokemon->getAttack(myAction)->getPriority();
    if(hisAction >= 5){
      hisPriority = 8;
    }else hisPriority = this->state1->thatBastardsPokemon->getAttack(hisAction)->getPriority();
    if(myPriority > hisPriority){
      mySpeed = hisSpeed + 1;
    }else if(myPriority < hisPriority){
      mySpeed = hisSpeed - 1;
    }
//TODO::add pokemon's speed stat, this is move priority
		myTurn = this->state1;
		hisTurn = this->state2;
		dprint("Me s1, he s2", 3);
	}
	else if(this->state1->whoseTurn == HIS_TURN && this->state2->whoseTurn == MY_TURN) {
    mySpeed = this->state2->myPokemon->get_stat(5);
	  hisSpeed = this->state2->myPokemon->get_stat(5);
		myPriority = this->state2->myPokemon->getAttack(myAction)->getPriority();
    hisPriority = this->state2->thatBastardsPokemon->getAttack(hisAction)->getPriority();
    if(myPriority > hisPriority){
      mySpeed = hisSpeed + 1;
    }else if(myPriority < hisPriority){
      mySpeed = hisSpeed - 1;
    }
		myTurn = this->state2;
    hisTurn = this->state1;
		dprint("He s1, me s2", 3);
	}
	else return this; //Match is over or invalid
	
	if(mySpeed > hisSpeed) {
		newState1 = myTurn->nextState(myAction);
		newState2 = newState1->nextState(hisAction);
	}
	else if (hisSpeed >= mySpeed) {
		newState1 = hisTurn->nextState(hisAction);
		newState2 = newState1->nextState(myAction);
	}
	
cout << "value = " << newState1->value << endl;
cout << "value = " << newState2->value << endl;

	Turn *nextTurn = new Turn(newState1, newState2);
	return nextTurn;
}

void Turn::print() {
	cout << "START******TURN****************************************" << endl;
	this->state1->print();
	cout << "===============********************************************====================" << endl;
	this->state2->print();
	cout << "END*********TURN*************************************" << endl;
}

