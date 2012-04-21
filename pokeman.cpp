#include "Pokeman.h"
#include <string>
#include <iostream>

Pokeman::Pokeman(int hP, int totalHp, TinyAttack* attack1, TinyAttack* attack2, TinyAttack* attack3, TinyAttack* attack4){
        this->hp = hP;
        this->totalHP = totalHp;
        for(int i = 0; i < 4; i++){
                this->attack[i] = new TinyAttack;
        }
        this->attack[0] = attack1;
        this->attack[1] = attack2;
        this->attack[2] = attack3;
	this->attack[3] = attack4;
	this->lastAction = -1;
}


Pokeman::Pokeman(int hP, int totalHp, TinyAttack* attack1, TinyAttack* attack2, TinyAttack* attack3){
        this->hp = hP;
        this->totalHP = totalHp;
        for(int i = 0; i < 3; i++){
                this->attack[i] = new TinyAttack;
        }
        this->attack[0] = attack1;
        this->attack[1] = attack2;
	this->attack[2] = attack3;
	this->lastAction = -1;
}

Pokeman::Pokeman(int hP, int totalHp, TinyAttack* attack1, TinyAttack* attack2){
	this->hp = hP;
	this->totalHP = totalHp;
	for(int i = 0; i < 2; i++){
		this->attack[i] = new TinyAttack;
	}
	this->attack[0] = attack1;
	this->attack[1] = attack2;
	this->lastAction = -1;
}
Pokeman::Pokeman(int hP, int totalHp, TinyAttack* attack1){
        this->hp = hP;
        this->totalHP = totalHp;
        for(int i = 0; i < NUM_OF_ATTACKS; i++){
                this->attack[i] = new TinyAttack;
        }
        this->attack[0] = attack1;
	this->lastAction = -1;
}


int Pokeman::getHealth(){
	return this->hp;
}

int Pokeman::getLastAction(){
	return this->lastAction;
}

void Pokeman::usedAction(int i) {
	this->lastAction = i;
}

TinyAttack* Pokeman::getAttack1(){
	return this->attack[0];
}

TinyAttack* Pokeman::getAttack2(){
	return this->attack[1];
}

TinyAttack* Pokeman::getAttack(int i){
	return this->attack[i-1]; //Minus 1 because it only makes sense to computer sciences to ask for attack number 0.
}

bool Pokeman::changeHealth(int power){
	this->hp = this->hp + power;
	if (0 < this->hp){
		return true;
	}
	else return false;
}

Pokeman* Pokeman::clone(){
	int myHP = this->hp;
	int myTotalHP = this->totalHP;
	TinyAttack* myAttack1 = this->attack[0];
	TinyAttack* myAttack2 = this->attack[1];
	Pokeman* newPokeman = new Pokeman(myHP, myTotalHP, myAttack1, myAttack2);
	return newPokeman;
}
