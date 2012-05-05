#include <iostream>

#include "TinyAttack.h"
#include "debug_print.h"
TinyAttack::TinyAttack(string a_name, string a_type, string a_effect, string a_p_or_s, int a_power, float a_acc, float a_effect_chance, int pp, int pty){
  this->name = a_name;
  this->type = a_type;
  this->effect = a_effect;
  this->p_or_s = a_p_or_s;
  this->power = a_power;
  this->acc = a_acc;
  this->effect_chance = a_effect_chance;
  this->pp = pp;
	this->priority = pty;
}

TinyAttack::TinyAttack(string attackType, int attackDamage, int pp, int pty){
  this->name = "default";
  this->effect = "none";
  this->p_or_s = "none";
  this->acc = 1;
  this->effect_chance = 0;

	this->type = attackType;
	this->power = attackDamage;
	this->pp = pp;
	this->priority = pty;
}

TinyAttack::TinyAttack(){
  this->name = "default";
  this->effect = "none";
  this->p_or_s = "none";
  this->acc = 1;
  this->effect_chance = 0;

	this->power = 0;
	this->type = "ERROR: Default constructor used for TinyAttack";
	this->pp = 0;
	this->priority = 0;
}

TinyAttack::TinyAttack(const TinyAttack& ta){
  this->name = ta.name;
  this->type = ta.type;
  this->effect = ta.effect;
  this->p_or_s = ta.p_or_s;
  this->power = ta.power;
  this->acc = ta.acc;
  this->effect_chance = ta.effect_chance;
  this->pp = ta.pp;
	this->priority = ta.priority;
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

int TinyAttack::getPriority(){
	return this->priority;
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
	if(this->getPriority() != ta->getPriority())
		{
		dprint("Priority mismatch", 2);
		 return false;
		}
	return true;
	}

string TinyAttack::get_name(){
  return name;
}

string TinyAttack::get_type(){//legacy code, shouldn't be used
  return type;
}

string TinyAttack::get_effect(){
  return effect;
}

string TinyAttack::get_p_or_s(){
  return p_or_s;
}

int TinyAttack::get_power(){//legacy code, shouldn't be used
  return power;
}

float TinyAttack::get_accuracy(){
  return acc;
}

float TinyAttack::get_effect_chance(){
  return effect_chance;
}

void TinyAttack::print(){
//TODO::print the rest of the constants
/*  cout << "name: " << this->;
  cout << "effect: " << this->;
  cout << "p_or_s: " << this->;
  cout << "acc: " << this->;
  cout << "effect_chance: " << this->;
*/

	cout << "Type: " << this->getType() << endl;
	cout << "Power: " << this->getPower() << endl;
	cout << "PP: " << this->getPP() << endl;
}

