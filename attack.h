#ifndef ATTACK_H
#define ATTACK_H

#include <iostream>
#include <string>
#include <math.h>

class attack {
public:
  attack(string a_name, string a_type, string a_effect, int a_power, float a_acc, float a_effect_chance);
  string get_name();
  string get_type();
  string get_effect();
  int get_power();
  float get_accuracy();
  float get_effect_chance();

private:
  string name;
  string type;
  string effect;
  int power;
  float acc;
  float effect_chance;

};
#endif /*attack.h*/
