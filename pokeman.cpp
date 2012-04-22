#include "Pokeman.h"
#include <string>
#include <iostream>

Pokeman::Pokeman(int hP, int totalHp, TinyAttack* attack1, TinyAttack* attack2, TinyAttack* attack3, TinyAttack* attack4){
        this->hp = hP;
        this->totalHP = totalHp;
        for(int i = 0; i < 4; i++){
                this->attack[i] = NULL;
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
        for(int i = 0; i < 4; i++){
                this->attack[i] = NULL;
        }
        this->attack[0] = attack1;
        this->attack[1] = attack2;
	this->attack[2] = attack3;
	this->lastAction = -1;
}

Pokeman::Pokeman(int hP, int totalHp, TinyAttack* attack1, TinyAttack* attack2){
	this->hp = hP;
	this->totalHP = totalHp;
	for(int i = 0; i < 4; i++){
		this->attack[i] = NULL;
	}
	this->attack[0] = attack1;
	this->attack[1] = attack2;
	this->lastAction = -1;
}

Pokeman::Pokeman(int hP, int totalHp, TinyAttack* attack1){
        this->hp = hP;
        this->totalHP = totalHp;
        for(int i = 0; i < NUM_OF_ATTACKS; i++){
                this->attack[i] = NULL;
        }
        this->attack[0] = attack1;
	this->lastAction = -1;
}

Pokeman::~Pokeman() {
    for(int i = 0; i < NUM_OF_ATTACKS; i++){
   		delete this->attack[i];
   		this->attack[i] = NULL;
    }
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
	return this->attack[i-1]; //Minus 1 because it only makes sense to computer sciences to ask for attack number 0. But we are computer scientists. jsr
								// btw: carl would be proud
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

// Copy constructor
Pokeman::Pokeman(const Pokeman& p) {
	hp = p.hp;
	totalHP = p.totalHP;

	cout << "Copy attacks" << endl;
	for (int i=0; i < 4; i++ ) {
		if (p.attack[i] != NULL) {
			string str;
			str = p.attack[i]->getType();
			attack[i] = new TinyAttack(str, p.attack[i]->getPower());
		}
		else attack[i] = NULL;
	}
}

void Pokeman::print() {
	cout << "Pokeman" << endl;
	cout << "T hp: " <<
	this->totalHP << endl;
	cout << "hp: " << this->hp << endl;
	cout << "att1: " << this->getAttack(1)->getType() << endl;
	cout << "att2: " << this->getAttack(2)->getType() << endl;
	cout << "done print" << endl;
}
