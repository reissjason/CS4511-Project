#include <iostream>
#include <string>
#include <math.h>

using namespace std;

#include "pkmn.h"
#include "attack.h"

pkmn::pkmn(string p_name, int * p_stats, string * p_types, string p_ability){
  name = p_name;
  for(int i = 0; i<6; i++){
    stats[i] = p_stats[i];
  }
  current_hp = stats[0];
  for(int i = 0; i<6; i++){
    types[0] = p_types[0];
  }
  ability = p_ability;
  status = NULL;
  pos_atk_head = new struct attack_list;
  pos_atk_head->atk_ptr = NULL;
  pos_atk_head->next = NULL;
  known_atk_head = new struct attack_list;
  known_atk_head->atk_ptr = NULL;
  known_atk_head->next = NULL;
}

string pkmn::get_name(){
  return name;
}

int * pkmn::get_stat(){
  return stats;
}

string * pkmn::get_type(){
  return types;
}

string pkmn::get_ability(){
  return ability;
}

void pkmn::change_type(string type1, string type2){
  if(type1.compare(types[0]) != 0){
    this->types[0] = type1;
  }
  if(type2.compare(types[1]) != 0){
    this->types[1] = type2;
  }
}

void pkmn::add_possible_attack(attack * atk){
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

void pkmn::add_item(string p_item){
  item = p_item;
}
