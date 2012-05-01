#include <iostream>
#include <string>
#include <math.h>

using namespace std;

#include "pkmn.h"
#include "attack.h"

pkmn::pkmn(string p_name, int * p_stats, string p_type1, string p_type2, string p_ability){
  name = p_name;
  for(int i = 0; i<6; i++){
    stats[i] = p_stats[i];
  }
  current_hp = stats[0];
  types[0] = p_type1;
  types[1] = p_type2;

  ability = p_ability;
  item = "empty";

/*  pos_atk_head = new struct attack_list;
  pos_atk_head->atk_ptr = NULL;
  pos_atk_head->next = NULL;
  known_atk_head = new struct attack_list;
  known_atk_head->atk_ptr = NULL;
  known_atk_head->next = NULL;
*/
}

pkmn::pkmn(const pkmn &pkmn){
  name = pkmn.name;
  for(int i = 0; i<6; i++){
    stats[i] = pkmn.stats[i];
  }
  current_hp = pkmn.current_hp;
  for(int i = 0; i<6; i++){
    stat_increases[i] = pkmn.stat_increases[i];
  }
  types[0] = pkmn.types[0];
  types[1] = pkmn.types[1];
  ability = pkmn.ability;
  status = pkmn.status;
  attack1 = pkmn.attack1;
  attack2 = pkmn.attack2;
  attack3 = pkmn.attack3;
  attack4 = pkmn.attack4;
  item = pkmn.item;
  charge = pkmn.charge;
}

string pkmn::get_name(){
  return name;
}

int pkmn::get_stat(int i){
  return stats[i];
}

int pkmn::get_stat_increase(int i){
  return stat_increases[i];
}

int pkmn::get_current_hp(){
  return current_hp;
}

string pkmn::get_type(int i){
  return types[i];
}

string pkmn::get_ability(){
  return ability;
}

string pkmn::get_item(){
  return item;
}

string pkmn::get_status(){
  return status;
}

bool pkmn::get_charge(){
  return charge;
}

string pkmn::get_attack(int attack_num){
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

void pkmn::update_hp(int new_hp){
  current_hp = new_hp;
}

void pkmn::change_type(string type1, string type2){
  if(type1.compare(types[0]) != 0){
    this->types[0] = type1;
  }
  if(type2.compare(types[1]) != 0){
    this->types[1] = type2;
  }
}
void pkmn::set_attacks(string p_attack1, string p_attack2, string p_attack3, string p_attack4)
{
  this->attack1.assign(p_attack1);
  this->attack2.assign(p_attack2);
  this->attack3.assign(p_attack3);
  this->attack4.assign(p_attack4);
}
/*void pkmn::add_possible_attack(attack * atk){
  struct attack_list * temp = new struct attack_list;
  temp = pos_atk_head;
  while(temp->next != NULL){
    if(temp->next->atk_ptr->get_name().compare(atk->get_name()) == 0){
      return;
    }
    else{
      temp = temp->next;
    }
  }
  struct attack_list * new_atk = new struct attack_list;
  new_atk->next = NULL;
  new_atk->atk_ptr = atk;
  temp->next = new_atk;
}

void pkmn::add_known_attack(attack * atk){
  struct attack_list * temp = new struct attack_list;
  temp = known_atk_head;
  while(temp->next != NULL){
    if(temp->next->atk_ptr->get_name().compare(atk->get_name()) == 0){
      return;
    }
    else{
      temp = temp->next;
    }
  }
  struct attack_list * new_atk = new struct attack_list;
  new_atk->next = NULL;
  new_atk->atk_ptr = atk;
  temp->next = new_atk;
}
*/
void pkmn::add_item(string p_item){
  item = p_item;
}
