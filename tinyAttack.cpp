#include <iostream>

#include "TinyAttack.h"

TinyAttack::TinyAttack(string attackType, int attackDamage, int pp){
	this->type = attackType;
	this->power = attackDamage;
	this->pp = pp;
}

TinyAttack::TinyAttack(){
	this->power = 0;
	this->type = "ERROR: Default constructor used for TinyAttack";
}

string TinyAttack::getType(){
	return this->type;
}

int TinyAttack::getPower(){
	return this->power;
}

int TinyAttack::getPP(){
	return this->pp;
}

void TinyAttack::use(){
	this->pp =  this->getPP() - 1;
}

void TinyAttack::print(){
	cout << "Type: " << this->getType() << endl;
	cout << "Power: " << this->getPower() << endl;
	cout << "PP: " << this->getPP() << endl;
}

