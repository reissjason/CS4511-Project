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
  TinyAttack(string attackType, int attackDamage, int pp, int spd);
  TinyAttack();
  // Copy constructor
  ~TinyAttack();
  TinyAttack(const TinyAttack& ta) : power(ta.power) , type(ta.type) , pp(ta.pp) , speed(ta.speed) {}
  string getType();
  int getPower();
  int getPP();
  void print();
  void use();
  int getSpeed();
  bool equals(TinyAttack*);

protected:
  string type;
  int power;
  int pp;
  int speed;
};

#endif /* TINYATTACK_H_ */
