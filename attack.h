#ifndef ATTACK_H
#define ATTACK_H

using namespace std;

#include <iostream>
#include <string>
#include <math.h>

class attack {
public:
  attack(string a_name, string a_type, string a_effect, string a_p_or_s, int a_power, float a_acc, float a_effect_chance);
  attack(attack &attack);
  string get_name();
  string get_type();
  string get_effect();
  string get_p_or_s();
  int get_power();
  float get_accuracy();
  float get_effect_chance();

private:
  string name;
  string type;
  string effect;
  string p_or_s;
  int power;
  float acc;
  float effect_chance;
/*not nessessarily the chance, depends on the exact effect. 
for freeze effect, chance to freeze
for heal, amount of max hp healed
for stat increases, amount increased
*/
};
#endif /*attack.h*/
