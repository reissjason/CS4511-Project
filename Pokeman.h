/*
 * Pokeman.h
 *
 *  Created on: Apr 12, 2012
 *      Author: alexander
 */

#include "TinyAttack.h"

using namespace std;

#ifndef POKEMAN_H_
#define POKEMAN_H_

class Pokeman {
public:
	Pokeman(int hp, int totalHP, TinyAttack &primaryAttack, TinyAttack &secondaryAttack);
	Pokeman(){};
	Pokeman(const Pokeman& p);
	int getHealth();
	bool changeHealth(int power);
	TinyAttack &getAttack1();
	TinyAttack &getAttack2();
	TinyAttack &getAttack(int);
	Pokeman* clone();
	void print();

	/*void useAttack(TinyAttack attack);*/

private:
	int hp;
	int totalHP;
	TinyAttack attack1;
	TinyAttack attack2;
};

#endif /* POKEMAN_H_ */
