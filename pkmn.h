#ifndef PKMN_H
#define PKMN_H

#include <iostream>
#include <string>
#include <math.h>
#include "attack.h"

class pkmn {
public:
  pkmn(string p_name, int * p_stats, string * p_types, string p_ability);
  string get_name();
  int * get_stat();
  string * get_type();
  string get_ability();
  void change_type(string type1, string type2);
  void add_possible_attack(attack * atk);
  void add_known_attack(attack * atk);
  void add_item(string p_item);

private:
  string name;
  int stats[6];
  int current_hp;
  int stat_increases[6];
  string types[2];
  string ability;
  struct attack_list
  {
    attack * atk_ptr;
    attack_list * next;
  };
  attack_list* pos_atk_head;
  attack_list* known_atk_head;
  string item;
};
#endif /*pkmn.h*/
