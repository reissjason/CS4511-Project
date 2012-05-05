/*
 * Pokeman.h
 *
 *  Created on: Apr 12, 2012
 *      Author: alexander
 */

#include "TinyAttack.h"

using namespace std;

#ifndef POKEMAN_H_
#define POKEMAN_H_

#define NUM_OF_ATTACKS 4

class Pokeman {
public:
  Pokeman(string p_name, int * p_stats, string p_type1, string p_type2, string p_ability, TinyAttack*, TinyAttack*, TinyAttack*, TinyAttack*);
	Pokeman(int hp, int totalHP, TinyAttack*, TinyAttack*, TinyAttack*, TinyAttack*);
	Pokeman(int hp, int totalHP, TinyAttack*, TinyAttack*, TinyAttack*);
	Pokeman(int hp, int totalHP, TinyAttack*, TinyAttack*);
	Pokeman(int hp, int totalHP, TinyAttack*);
	Pokeman();
	Pokeman(const Pokeman& p);
	~Pokeman();
	bool equals(Pokeman& p);
	int getHealth();
	int getMaxHealth();
	bool changeHealth(int power);
	TinyAttack *getAttack1();
	TinyAttack *getAttack2();
	TinyAttack *getAttack(int);
	Pokeman* clone();
	bool usedAction(int);
	bool isAlive();
	int getLastAction();
	void reduce_hp(int damage);

	void print();

//end of old code

  string get_name();
  int get_stat(int i);
  int get_stat_increase(int i);
  int get_current_hp();
  string get_type(int i);
  string get_ability();
  string get_item();
  string get_status();
  bool get_charge();
  bool get_protect();

  string get_attack(int attack_num);
  
  void update_hp(int new_hp);
  void set_status(string new_status);
  void set_protect(bool i);

  void set_attacks(string p_attack1, string p_attack2, string p_attack3, string p_attack4);
  void change_type(string type1, string type2);
  void add_item(string p_item);

	/*void useAttack(TinyAttack attack);*/

private:
	int hp;	
	int lastAction;
	int totalHP;
	TinyAttack* attack[NUM_OF_ATTACKS];

//old variables end here

  string name;
  int stats[6];
  int current_hp;
  int stat_increases[6];
  string types[2];
  string ability;
  string status;

  string attack1;
  string attack2;
  string attack3;
  string attack4;

  string item;
  bool protect;
  bool charge; //to be used in damage calculation
  //::TODO:: add a flashfire modifier?
};

#endif /* POKEMAN_H_ */
