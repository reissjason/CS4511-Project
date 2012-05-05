/*
 * TinyAttack.h
 *
 *  Created on: Apr 12, 2012
 *      Author: alexander
 */

#include <string>

using namespace std;

#ifndef TINYATTACK_H_
#define TINYATTACK_H_

class TinyAttack {
public:
  TinyAttack(string a_name, string a_type, string a_effect, string a_p_or_s, int a_power, float a_acc, float a_effect_chance, int pp, int pty);
  
  TinyAttack(string attackType, int attackDamage, int pp, int pty);
  TinyAttack();
  // Copy constructor
  ~TinyAttack();
  TinyAttack(const TinyAttack& ta);

  string getType();
  int getPower();
  int getPP();
  void print();
  void use();
  int getPriority();
  bool equals(TinyAttack*);

  string get_name();
  string get_type(); //legacy code, shouldn't be used
  string get_effect();
  string get_p_or_s();
  int get_power(); //legacy code, shouldn't be used
  float get_accuracy();
  float get_effect_chance();

protected:
  string name;
  string effect;
  string p_or_s;
  float acc;
  float effect_chance;

  string type;
  int power;
  int pp;
  int priority;
};

#endif /* TINYATTACK_H_ */
