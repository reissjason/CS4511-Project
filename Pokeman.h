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

#define NUM_OF_ATTACKS 4

class Pokeman {
public:
	Pokeman(int hp, int totalHP, TinyAttack*, TinyAttack*, TinyAttack*, TinyAttack*);
	Pokeman(int hp, int totalHP, TinyAttack*, TinyAttack*, TinyAttack*);
	Pokeman(int hp, int totalHP, TinyAttack*, TinyAttack*);
	Pokeman(int hp, int totalHP, TinyAttack*);
	Pokeman(){};
	Pokeman(const Pokeman& p);
	int getHealth();
	bool changeHealth(int power);
	TinyAttack *getAttack1();
	TinyAttack *getAttack2();
	TinyAttack *getAttack(int);
	Pokeman* clone();
	void usedAction(int);
	int getLastAction();

	void print();

	/*void useAttack(TinyAttack attack);*/

private:
	int hp;	
	int lastAction;
	int totalHP;
	TinyAttack* attack[NUM_OF_ATTACKS];
};

#endif /* POKEMAN_H_ */
