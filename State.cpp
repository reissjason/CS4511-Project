#include "State.h"
#include <string>
#include <ctime>
#include <stdlib.h>
#include <iostream>

#define MY_TURN 0
#define THAT_BASTARDS_TURN 1


State::State(Pokeman* pokeman1, Pokeman* pokeman2, int turn){
	this->myPokemon = pokeman1;
	this->thatBastardsPokemon = pokeman2;
	this->whoseTurn = turn;
	this->isOver = false;
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
	else newState = new State(myNewPokeman);
	hisHealth = hisNewPokeman->getHealth();
	myHealth = myNewPokeman->getHealth();
	cout << "My Health: " << myHealth << endl;
	cout << "--- His Health: " << hisHealth << endl;
	cout << "=======================" << endl;
	return newState;
}
