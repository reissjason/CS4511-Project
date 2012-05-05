/*
 * Pokeman.h
 *
 *  Created on: Apr 12, 2012
 *      Author: nick
 */

#include "TinyAttack.h"

using namespace std;

#ifndef LIST_H_
#define LIST_H_

#define ATTACK_LIST_LENGTH 30

class list {

public:
  list();

  int * stat_cast(int hp, int atk, int def, int spatk, int spdef, int spd);
  TinyAttack * string_to_attack(string move_name);
  void construct_list();

private:
	TinyAttack* attack_list[30];

};
#endif /* LIST_H_ */
