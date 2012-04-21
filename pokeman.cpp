#include "Pokeman.h"
#include <string>
#include <iostream>


Pokeman::Pokeman(int hP, int totalHp, TinyAttack* attack1, TinyAttack* attack2){
	this->hp = hP;
	this->totalHP = totalHp;
	for(int i = 0; i < NUM_OF_ATTACKS; i++){
		this->attack[i] = new TinyAttack;
	}
	this->attack[0] = attack1;
	this->attack[1] = attack2;
}

int Pokeman::getHealth(){
	return this->hp;
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

// Copy constructor
Pokeman::Pokeman(const Pokeman& p) {
	hp = p.hp;
	totalHP = p.totalHP;
	attack1 = p.attack1;
	attack2 = p.attack2;
}

void Pokeman::print() {
	cout << "Pokeman" << endl;
	cout << "T hp: " << this->totalHP << endl;
	cout << "hp: " << this->hp << endl;
	cout << "att1: " << this->attack1.getType() << endl;
	cout << "att2: " << this->attack2.getType() << endl;
}


/*void Pokeman::useAttack(TinyAttack attack){
	string attackType = attack.getType();
	cout << "Using attack type " + attackType << endl;
	int attackPower = attack.getPower();
	cout << "Attack has power: " + attackPower << endl;

}*/

