//============================================================================
// Name        : cs4511.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>

#include "State.h"

using namespace std;

bool testStateEval(State *s, int expected) {
	if (s->stateEval() == expected) { return true;}
	cout << "Failed stateEval() test. Expected: " << expected << ", but received: " << s->stateEval() << endl;
	return false;
}

bool testGetActive(State *s, Pokeman *expected) {
	if (s->getActivePokemon()->equals(*expected)) { return true;}
	cout << "Failed getActive test. Expected: " << endl;
	expected->print();
	cout << "Received: " << endl;
	s->getActivePokemon()->print();
	return false;
}

bool testGetPassive(State *s, Pokeman *expected) {
        if (s->getPassivePokemon()->equals(*expected)) { return true;}
        cout << "Failed getActive test. Expected: " << endl;
        expected->print();
        cout << "Received: " << endl;
        s->getActivePokemon()->print();
        return false;
}

void runTests() {
        TinyAttack *ta = new TinyAttack("damage", -5, 25, 10);
        Pokeman *p = new Pokeman(25, 25, ta, ta, ta, ta);
        Pokeman *p2 = new Pokeman(10, 10, ta, ta, ta, ta);
        State *s = new State(p, p2, 0);
        double testsRun = 0;
        double testsPassed = 0;

	cout << "Running test 1" << endl;
	testsRun++;
	if(testStateEval(s, 0)) {
		testsPassed++;
	}

	cout << "Running test 2" << endl;
	testsRun++;
	if(testGetActive(s, p)) {
		testsPassed++;
	}

        cout << "Running test 3" << endl;
        testsRun++;
        if(testGetPassive(s, p2)) {
                testsPassed++;
        }

	cout << testsRun << " tests run. " << testsPassed << " passed. Pass rate: " << testsPassed/testsRun * 100 << "%" << endl;
}

int main(int args, char** argv) {
	runTests();
return 0;
}
