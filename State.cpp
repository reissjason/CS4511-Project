#include "State.h"
#include "Tree.h"
#include "Node.h"
#include <string>
#include <ctime>
#include <stdlib.h>
#include <iostream>

#define USE_ATTACK_1 1
#define USE_ATTACK_2 2
#define USE_ATTACK_3 3
#define USE_ATTACK_4 4
#define SWITCH 5
#define NUM_OF_ACTIONS 5 
#define MATCH_OVER -1
#define INVALID -2
#define MY_TURN 0
#define THAT_BASTARDS_TURN 1

State::State(Pokeman* pokeman1, Pokeman* pokeman2, int turn){
	this->myPokemon = pokeman1;
	this->thatBastardsPokemon = pokeman2;
	if (turn == MATCH_OVER){
		this->whoseTurn = MATCH_OVER;
		this->isOver = true;
	}
	else if(turn == INVALID) {
		this->whoseTurn = INVALID;
		this->isOver = true;
	}
	else {
		this->whoseTurn = turn;
		this->isOver = false;
	}
	this->value = this->stateEval();
}

State::State(int *i) {
	this->value = *i;
}

State::~State() {
	delete this->myPokemon;
	delete this->thatBastardsPokemon;
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

Pokeman* State::getActivePokemon(){
	switch(this->whoseTurn) {
		case MY_TURN: return this->myPokemon;
		case THAT_BASTARDS_TURN: return this->thatBastardsPokemon;
		default: cout << "Attempting to get active pokemon on invalid state." << endl;
	}
}

Pokeman* State::getPassivePokemon(){
        switch(this->whoseTurn) {
                case MY_TURN: return this->thatBastardsPokemon;
                case THAT_BASTARDS_TURN: return this->myPokemon;
                default: cout << "Attempting to get passive pokemon on invalid state." << endl;
        }
}

State* State::nextState(int selectedAction){
	if(selectedAction > SWITCH || selectedAction < 0) {
		cout << "nextState() function called with improper value for Selected Action: " << selectedAction << endl;
		cout << "This value must be (attack) 1, (attack) 2, (attack) 3, (attack) 4, or 5(switch)" << endl;
	}
        Pokeman* myNewPokeman = new Pokeman(*myPokemon);
        Pokeman* hisNewPokeman = new Pokeman(*thatBastardsPokemon);
        int hisHealth;
        int myHealth;
        State* newState;
        TinyAttack attack;
        bool continueMatch;
	bool usedAction;
	int used = selectedAction;
	string action;
	Pokeman* active = NULL;
	Pokeman* passive = NULL;
        //cout << "Pokemans! use attack number " << selectedAction << "!!!" << endl;
        if(this->whoseTurn == MY_TURN && selectedAction != SWITCH){
		active = myNewPokeman;
		passive = hisNewPokeman;
	}
        else if(selectedAction != SWITCH){
		active = hisNewPokeman;
		passive = myNewPokeman;
	}
	if (selectedAction == SWITCH) {
		cout << "Switching not currently implemented" << endl;
		newState = new State(myNewPokeman, hisNewPokeman, INVALID);
	}
	else {
		if(active->getAttack(selectedAction) != NULL) {
			usedAction = active->usedAction(selectedAction);
			if(!usedAction){
				newState = new State(myNewPokeman, hisNewPokeman, INVALID);
				return newState;
			}
			else {
				action = active->getAttack(selectedAction)->getType();
				if(action.compare("damage") == 0) {
					continueMatch = useAttack(passive, active->getAttack(selectedAction));
				}
				else if (action.compare("heal") == 0) {
					continueMatch = useAttack(active, active->getAttack(selectedAction));
				}
			}
		
		}
		else {
			newState = new State(myNewPokeman, hisNewPokeman, INVALID);
			return newState;
		}
	}
        if(continueMatch){
        newState = new State(myNewPokeman, hisNewPokeman, (this->whoseTurn + 1) % 2);
        }
        else newState = new State(myNewPokeman, hisNewPokeman, MATCH_OVER);
        return newState;
}

int State::stateEval(){
        if(this == NULL){
                cout << "Null state provided to State Evaluation function" << endl;
                return -1000000000;
        }
        int myHealth = this->myPokemon->getHealth();
        int hisHealth = this->thatBastardsPokemon->getHealth();
	int myMax = this->myPokemon->getMaxHealth();
	int hisMax = this->thatBastardsPokemon->getMaxHealth();
	int myHealthPercent = myHealth/(myMax * 1.0) * 100;
	int hisHealthPercent = hisHealth/(hisMax * 1.0) * 100;
        return myHealthPercent - hisHealthPercent;
}

void State::print(){
	int turn = this->whoseTurn;
	string prevTurn;
	int lastAction;
	if (turn == MY_TURN || this->myPokemon->getHealth() <= 0) { 
		prevTurn = "THAT_BASTARDS_TURN"; lastAction = this->thatBastardsPokemon->getLastAction(); 
	}
	else if( turn == THAT_BASTARDS_TURN || this->thatBastardsPokemon->getHealth() <= 0) {
		prevTurn = "MY_TURN"; lastAction = this->myPokemon->getLastAction(); 
	}
	else if(turn == INVALID) {
		cout << "tried to use ability too many times" << endl;
		return;
	}
	cout << "====================================" << endl;
	cout << "Whose turn was it: " << prevTurn <<":::: " << turn << endl;
	cout << "Action used: " << lastAction <<endl;
	cout << "---------------------------------" << endl;
	cout << "My" << endl;
	this->myPokemon->print();
	cout << "---------------------------------" << endl;
	cout << "His" << endl;
	this->thatBastardsPokemon->print();
	cout << "---------------------------------" << endl;
        cout << "Value of this state: " << this->value << endl;
        cout << "====================================" << endl;
}
