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
	cout << "Failed hp test. Expected " << expected << " but received " << p->getHealth() << endl;
	return false;
}

bool testLastAction(Pokeman *p, int expected) {
	int test = p->getLastAction();
        if (test == expected) {
                return true;
        }
        cout << "Failed last action test. Expected " << expected << " but received " << test << endl;
        return false;
}

bool testTotalHP(Pokeman *p, int expected) {
        int test = p->getMaxHealth();
        if (test == expected) {
                return true;
        }
        cout << "Failed max health test. Expected " << expected << " but received " << test  << endl;
        return false;
}

bool testUsedAction(Pokeman *p, bool expected, int action) {
        bool test = p->usedAction(action);
        if (test == expected ) {
                return true;
        }
        cout << "Failed usedAction test. Expected " << expected << " but received " << test << endl;
        return false;
}

bool testGetAttack(Pokeman *p, TinyAttack *expected[]) {
	int i;
	TinyAttack *test;
	bool ans = true;
	for (i=0; i < 4; i++) {
        	test = p->getAttack(i + 1);
		
	        if (!test->equals(expected[i]) && test != NULL) {
        	        ans = false;
			cout << "Attack expected: " << endl; 
			expected[i]->print();
			cout << " but recieved: " << endl; 
			test->print();
	        }
		if (test == NULL) {
			cout << "received NULL attack" << endl;
		}
	}
	if (ans == true) {return ans;}
        cout << "Failed getAttack test." << endl;
        return false;
}

bool testCopyConstructor(Pokeman *p) {
	Pokeman *p2 = new Pokeman(*p);
	if (!testTotalHP(p2, p->getMaxHealth())) {return false;}
	if (!testHP(p2, p->getHealth())) {return false;}
	TinyAttack *attacks[4];
	for (int i = 0; i < 4; i++) {
		attacks[i] = p->getAttack(i + 1);
	}
	if (!testGetAttack(p2, attacks)) {delete p2; return false;}
	delete p2;
	return true;
}

bool testChangeHealth(Pokeman *p, int expected, int modify) {
	p->changeHealth(modify);
	int test = p->getHealth();
	if (test == expected) {
                return true;
        }
        cout << "Failed changeHealth test. Expected " << expected << " but received " << test << endl;
        return false;
}

double runTests() {
	TinyAttack *t1 = new TinyAttack("damage", -10, 5, 5);
	TinyAttack *t2 = new TinyAttack("damage", -15, 2, 2);
	TinyAttack *t3 = new TinyAttack("heal", 5, 0, 2);
	TinyAttack *t4 = new TinyAttack("damage", -2, 25, 10);
	TinyAttack *Tarray[4];
	Tarray[0] = t1;
	Tarray[1] = t2;
	Tarray[2] = t3;
	Tarray[3] = t4;
	Pokeman *p = new Pokeman(25, 25, t1, t2, t3, t4);
	double testsRun = 0;
	double testsPassed = 0;

	cout << "Running test 1" << endl;
	testsRun++;
	if (testHP(p, 25)) {
		testsPassed++;
	}

        cout << "Running test 2" << endl;
	testsRun++;
	if (testTotalHP(p, 25)) {
		testsPassed++;
	}

        cout << "Running test 3" << endl;
	testsRun++;
	if (testChangeHealth(p, 20, -5)) {
		testsPassed++;
	}

        cout << "Running test 4" << endl;
	testsRun++;
	if (testGetAttack(p, Tarray)) {
		testsPassed++;
	}

        cout << "Running test 5" << endl;
	testsRun++;
	if (testUsedAction(p, true, 1)) {
		testsPassed++;
	}

        cout << "Running test 6" << endl;
	testsRun++;
	if (testUsedAction(p, false, 3)) {
		testsPassed++;
	}

        cout << "Running test 7" << endl;
	testsRun++;
	if (testCopyConstructor(p)) {
		testsPassed++;
	}
	
	cout << "Running test 8" << endl;
	testsRun++;
	Pokeman *p2 = new Pokeman(*p);
	if (p2->equals(*p)) {
		testsPassed++;
	}

	cout << "Running test 9" << endl;
	testsRun++;
	Pokeman *p3 = new Pokeman(10, 10, t1, t1, t2, t2);
	if (!p3->equals(*p)) {
		testsPassed++;
	}

	delete p; //Also deletes all the attacks.

	cout << "Tests run: " << testsRun << ". Tests passed: " << testsPassed << ". Pass rate: " << testsPassed/testsRun * 100 << "%" << endl;
}

int main(int args, char** argv) {

	TinyAttack *t1 = new TinyAttack("Cool Attack", 12, 5, 5);
	TinyAttack *t2 = new TinyAttack("Hot Attack", 20, 5, 5);
	
	runTests();

	return 0;
}
