#include "Pokeman.h"
#include <string>
#include <iostream>

#define DEFAULT_PP 5

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

bool Pokeman::isAlive() {
	if(this->getHealth() > 0) { return true; }
	else return false;
}

Pokeman::~Pokeman() {
    for(int i = 0; i < NUM_OF_ATTACKS; i++){
   		delete this->attack[i]; //This causes problems since the Pokema might not "own" those attacks. They're pointers, not references.
   		this->attack[i] = NULL;
    }
}

int Pokeman::getHealth(){
	return this->hp;
}

int Pokeman::getMaxHealth(){
	return this->totalHP;
}

int Pokeman::getLastAction(){
	return this->lastAction;
}

bool Pokeman::usedAction(int i) {
	if(this->getAttack(i)->getPP() > 0 && this->isAlive()){
		this->lastAction = i;
		this->getAttack(i)->use();
		return true;
	}
	else return false;
}

TinyAttack* Pokeman::getAttack1(){
	return this->attack[0];
}

TinyAttack* Pokeman::getAttack2(){
	return this->attack[1];
}

TinyAttack* Pokeman::getAttack(int i){
	return this->attack[i-1]; //Minus 1 because it only makes sense to computer scientists to ask for attack number 0. But we are computer scientists. jsr
								// btw: carl would be proud
}

bool Pokeman::changeHealth(int power){
	this->hp = this->hp + power;
	if(this->hp > this->totalHP) { this->hp = this->totalHP; };
	if (0 < this->hp){
		return true;
	}
	else {
		this->hp = 0;
		return false;
	}
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

//	cout << "Copy attacks" << endl;
	for (int i=0; i < 4; i++ ) {
		if (p.attack[i] != NULL) {
			string str;
			str = p.attack[i]->getType();
			//attack[i] = new TinyAttack(str, p.attack[i]->getPower(), p.attack[i]->getPP());
			attack[i] = new TinyAttack(*p.attack[i]);
		}
		else attack[i] = NULL;
	}
}

bool Pokeman::equals(Pokeman& p) {
	if(this->getMaxHealth() != p.getMaxHealth()) {return false; }
	if (this->getHealth() != p.getHealth()) {return false;}
	for (int i = 1; i < 5; i++){
		if (!this->getAttack(i)->equals(p.getAttack(i))) {return false;}
	}
	return true;
}

void Pokeman::print() {
	cout << "Pokeman" << endl;
	cout << "T hp: " <<
	this->totalHP << endl;
	cout << "hp: " << this->hp << endl;
	cout << "*******************" << endl;
	int i = 1;
	while (this->getAttack(i) != NULL && i < 5){
	this->getAttack(i)->print();
	cout << "*******************" << endl;
	i++;
	}
//	this->getAttack(2)->print();
//	cout << "*******************" << endl;
	cout << "done print" << endl;
}
