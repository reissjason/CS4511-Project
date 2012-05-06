#include "pkmn.h"
#include "attack.h"
#include "Tree.h"
#include "team.h"
#include "battle.h"
#include "TinyAttack.h"
#include <string>
#include <sstream>
#include <stdio.h>
#include "list.h"

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
list * alist = new list();

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
			//cout << count << ": " << "Using " << mySelectedAction << ", " << hisSelectedAction << " at depth " << depth << endl;
			Turn *nextTurn = parent->getValue()->next(mySelectedAction, hisSelectedAction);
			if (nextTurn != NULL) {
				Node<Turn>* child = new Node<Turn>(nextTurn);
				if( child->getValue()->isValid() ) {
					parent->addChild(child);
					if(!child->getValue()->isOver()) {
						generateSuccessors(child, depth + 1);
					}
				}
				else {
					delete child; //Invalid children are deleted, as is the Spartan tradition.
					child = NULL;
				}
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
				//cout << "ans->myPokemon->get_name() = " << ans->myPokemon->get_name() << endl;
			}
			else ans = new State(*temp->getValue()->getState2());
			return ans;
		}
		temp = temp->getNext();
	}
	cout << "here" << endl;
	return NULL;
}

Pokeman* choose(string);

TinyAttack * attack_list[30];

int * stat_cast(int hp, int atk, int def, int spatk, int spdef, int spd){
	int * ret_val = new int[6];
	ret_val[0] = hp;
	ret_val[1] = atk;
	ret_val[2] = def;
	ret_val[3] = spatk;
	ret_val[4] = spdef;
	ret_val[5] = spd;
	return ret_val;
}

TinyAttack * string_to_attack(string move_name){
	int i;

	cout << "looking for " << move_name << endl;
	for(i = 0; i < ATTACK_LIST_LENGTH; i++){
		//		if(attack_list[i] != NULL)
		//			cout << "is it " << attack_list[i]->get_name() << "?" << endl;

		if(attack_list[i] != NULL && attack_list[i]->get_name().compare(move_name) == 0){
			//			cout << "yep" << endl;
			return attack_list[i];
		}
		//		if(attack_list[i] != NULL)
		//			cout << "nope" << endl;
	}
	return NULL;
}

int have_a_fight() {

	string pokemons[] = { "charizard",
			"roserade",
			"slowbro",
			"ambipom",
			"yanmega",
			"porygon2"
	};

	string choices = "";

	while (choices.length() < 6) {
		int num = rand() % 6;
		stringstream ss;
		ss << num;
		//if (choices.find_first_of(ss.str()) == string::npos)
			choices += ss.str();
	}

	team * laptop = new team(choose(pokemons[(choices[0])-48]),
			choose(pokemons[(choices[1])-48]),
			choose(pokemons[(choices[2])-48]), NULL, NULL, NULL);

	team * tower = new team(choose(pokemons[(choices[3])-48]),
			choose(pokemons[(choices[4])-48]),
			choose(pokemons[(choices[5])-48]), NULL, NULL, NULL);

	cout << "Teams have been chosen!" << endl;
	cout << "Choose your Pokemon!" <<endl;
	cout << "Team 1 : " << laptop->isAlive() << endl;
	cout << pokemons[(choices[0])-48] << endl;
	cout << pokemons[(choices[1])-48] << endl;
	cout << pokemons[(choices[2])-48] << endl;
	cout << endl;
	cout << "Choose your Enemy!" << endl;
	cout << "Team 2 : " << tower->isAlive() << endl;
	cout << pokemons[(choices[3])-48] << endl;
	cout << pokemons[(choices[4])-48] << endl;
	cout << pokemons[(choices[5])-48] << endl;
	cout << endl;

	battle * sim = new battle(laptop, tower);
	battle * sim2 = new battle(*sim);
	cout << "Teams have been made!" << endl;

	TinyAttack *next_move;
	Pokeman * attacker;
	Pokeman * defender;
	cout << "Fight!" << endl;

	int round_num = 1;
	int damage = 0;
	int attack_num = 1;
	bool dont_switch = false;
	bool switched_last_round = false;


	TinyAttack *last_move = NULL;

	while (laptop->isAlive() && tower->isAlive()) {
		State *s = new State(sim, 0);
		State *s2 = new State(sim2, 1);
		Turn *t = new Turn(s, s2);

		cout << "*********************************************************************************************************************" << endl;

		Tree<Node<Turn>, Turn> tree(t);

		attacker = sim->get_player()->get_lead();
		defender = sim->get_opponent()->get_lead();
		cout << "A player has been gotten!" << endl;

		generateSuccessors(&tree, 0);
//		tree.printClass();
		int minimaxValue = turn_minimax(&tree);
		cout << "Minimax Returns: " << minimaxValue << endl;
		State* minimaxRecommends = buildAnswer(&tree, minimaxValue);

		cout << "MINIMAX RECOMMENDS: " << minimaxRecommends->getActionUsed() << endl;
		attack_num = minimaxRecommends->getActionUsed();
		next_move = alist->string_to_attack(attacker->get_attack(attack_num));
		//cout << "test = " << minimaxRecommends->myPokemon->get_name() << endl;
		if (last_move != NULL)
			cout << "last move: " << last_move->get_power() << endl;
		cout << "next move: " << next_move->get_power() << endl;

		if (last_move != NULL && last_move->get_power() >= next_move->get_power()) {
			next_move = last_move;
			dont_switch = true;
		} else {
			dont_switch = false;
		}

		if (!switched_last_round && !dont_switch && minimaxRecommends->myPokemon->get_name().compare(attacker->get_name()) != 0) {
			cout << "switching to " << minimaxRecommends->myPokemon->get_name() << endl;
			sim->get_player()->change_lead(minimaxRecommends->myPokemon);
			attacker = sim->get_player()->get_lead();
			switched_last_round = true;
		} else {
			cout << "That player has an attack!" << endl;
			cout << "look for attack #" << attack_num << endl;
			cout << attacker->get_attack(attack_num) << endl;

			cout << "That attack has power = " << next_move->get_power() << "!" << endl;
			cout << attacker->get_name() << " attacks " << defender->get_name() << " with " << next_move->get_name() << endl;

			damage = sim->calculate_damage(next_move, attacker, defender);
			cout << "damage = " << damage << endl;

			defender->reduce_hp(damage);
			last_move = next_move;
			switched_last_round = false;
		}

		delete minimaxRecommends;



		attack_num = rand() % 4 + 1;
		int poke_num = attack_num - 4;
		cout << "attack_num : " << attack_num << " poke_num : " << poke_num << endl;
		if (attack_num < 5 || tower->get_bench(poke_num)->get_name().compare(defender->get_name()) == 0) {
			if (attack_num >= 5) attack_num -= 3;
			cout << "attack_num : " << attack_num << endl;
			next_move = alist->string_to_attack(defender->get_attack(attack_num));

			cout << defender->get_name() << " attacks " << attacker->get_name() << " with " << next_move->get_name() << endl;
			damage = sim->calculate_damage(next_move, defender, attacker);
			cout << "damage = " << damage << endl;

			attacker->reduce_hp(damage);
		} else {

			cout << "switching to " << tower->get_bench(poke_num)->get_name() << endl;
			tower->change_lead(tower->get_bench(poke_num));

		}
		round_num++;
		cout << "Round " << round_num << endl;
		cout << " " << attacker->get_name() << " hp: " << attacker->get_current_hp() << endl;
		cout << " " << defender->get_name() << " hp: " << defender->get_current_hp() << endl;
		delete s; delete s2; delete t;

		if (round_num > 100)  // too long just call it a tie
			break;
	}

	delete sim;
	delete sim2;

	int ret_val =0;
	if (!tower->isAlive() && !laptop->isAlive()) {
		cout << endl << "There was a tie!" << endl << endl;
		ret_val = 0;
	} else if (tower->isAlive()) {
		cout << endl << "Team 2 wins!" << endl << endl;
		ret_val = 2;
	} else {
		cout << endl << "Team 1 wins!" << endl << endl;
		ret_val = 1;
	}

	delete tower;
	delete laptop;
	return ret_val;
}

int main() {

	alist->construct_list();

	srand(time(NULL));
	int num_of_battles = 1;

	int results[3] = {0,0,0};

	for(int i=0; i<num_of_battles; i++) {
		cout << "Battle " << i+1 << endl;
		int result = have_a_fight();
		results[result]++;
	}

	cout << "Out of " << num_of_battles << " battles there were:" << endl;
	cout << "\t" << results[0] << "\tties" << endl;
	cout << "\t" << results[1] << "\tteam 1 wins" << endl;
	cout << "\t" << results[2] << "\tteam 2 wins" << endl;


	return 0;
}

Pokeman* choose(string name) {
	int * stat_ptr;
	//team1
	Pokeman* choice = NULL;
	if (name == "charizard") {
		TinyAttack * charizard_1 = new TinyAttack(*alist->string_to_attack("flare blitz"));
		TinyAttack * charizard_2 = new TinyAttack(*alist->string_to_attack("thunderpunch"));
		TinyAttack * charizard_3 = new TinyAttack(*alist->string_to_attack("dragon dance"));
		TinyAttack * charizard_4 = new TinyAttack(*alist->string_to_attack("earthquake"));

		stat_ptr = alist->stat_cast(297, 293, 193, 228, 206, 299);
		choice = new Pokeman("charizard", stat_ptr, "fire", "flying", "blaze", charizard_1, charizard_2, charizard_3, charizard_4);
	}

	if (name == "roserade") {
		TinyAttack * roserade_1 = new TinyAttack(*alist->string_to_attack("giga drain"));
		TinyAttack * roserade_2 = new TinyAttack(*alist->string_to_attack("sludge bomb"));
		TinyAttack * roserade_3 = new TinyAttack(*alist->string_to_attack("sleep powder"));
		TinyAttack * roserade_4 = new TinyAttack(*alist->string_to_attack("synthesis"));

		stat_ptr = alist->stat_cast(261, 158, 146, 383, 247, 279);
		choice = new Pokeman("roserade", stat_ptr, "grass", "poison", "natural cure", roserade_1, roserade_2, roserade_3, roserade_4);
		//  roserade->add_item("big root");
	}

	if (name == "slowbro") {
		TinyAttack * slowbro_1 = new TinyAttack(*alist->string_to_attack("scald"));
		TinyAttack * slowbro_2 = new TinyAttack(*alist->string_to_attack("slack off"));
		TinyAttack * slowbro_3 = new TinyAttack(*alist->string_to_attack("psychic"));
		TinyAttack * slowbro_4 = new TinyAttack(*alist->string_to_attack("toxic"));

		stat_ptr = alist->stat_cast(393, 167, 348, 240, 196, 96);
		choice = new Pokeman("slowbro", stat_ptr, "water", "psychic", "regenerator", slowbro_1, slowbro_2, slowbro_3, slowbro_4);
		//  slowbro->add_item("leftover");

	}

	if (name == "ambipom") {
		TinyAttack * ambipom_1 = new TinyAttack(*alist->string_to_attack("aerial ace"));
		TinyAttack * ambipom_2 = new TinyAttack(*alist->string_to_attack("double hit"));
		TinyAttack * ambipom_3 = new TinyAttack(*alist->string_to_attack("fake out"));
		TinyAttack * ambipom_4 = new TinyAttack(*alist->string_to_attack("low sweep"));
		//team2
		stat_ptr = alist->stat_cast(292, 328, 168, 140, 168, 329);
		choice = new Pokeman("ambipom", stat_ptr, "normal", "none", "technician", ambipom_1, ambipom_2, ambipom_3, ambipom_4);
		//  ambipom->add_item("gem flying");
	}

	if (name == "yanmega") {
		TinyAttack * yanmega_1 = new TinyAttack(*alist->string_to_attack("giga drain"));
		TinyAttack * yanmega_2 = new TinyAttack(*alist->string_to_attack("bug buzz"));
		TinyAttack * yanmega_3 = new TinyAttack(*alist->string_to_attack("air slash"));
		TinyAttack * yanmega_4 = new TinyAttack(*alist->string_to_attack("protect"));

		stat_ptr = alist->stat_cast(308, 149, 208, 325, 148, 317);
		choice = new Pokeman("yanmega", stat_ptr, "bug", "flying", "speed boost", yanmega_1, yanmega_2, yanmega_3, yanmega_4);
		//  yanmega->add_item("wise glasses");
	}

	if (name == "porygon2") {
		TinyAttack * porygon2_1 = new TinyAttack(*alist->string_to_attack("ice beam"));
		TinyAttack * porygon2_2 = new TinyAttack(*alist->string_to_attack("thunderbolt"));
		TinyAttack * porygon2_3 = new TinyAttack(*alist->string_to_attack("recover"));
		TinyAttack * porygon2_4 = new TinyAttack(*alist->string_to_attack("toxic"));

		stat_ptr = alist->stat_cast(374, 176, 288, 246, 244, 156);
		choice = new Pokeman("porygon2", stat_ptr, "normal", "none", "analytic", porygon2_1, porygon2_2, porygon2_3, porygon2_4);
	}

	if (choice != NULL)
		cout << "Picked " << choice->get_name() << " : " << choice->get_current_hp() << " : isAlive() = " << choice->isAlive() << endl;
	return choice;
}



