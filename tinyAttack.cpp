#include "TinyAttack.h"

TinyAttack::TinyAttack(string attackType, int attackDamage){
	this->type = attackType;
	this->power = attackDamage;
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