#include <iostream>
#include <string>
#include <math.h>

using namespace std;

#include "attack.h"

attack::attack(string a_name, string a_type, string a_effect, string a_p_or_s, int a_power, float a_acc, float a_effect_chance){
  name = a_name;
  type = a_type;
  effect = a_effect;
  p_or_s = a_p_or_s;
  power = a_power;
  acc = a_acc;
  effect_chance = a_effect_chance;
}

attack::attack(attack &attack){
  name = attack.name;
  type = attack.type;
  effect = attack.effect;
  p_or_s = attack.p_or_s;
  power = attack.power;
  acc = attack.acc;
  effect_chance = attack.effect_chance;
}

string attack::get_name(){
  return name;
}

string attack::get_type(){
  return type;
}

string attack::get_effect(){
  return effect;
}

string attack::get_p_or_s(){
  return p_or_s;
}

int attack::get_power(){
  return power;
}

float attack::get_accuracy(){
  return acc;
}

float attack::get_effect_chance(){
  return effect_chance;
}

