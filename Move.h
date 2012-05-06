/*
 * Move.h
 *
 *  Created on: May 6, 2012
 *      Author: jason
 */

#ifndef MOVE_H_
#define MOVE_H_


class Move {
public:
	Move(int val) { value = val; }
	~Move();
	Move(Pokeman* attacker, TinyAttack *atat, int value);
	int getValue();
	Pokeman* getPokeman();
	TinyAttack* getAttack();

private:
	int value;
	Pokeman* attacker;
	TinyAttack* attack;
};

Move::Move(Pokeman* attacker, TinyAttack *attack, int value) {
	this->value = value;
	this->attacker = attacker;
	this->attack = attack;
}

Move::~Move() {

}

int Move::getValue() {
	return value;
}

Pokeman* Move::getPokeman() {
	return attacker;
}

TinyAttack* Move::getAttack() {
	return attack;
}

#endif /* MOVE_H_ */
