
#include <iostream>
#include <string>

#include "TinyAttack.h"


bool testType(TinyAttack *ta, string expected) {
	if(ta->getType() == expected) {
                return true;
        }
        else {
                cout << "Failed typecheck. Expected " << expected << ", received " << ta->getType() << endl;
		return false;
        }
}

bool testPower(TinyAttack *ta, int expected) {
	if(ta->getPower() == expected) {
		return true;
	}
	else {
		cout << "Failed power check. Expected " << expected << ", received " << ta->getPower() << endl;
                return false;
	}
}

bool testPP(TinyAttack *ta, int expected) {
 	if(ta->getPP() == expected) {
                return true;
        }
        else {
                cout << "Failed pp (or use) check. Expected " << expected << ", received " << ta->getPP() << endl;
                return false;
        }
}

bool testSpeed(TinyAttack *ta, int expected) {
        if(ta->getSpeed() == expected) {
                return true;
        }
        else {
                cout << "Failed speed check. Expected " << expected << ", received " << ta->getSpeed() << endl;
                return false;
        }
}

bool testUse(TinyAttack *ta) {
        int prePP = ta->getPP();
	if(prePP == 0) {
                return false;
        }
	ta->use();
	return testPP(ta, prePP - 1);
}

void runTests(string type, int power,int pp, int speed) {
	double testsRun = 0;
	double testsPassed = 0;
	int round;

	TinyAttack *ta = new TinyAttack(type, power, pp, speed);
	TinyAttack *taCopy = new TinyAttack(type, power, pp, speed);
	TinyAttack *wrongType = new TinyAttack("test", power, pp, speed);
	TinyAttack *wrongPower = new TinyAttack(type, power + 1, pp, speed);
	TinyAttack *wrongSpeed = new TinyAttack(type, power, pp, speed * 2);

	cout << "---------------------------------------------------------" << endl;
	cout << "Running tests on: " << endl;
	ta->print();
	cout << "*********************************************************" << endl;
	
	testsRun++;
	if(testType(ta, type)) {
		testsPassed++;
	}

	testsRun++;
	if(testPower(ta, power)) {
		testsPassed++;
	}

	testsRun++;
	if(testPP(ta, pp)) {
		testsPassed++;
	}

	testsRun++;
	if(testSpeed(ta, speed)) {
		testsPassed++;
	}
	
	testsRun++;
	if(testUse(ta)) {
		testsPassed++;
	}

	testsRun++;
	if(ta->equals(taCopy) && !ta->equals(wrongType) && !ta->equals(wrongPower) && !ta->equals(wrongSpeed)) {
		testsPassed++;
	}
	else cout << "failed equality test" << endl;
	
	
	round = testsPassed/testsRun * 100;
	cout << "Passed " << testsPassed << " out of " << testsRun << "! Pass Rate: " << round << "%" << endl;
	cout << "********************************************************" << endl;

	delete ta;
	delete taCopy;
	delete wrongType;
	delete wrongPower;
	delete wrongSpeed;
}

int main(int args, char** argv) {

	cout <<"Creating tests..." << endl;
	runTests("damage", -5, 25, 5);
	runTests("heal", 10, 5, 20);
	
	return 1;
}

