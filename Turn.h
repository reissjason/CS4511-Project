/*
* Turn.h
*
* Created on: Apr 21, 2012
*        Author: alexander 
*/


#include "State.h"

using namespace std;

#ifndef TURN_H_
#define TURN_H_

class Turn {
public:
	Turn(State *, State *);
	Turn(int*);
	~Turn();
	Turn * next(int, int);
	void print();
	bool isOver();
	bool isValid();
	int getValue();
  State *getState1();
	State *getState2();
protected:
	State *state1;
	State *state2;
};

#endif
