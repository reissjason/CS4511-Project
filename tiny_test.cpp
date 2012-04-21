#include "TinyAttack.h"
//#include "tinyAttack.cpp"
#include "Pokeman.h"
//#include "pokeman.cpp"
#include "State.h"
//#include "State.cpp"

#include <iostream>
#include <string.h>

using namespace std;

int main(int args, char** argv) {
	cout << "*****************INITALIZING*TINY*TEST****************" << endl;
	cout << "*****************CREATING*TINY*ATTACK*****************" << endl;
	int i = 0;
	string damage = "damage";
	int power;
	TinyAttack* ta = new TinyAttack(damage, -5);
	cout << "****************TINY*ATTACK*CREATED*******************" << endl;
	power = ta->getPower();
	cout << "****************TINY*ATTACK*TYPE: " + ta->getType() + "*********" << endl;
	cout << "****************TINY*ATTACK*TYPE: " << power << "************" <<  endl;
	cout << "******************************************************************" << endl;
	cout << "*****************CREATING*POKEMAN*****************" << endl;
	Pokeman* p = new Pokeman(10, 10, ta, ta);
	cout << "****************POKEMAN*CREATED*******************" << endl;
	cout << "****************POKEMAN*HEALTH: " << p->getHealth() << "*********************" << endl;
	for(i=1; i < 3; i++){
		cout << "****************POKEMAN*ATTACK*"<< i << "*TYPE: " << p->getAttack(i)->getType() << "********************************" << endl;
		cout << "****************POKEMAN*ATTACK*"<< i << "*POWER: " << p->getAttack(i)->getPower() << "*********************************" << endl;
	}
	cout << "************************CLONING*TEH*POKEMANS*******************************" << endl;
	Pokeman* clone = p->clone();
	cout << "************************CLONING*COMPLETE*******************************" << endl;
	cout << "****************POKEMAN*HEALTH: " << clone->getHealth() << "*********************" << endl;
        for(i=1; i < 3; i++){
                cout << "****************POKEMAN*ATTACK*"<< i << "*TYPE: " << clone->getAttack(i)->getType() << "********************************" << endl;
                cout << "****************POKEMAN*ATTACK*"<< i << "*POWER: " << clone->getAttack(i)->getPower() << "*********************************" << endl;
        }
	cout << "************************DAMAGING*CLONE**********************************" << endl;
	bool cloneAlive = clone->changeHealth(-5);
	if (cloneAlive == false) {
		cout << "********************TEH*CLONE*DIED**************************" 	<< endl;
	}
	cout << "************************TEH*CLONE'S*HEALTH: " << clone->getHealth() << "***********************" << endl;
	cout << "***********************TEH*ORIGINAL'S*HEALTH: " << p->getHealth() << "***************************" << endl;
	cout << "**************************BEGINNING*STATE*TEST***************ALABAMA,ALASKA,ARIZONA,ARKANSAS,CALIFORNIA,COLORADO,CONNETICUT..." << endl;
	State* s = new State(p, clone, 1);
	while(!s->isOver){
	State* tempState = s->nextState();
	//Delete State attached to s?
	s = tempState;
	}
	return i;
}
