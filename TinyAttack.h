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
  TinyAttack(string attackType, int attackDamage);
  TinyAttack();
  string getType();
  int getPower();

private:
  string type;
  int power;
};

#endif /* TINYATTACK_H_ */