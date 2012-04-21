#include "State.h"
#include <string>
#include <ctime>
#include <stdlib.h>
#include <iostream>

#define MATCH_OVER -1
#define MY_TURN 0
#define THAT_BASTARDS_TURN 1
#define SWITCH 5

int stateEval(State*);


State::State(Pokeman* pokeman1, Pokeman* pokeman2, int turn){
	this->myPokemon = pokeman1;
	this->thatBastardsPokemon = pokeman2;
	if (turn == MATCH_OVER){
		this->whoseTurn = MATCH_OVER;
		this->isOver = true;
	}
	else {
		this->whoseTurn = turn;
		this->isOver = false;
	}
	this->value = stateEval(this);
}

State::State(Pokeman* winner){
	this->myPokemon = winner;
	this->isOver = true;
}

bool useAttack(Pokeman* targetPokeman, TinyAttack* attack){
	int power = attack->getPower();
	bool stillAlive = targetPokeman->changeHealth(power);
	return stillAlive;
}

State* State::nextState(){
	Pokeman* myNewPokeman = this->myPokemon->clone();
	Pokeman* hisNewPokeman = this->thatBastardsPokemon->clone();
	int hisHealth;
	int myHealth;
	State* newState;
	srand ( time(NULL) );
	TinyAttack attack;
	bool continueMatch;
	int random = rand() % 2 + 1;
	cout << "Pokemans! use attack number " << random << "!!!" << endl;
	if(this->whoseTurn == MY_TURN){
		continueMatch = useAttack(hisNewPokeman, myNewPokeman->getAttack(random));
	}
	else {
		continueMatch = useAttack(myNewPokeman, hisNewPokeman->getAttack(random));
	}
	if(continueMatch){
	newState = new State(myNewPokeman, hisNewPokeman, (this->whoseTurn + 1) % 2);
	}
	else newState = new State(myNewPokeman, hisNewPokeman, MATCH_OVER);
	hisHealth = hisNewPokeman->getHealth();
	myHealth = myNewPokeman->getHealth();
/*	cout << "My Health: " << myHealth << endl;
	cout << "--- His Health: " << hisHealth << endl;
	cout << "Value of this state: " << newState->value << endl;
	cout << "=======================" << endl;*/
	newState->print();
	return newState;
}

State* State::nextState(int selectedAction){
	if(selectedAction > SWITCH || selectedAction < 0) {
		cout << "nextState() function called with improper value for Selected Action: " << selectedAction << endl;
		cout << "This value must be (attack) 1, (attack) 2, (attack) 3, (attack) 4, or 5(switch)" << endl;
	}
        Pokeman* myNewPokeman = this->myPokemon->clone();
        Pokeman* hisNewPokeman = this->thatBastardsPokemon->clone();
        int hisHealth;
        int myHealth;
        State* newState;
        TinyAttack attack;
        bool continueMatch;
	int used = selectedAction;
        cout << "Pokemans! use attack number " << selectedAction << "!!!" << endl;
        if(this->whoseTurn == MY_TURN && selectedAction != SWITCH){
		myNewPokeman->usedAction(used);
                continueMatch = useAttack(hisNewPokeman, myNewPokeman->getAttack(selectedAction));
        }
        else if(selectedAction != SWITCH){
		hisNewPokeman->usedAction(used);
                continueMatch = useAttack(myNewPokeman, hisNewPokeman->getAttack(selectedAction));
        }
	else {
		cout << "Switching not currently implemented" << endl;
	}
        if(continueMatch){
        newState = new State(myNewPokeman, hisNewPokeman, (this->whoseTurn + 1) % 2);
        }
        else newState = new State(myNewPokeman, hisNewPokeman, MATCH_OVER);
        hisHealth = hisNewPokeman->getHealth();
        myHealth = myNewPokeman->getHealth();
/*        cout << "My Health: " << myHealth << endl;
        cout << "--- His Health: " << hisHealth << endl;
	cout << "Value of this state: " << newState->value << endl;
        cout << "=======================" << endl;*/
	newState->print();
        return newState;
}

int stateEval(State* state){
        if(state == NULL){
                cout << "Null state provided to State Evaluation function" << endl;
                return -1000000000;
        }
        int myHealth = state->myPokemon->getHealth();
        int hisHealth = state->thatBastardsPokemon->getHealth();
        return myHealth - hisHealth;
}

void State::print(){
	int turn = this->whoseTurn;
	string prevTurn;
	int lastAction;
	if (turn == MY_TURN) { prevTurn = "THAT_BASTARDS_TURN"; lastAction = this->thatBastardsPokemon->getLastAction(); }
	else {prevTurn = "MY_TURN"; lastAction = this->myPokemon->getLastAction(); }
	cout << "====================================" << endl;
	cout << "Whose turn was it: " << prevTurn << endl;
	cout << "Action used: " << lastAction <<endl;
	cout << "My Health: " << this->myPokemon->getHealth() << endl;
	cout << "--- His Health: " << this->thatBastardsPokemon->getHealth() << endl;
        cout << "Value of this state: " << this->value << endl;
        cout << "=======================" << endl;
}
