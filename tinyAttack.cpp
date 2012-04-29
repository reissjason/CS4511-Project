#include <iostream>

#include "TinyAttack.h"
#include "debug_print.h"
TinyAttack::TinyAttack(string attackType, int attackDamage, int pp, int spd){
	this->type = attackType;
	this->power = attackDamage;
	this->pp = pp;
	this->speed = spd;
}

TinyAttack::TinyAttack(){
	this->power = 0;
	this->type = "ERROR: Default constructor used for TinyAttack";
}

TinyAttack::~TinyAttack(){
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

int TinyAttack::getSpeed(){
	return this->speed;
}

void TinyAttack::use(){
	this->pp =  this->getPP() - 1;
}

bool TinyAttack::equals(TinyAttack *ta) 
	{
	if(this->getType() != ta->getType())
		{ 
		dprint("Type mismatch", 2);
		return false;
		}
	if(this->getPower() != ta->getPower())
		{
		dprint("Power mismatch", 2);
		 return false;
		}
/*	if(this->getPP() != ta->getPP()) 
		{
		dprint("PP mismatch", 1);
		return false;
		} //debatable*/
	if(this->getSpeed() != ta->getSpeed())
		{
		dprint("Speed mismatch", 2);
		 return false;
		}
	return true;
	}

void TinyAttack::print(){
	cout << "Type: " << this->getType() << endl;
	cout << "Power: " << this->getPower() << endl;
	cout << "PP: " << this->getPP() << endl;
}

