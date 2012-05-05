//============================================================================
// Name        : turn_test.cpp
// Author      : alexander koenen
// Version     : 0
// Copyright   : 
// Description : Test turns 
//============================================================================


#include <iostream>
#include <cstdlib>

#include "Turn.h"
#include "Node.h"
#include "Tree.h"
#include "turn_minimax.h"
#include "team.h"
#include "battle.h"
#include "type.h"
#include "list.h"

#define USE_ATTACK_1 1
#define USE_ATTACK_2 2
#define USE_ATTACK_3 3
#define USE_ATTACK_4 4
#define SWITCH1 5
#define SWITCH2 6
#define SWITCH3 7
#define NUM_OF_ACTIONS 4
#define INVALID -2
#define MAX_DEPTH 2 


using namespace std;
int count = 0;
void generateSuccessors(Node<Turn>* parent, int depth) {
	if (depth > MAX_DEPTH) { return; }
	if (parent == NULL) {
		cout << "NULL value passed to Successor Generation" << endl;
	}
	int mySelectedAction = 1;
	int hisSelectedAction = 1;
	
	for (mySelectedAction = USE_ATTACK_1; mySelectedAction <= NUM_OF_ACTIONS; mySelectedAction++) {
		for(hisSelectedAction = USE_ATTACK_1; hisSelectedAction <= NUM_OF_ACTIONS; hisSelectedAction++) {
			count++;
			cout << count << ": " << "Using " << mySelectedAction << ", " << hisSelectedAction << " at depth " << depth << endl;
			Turn *nextTurn = parent->getValue()->next(mySelectedAction, hisSelectedAction);
			if (nextTurn != NULL) {
				Node<Turn>* child = new Node<Turn>(nextTurn);
				if( child->getValue()->isValid() ) {
					parent->addChild(child);
					if(!child->getValue()->isOver()) {
						generateSuccessors(child, depth + 1);
					}
				}
				else delete child; //Invalid children are deleted, as is the Spartan tradition.
			}
		}
	}
}


State *buildAnswer(Node<Turn>* parent, int minimaxValue) {
	Node<Turn>* temp = parent->getChildren();
	State *ans;
	while(temp != NULL) {
//cout << "active pokemon = " << temp->getValue()->getState1()->getActivePokemon()->get_name() << endl;
//cout << "myPokemon = " << temp->getValue()->getState1()->myPokemon->get_name() << endl;
//cout << "getMinimaxValue = " << temp->getMinimaxValue() << endl;
//cout << "minimax value = " << minimaxValue << endl << endl;
		if(temp->getMinimaxValue() == minimaxValue) {

			if (temp->getValue()->getState1()->getActivePokemon()->equals(*temp->getValue()->getState1()->myPokemon)){
				ans = new State(*temp->getValue()->getState1());
cout << "ans->myPokemon->get_name() = " << ans->myPokemon->get_name() << endl;
			}
			else ans = new State(*temp->getValue()->getState2());
			return ans;
		}
	temp = temp->getNext();
	}
cout << "here" << endl;
}

int main(int args, char** argv) {
  list * alist = new list();
  alist->construct_list();

  TinyAttack * charizard_1 = new TinyAttack(*alist->string_to_attack("flare blitz"));
  TinyAttack * charizard_2 = new TinyAttack(*alist->string_to_attack("thunderpunch"));
  TinyAttack * charizard_3 = new TinyAttack(*alist->string_to_attack("dragon dance"));
  TinyAttack * charizard_4 = new TinyAttack(*alist->string_to_attack("earthquake"));

  TinyAttack * roserade_1 = new TinyAttack(*alist->string_to_attack("giga drain"));
  TinyAttack * roserade_2 = new TinyAttack(*alist->string_to_attack("sludge bomb"));
  TinyAttack * roserade_3 = new TinyAttack(*alist->string_to_attack("sleep powder"));
  TinyAttack * roserade_4 = new TinyAttack(*alist->string_to_attack("synthesis"));

  TinyAttack * slowbro_1 = new TinyAttack(*alist->string_to_attack("scald"));
  TinyAttack * slowbro_2 = new TinyAttack(*alist->string_to_attack("slack off"));
  TinyAttack * slowbro_3 = new TinyAttack(*alist->string_to_attack("psychic"));
  TinyAttack * slowbro_4 = new TinyAttack(*alist->string_to_attack("toxic"));

  TinyAttack * ambipom_1 = new TinyAttack(*alist->string_to_attack("aerial ace"));
  TinyAttack * ambipom_2 = new TinyAttack(*alist->string_to_attack("double hit"));
  TinyAttack * ambipom_3 = new TinyAttack(*alist->string_to_attack("fake out"));
  TinyAttack * ambipom_4 = new TinyAttack(*alist->string_to_attack("low sweep"));

  TinyAttack * porygon2_1 = new TinyAttack(*alist->string_to_attack("ice beam"));
  TinyAttack * porygon2_2 = new TinyAttack(*alist->string_to_attack("thunderbolt"));
  TinyAttack * porygon2_3 = new TinyAttack(*alist->string_to_attack("recover"));
  TinyAttack * porygon2_4 = new TinyAttack(*alist->string_to_attack("toxic"));

  TinyAttack * yanmega_1 = new TinyAttack(*alist->string_to_attack("giga drain"));
  TinyAttack * yanmega_2 = new TinyAttack(*alist->string_to_attack("bug buzz"));
  TinyAttack * yanmega_3 = new TinyAttack(*alist->string_to_attack("air slash"));
  TinyAttack * yanmega_4 = new TinyAttack(*alist->string_to_attack("protect"));

  int * stat_ptr;
//team1
  stat_ptr = alist->stat_cast(297, 293, 193, 228, 206, 299);
  Pokeman * charizard = new Pokeman("charizard", stat_ptr, "fire", "flying", "blaze", charizard_1, charizard_2, charizard_3, charizard_4);

  Pokeman * charizard2 = new Pokeman("charizard", stat_ptr, "fire", "flying", "blaze", charizard_1, charizard_2, charizard_3, charizard_4);
//  charizard->add_item("life orb");

  stat_ptr = alist->stat_cast(261, 158, 146, 383, 247, 279);
  Pokeman * roserade = new Pokeman("roserade", stat_ptr, "grass", "poison", "natural cure", roserade_1, roserade_2, roserade_3, roserade_4);
//  roserade->add_item("big root");

  stat_ptr = alist->stat_cast(393, 167, 348, 240, 196, 96);
  Pokeman * slowbro = new Pokeman("slowbro", stat_ptr, "water", "psychic", "regenerator", slowbro_1, slowbro_2, slowbro_3, slowbro_4);
//  slowbro->add_item("leftover");

//team2
  stat_ptr = alist->stat_cast(292, 328, 168, 140, 168, 329);
  Pokeman * ambipom = new Pokeman("ambipom", stat_ptr, "normal", "none", "technician", ambipom_1, ambipom_2, ambipom_3, ambipom_4);
//  ambipom->add_item("gem flying");

  stat_ptr = alist->stat_cast(308, 149, 208, 325, 148, 317);
  Pokeman * yanmega = new Pokeman("yanmega", stat_ptr, "bug", "flying", "speed boost", yanmega_1, yanmega_2, yanmega_3, yanmega_4);
//  yanmega->add_item("wise glasses");

  stat_ptr = alist->stat_cast(374, 176, 288, 246, 244, 156);
  Pokeman * porygon2 = new Pokeman("porygon2", stat_ptr, "normal", "none", "analytic", porygon2_1, porygon2_2, porygon2_3, porygon2_4);
//  porygon2->add_item("eviolite");

//  team * laptop = new team(slowbro, charizard, roserade, NULL, NULL, NULL);
//  team * tower = new team(ambipom, yanmega, porygon2, NULL, NULL, NULL);

  team * laptop = new team(charizard, NULL, NULL, NULL, NULL, NULL);
  team * tower = new team(roserade, NULL, NULL, NULL, NULL, NULL);

  battle * sim = new battle(laptop, tower);

//  sim->get_player()->get_lead()->update_hp(259);
//  sim->get_opponent()->get_lead()->update_hp(254);

  battle * sim2 = new battle(*sim);

/*
	TinyAttack* ta = new TinyAttack("damage", -12, 2, 2);
	TinyAttack* ta2 = new TinyAttack("damage", -14, 2, 3);
	TinyAttack *ta3 = new TinyAttack("heal", 2, 2, 5);
	TinyAttack *ta4 = new TinyAttack(*ta);
	TinyAttack *ta5 = new TinyAttack(*ta);
	TinyAttack *ta6 = new TinyAttack(*ta);
  TinyAttack *ta7 = new TinyAttack(*ta);
	TinyAttack *ta8 = new TinyAttack(*ta);
	Pokeman *p = new Pokeman(40,40,ta2,ta,ta5,ta6);
	Pokeman *p2 = new Pokeman(20,20,ta3,ta4,ta7,ta8);
	Pokeman *p3 = new Pokeman(*p);
	Pokeman *p4 = new Pokeman(*p2);

	State *s = new State(p, p2, 0);
	State *s2 = new State(p3, p4, 1);
*/
	State *s = new State(sim, 0);
	State *s2 = new State(sim2, 1);
	Turn *t = new Turn(s, s2);
	//t->print();
//	State *newS = s->nextState(1);
//	State *newS2 = newS->nextState(2);
//	Turn *newT = new Turn(newS, newS2);
	//newT->print();
	cout << "*********************************************************************************************************************" << endl;
	//t->next(1,2)->print();
	Tree<Node<Turn>, Turn> tree(t);
	generateSuccessors(&tree, 0);
	tree.printClass();
  int minimaxValue = turn_minimax(&tree);
	cout << "Minimax Returns: " << minimaxValue << endl;
  State* minimaxRecommends = buildAnswer(&tree, minimaxValue);
//cout << "test = " << minimaxRecommends->myPokemon->get_name() << endl;
	cout << "MINIMAX RECOMMENDS: " << minimaxRecommends->getActionUsed() << endl;
/*
get first attack in chain


State *s = new State(p, p2, 0);
State *s2 = new State(p3, p4, 1);



*/
//cout << tree.getMinimaxValue() << endl;
/*	Node<Turn>* temp = tree.getChildren();
	while(temp != NULL) {
		cout << "Minimax Value: " << endl;
		cout << temp->getMinimaxValue() << endl;
		temp = temp->getNext();
	}
*/
	return 1;
}
