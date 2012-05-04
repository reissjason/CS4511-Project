#ifndef PKMN_H
#define PKMN_H

using namespace std;

#include <iostream>
#include <string>
#include <math.h>
#include "attack.h"

class pkmn {
public:
  pkmn(string p_name, int * p_stats, string p_type1, string p_type2, string p_ability);
  pkmn(const pkmn &pkmn);
  string get_name();
  int get_stat(int i);
  int get_stat_increase(int i);
  int get_current_hp();
  string get_type(int i);
  string get_ability();
  string get_item();
  string get_status();
  bool get_charge();
  bool reduce_hp(int damage) { current_hp -= damage; return isAlive(); }

  bool isAlive() { return current_hp > 0; }

  string get_attack(int attack_num);
  
  struct attack_list get_attack_head();

  void update_hp(int new_hp);

  void set_attacks(string p_attack1, string p_attack2, string p_attack3, string p_attack4);
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
  string status;
  struct attack_list
  {
    attack * atk_ptr;
    attack_list * next;
  };
  attack_list* pos_atk_head;
  attack_list* known_atk_head;
  string attack1;
  string attack2;
  string attack3;
  string attack4;
  string item;
  bool charge; //to be used in damage calculation
  //::TODO:: add a flashfire modifier?
};
#endif /*pkmn.h*/
