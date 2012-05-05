#include "Pokeman.h"
#include <string>
#include <iostream>

#define DEFAULT_PP 5

Pokeman::Pokeman(string p_name, int * p_stats, string p_type1, string p_type2, string p_ability, TinyAttack* attack1, TinyAttack* attack2, TinyAttack* attack3, TinyAttack* attack4){ //new constructor
  this->name.assign(p_name);
  for(int i = 0; i<6; i++){
    this->stats[i] = p_stats[i];
  }
  this->current_hp = stats[0];
  this->types[0] = p_type1;
  this->types[1] = p_type2;

  this->ability.assign(p_ability);
  this->item.assign("empty");
  this->status.assign("none");

  for(int i = 0; i < 4; i++){
    this->attack[i] = NULL;
  }
  this->attack[0] = attack1;
  this->attack[1] = attack2;
  this->attack[2] = attack3;
  this->attack[3] = attack4;

  this->lastAction = -1;

  set_attacks(attack1->get_name(),attack2->get_name(),attack3->get_name(),attack4->get_name());
}

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

Pokeman::Pokeman(){
  this->name.assign("empty");
  for(int i = 0; i<6; i++){
    this->stats[i] = 0;
  }
  this->current_hp = stats[0];
  this->types[0] = "none";
  this->types[1] = "none";

  this->ability.assign("none");
  this->item.assign("empty");
  this->status.assign("none");

  for(int i = 0; i < 4; i++){
    this->attack[i] = NULL;
  }
  this->attack[0] = new TinyAttack();
  this->attack[1] = new TinyAttack();
  this->attack[2] = new TinyAttack();
	this->attack[3] = new TinyAttack();
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

void Pokeman::reduce_hp(int damage) {
	current_hp -= damage;
}

int Pokeman::getHealth(){
	return this->current_hp;
}

int Pokeman::getMaxHealth(){
	return this->totalHP;
}

int Pokeman::getLastAction(){
	return this->lastAction;
}

bool Pokeman::usedAction(int i) {
	if(this->getAttack(i)->getPP() > 0 && this->get_status().compare("fainted") != 0){
		this->lastAction = i;
		this->getAttack(i)->use();
		return true;
	}else{
//cout<<"pp = " << this->getAttack(i)->getPP() << endl;
	 return false;
  }
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
  if(&p != NULL){
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

//old ends here
    name = p.name;
    for(int i = 0; i<6; i++){
      stats[i] = p.stats[i];
    }
    current_hp = p.current_hp;
    for(int i = 0; i<6; i++){
      stat_increases[i] = p.stat_increases[i];
    }
    types[0] = p.types[0];
    types[1] = p.types[1];
    ability = p.ability;
    status = p.status;
    attack1 = p.attack1;
    attack2 = p.attack2;
    attack3 = p.attack3;
    attack4 = p.attack4;
    item = p.item;
    charge = p.charge;
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

//old code ends here

string Pokeman::get_name(){
  return name;
}

int Pokeman::get_stat(int i){
  return stats[i];
}

int Pokeman::get_stat_increase(int i){
  return stat_increases[i];
}

int Pokeman::get_current_hp(){
  return current_hp;
}

string Pokeman::get_type(int i){
  return types[i];
}

string Pokeman::get_ability(){
  return ability;
}

string Pokeman::get_item(){
  return item;
}

string Pokeman::get_status(){
  return status;
}

bool Pokeman::get_charge(){
  return charge;
}

string Pokeman::get_attack(int attack_num){
  string ret;
  ret.assign("null attack");
  if(attack_num == 1){
    ret.assign(attack1);
  }else if(attack_num == 2){
    ret.assign(attack2);
  }else if(attack_num == 3){
    ret.assign(attack3);
  }else if(attack_num == 4){
    ret.assign(attack4);
  }
  return ret;
}

void Pokeman::update_hp(int new_hp){
  this->current_hp = new_hp;
}

void Pokeman::change_type(string type1, string type2){
  if(type1.compare(types[0]) != 0){
    this->types[0] = type1;
  }
  if(type2.compare(types[1]) != 0){
    this->types[1] = type2;
  }
}
void Pokeman::set_attacks(string p_attack1, string p_attack2, string p_attack3, string p_attack4)
{
  this->attack1.assign(p_attack1);
  this->attack2.assign(p_attack2);
  this->attack3.assign(p_attack3);
  this->attack4.assign(p_attack4);
}

void Pokeman::add_item(string p_item){
  this->item = p_item;
}

bool Pokeman::get_protect(){
  return protect;
}

void Pokeman::set_protect(bool i){
  protect = i;
}

void Pokeman::set_status(string new_status){
  if(this->status.compare("none") == 0){
    this->status.assign(new_status);
  }else if(new_status.compare("fainted") == 0){
    this->status.assign(new_status);
  }
}
