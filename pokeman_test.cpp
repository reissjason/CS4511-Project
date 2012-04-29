//============================================================================
// Name        : cs4511.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>

#include "Pokeman.h"

using namespace std;

bool testHP(Pokeman *p, int expected) {
	if (p->getHealth() == expected) {
		return true;
	}
	cout << "Failed hp test. Expected " << expected << " but received " << p->getHealth();
	return false;
}

bool testLastAction(Pokeman *p, int expected) {
	int test = p->getLastAction();
        if (test == expected) {
                return true;
        }
        cout << "Failed last action test. Expected " << expected << " but received " << test;
        return false;
}

bool testTotalHP(Pokeman *p, int expected) {
        int test = p->getMaxHealth();
        if (test == expected) {
                return true;
        }
        cout << "Failed max health test. Expected " << expected << " but received " << test;
        return false;
}

bool testTotalHP(Pokeman *p, int expected) {
        int test = p->getMaxHealth();
        if (test == expected) {
                return true;
        }
        cout << "Failed max health test. Expected " << expected << " but received " << test;
        return false;
}

bool testGetAttack(Pokeman *p, TinyAttack *expected[]) {
	int i;
	TinyAttack *test;
	for (i=0; expected[i] != "NULL") {
        	test = p->getMaxHealth();
	}
        if (test == expected) {
                return true;
        }
        cout << "Failed max health test. Expected " << expected << " but received " << test;
        return false;
}



int main(int args, char** argv) {

	TinyAttack *t1 = new TinyAttack("Cool Attack", 12);
	TinyAttack *t2 = new TinyAttack("Hot Attack", 20);

	Pokeman p(50, 70, t1, t2);

	// Test copy constructor
	Pokeman p2 = p;

	p.print();
	p2.print();

	return 0;
}
