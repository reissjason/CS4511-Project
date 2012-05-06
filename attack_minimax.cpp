/*
 * attack_minimax.cpp
 *
 *  Created on: May 6, 2012
 *      Author: jason
 */

#include "Tree.h"
#include "TinyAttack.h"
#include "Pokeman.h"
#include "Node.h"
#include "battle.h"
#include "State.h"
#include "minimax.h"
#include "team.h"
#include "attack_minimax.h"
#include "Move.h"

State* run_minimax(battle *sim) {

	Tree<Node<Move >, Move > tree(new Move(0));

	team* player = sim->get_player();
	team* opponent = sim->get_opponent();

	Pokeman* attacker = player->get_lead();
	Pokeman* defender = opponent->get_lead();

	// Add player attacks in first level
	//cout << "player nodes" << endl;
	for (int i=1; i<=4; i++) {
	//	cout << "Add " << attacker->get_name() << " : " << attacker->getAttack(i)->get_name() << endl;
		tree.addChild(new Node<Move>(new Move(attacker, attacker->getAttack(i), 0)));
	}
	// Add player switch options
	for (int i=1; i<=3; i++) {
		//cout << "can I add " << player->get_bench(i)->get_name() << " who is " <<  (player->get_bench(i)->isAlive() == true ? "" : "not") <<  " alive" << endl;
		if (player->get_bench(i) != NULL && player->get_bench(i)->get_name().compare(attacker->get_name()) != 0 && player->get_bench(i)->isAlive()) {
		//	cout << "Add switch " << player->get_bench(i)->get_name() << endl;
			tree.addChild(new Node<Move>(new Move(player->get_bench(i), NULL, 0)));
		}
	}

	Node<Move> *temp = tree.getChildren();

	//cout << "opponent nodes" << endl;
	while (temp != NULL) {
		// Add opponent attacks in first level
		for (int i=1; i<=4; i++) {
			int move_val;
			if (temp->getValue()->getAttack() != NULL) {
				move_val = sim->calculate_damage(temp->getValue()->getAttack(), temp->getValue()->getPokeman(), defender);
	//			cout << "Add " << defender->get_name() << " : " << defender->getAttack(i)->get_name() << endl;
				temp->addChild(new Node<Move>(new Move(attacker, temp->getValue()->getAttack(), move_val)));
			} else {
				// we are calculating a switch move so find the max damage if we switch
				int best_val = INT_MIN;
				Pokeman* switch_to = temp->getValue()->getPokeman();
				for (int j=1; j<=4; j++) {
					int curr_val = sim->calculate_damage(switch_to->getAttack(j), temp->getValue()->getPokeman(), defender);
					if (curr_val > best_val) {
						best_val = curr_val;
					}
				}
//				cout << "Add switch " << switch_to->get_name() << endl;
				temp->addChild(new Node<Move>(new Move(switch_to, NULL, best_val)));
			}
		}
		// Add opponent switch options but we don't care about the potential switch so keep value INT_MAX
//		for (int i=1; i<=3; i++) {
//			if (opponent->get_bench(i) != NULL && opponent->get_bench(i)->get_name().compare(defender->get_name()) != 0) {
//				cout << "Add " << player->get_bench(i)->get_name() << endl;
//				temp->addChild(new Node<Move>(new Move(player->get_bench(i), NULL, INT_MAX)));
//			}
//		}

		temp = temp->getNext();
	}


	Node<Move>* result = minimax(&tree);

	cout << "current pkmn " << player->get_lead()->get_name() << endl;
	cout << "suggest using " << result->getValue()->getPokeman()->get_name() << endl;

	int attack_num = 0;

	if (result->getValue()->getAttack() != NULL) {
		cout << "with attack " << result->getValue()->getAttack()->get_name() << endl;
		// find the action number
		for (int i=1; i<=4; i++) {
		//	cout << "is it " << attacker->getAttack(i)->get_name() << endl;
			if (attacker->getAttack(i)->get_name().compare(result->getValue()->getAttack()->get_name()) == 0) {
				attack_num = i;
		//		cout << "yep" << endl;
				break;
			}
		//	cout << "nope" << endl;
		}
	}

	return new State(result->getValue()->getPokeman(), attack_num);

}
