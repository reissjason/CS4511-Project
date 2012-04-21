#include "TinyAttack.h"
#include "tinyAttack.cpp"
#include <iostream>
#include <string.h>

using namespace std;

int main(int args, char** argv) {
	cout << "HIHIHIHIHIHIHIHIHIHIHIHIHIHIHIHIHIHI" << endl;
	int i = 0;
	string damage = "damage";
	int power;
	TinyAttack* ta = new TinyAttack(damage, 5);
	power = ta->getPower();
	cout << ta->getType() << endl;
	cout << power << endl;
	return i;
}
