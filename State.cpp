#include "State.h"
#include "Tree.h"
#include "Node.h"
#include <string>
#include <ctime>
#include <stdlib.h>
#include <iostream>

#define NO_ATTACK 0
#define USE_ATTACK_1 1
#define USE_ATTACK_2 2
#define USE_ATTACK_3 3
#define USE_ATTACK_4 4
#define SWITCH1 5
#define SWITCH2 6
#define SWITCH3 7
#define NUM_OF_ACTIONS 5 
#define MATCH_OVER -1
#define INVALID -2
#define MY_TURN 1
#define THAT_BASTARDS_TURN -1

State::State(battle* s_battle, int turn){
  this->global = s_battle;
	this->myPokemon = s_battle->get_player()->get_lead();
	this->thatBastardsPokemon = s_battle->get_opponent()->get_lead();
	if (turn == MATCH_OVER){
		this->whoseTurn = MATCH_OVER;
		this->isOver = true;
	}
	else if(turn == INVALID) {
		this->whoseTurn = INVALID;
		this->isOver = true;
	}
	else {
		this->whoseTurn = turn;
		this->isOver = false;
	}
//cout<<"State value = " << this->stateEval() << endl;
	this->value = this->stateEval();
  this->actionUsed = 101;

}

State::State(Pokeman* pokeman1, Pokeman* pokeman2, int turn){
	this->myPokemon = pokeman1;
	this->thatBastardsPokemon = pokeman2;
	if (turn == MATCH_OVER){
		this->whoseTurn = MATCH_OVER;
		this->isOver = true;
	}
	else if(turn == INVALID) {
		this->whoseTurn = INVALID;
		this->isOver = true;
	}
	else {
		this->whoseTurn = turn;
		this->isOver = false;
	}
	this->value = this->stateEval();
  this->actionUsed = 101;
}

State::State(int *i) {
	this->value = *i;
}

State::~State() {
	delete this->myPokemon;
	delete this->thatBastardsPokemon;
}

State::State(Pokeman* winner){
	this->myPokemon = winner;
	this->isOver = true;
}

State::State(State &s) {
	this->myPokemon = new Pokeman(*s.myPokemon);
	this->thatBastardsPokemon = new Pokeman(*s.thatBastardsPokemon);
  this->global = new battle(*s.global);
	this->whoseTurn = s.whoseTurn;
	this->isOver = s.isOver;
	this->value = s.value;
	this->actionUsed = s.getActionUsed();
}

void State::setActionUsed(int i) {
	this->actionUsed = i;
}

int State::getActionUsed() {
  return this->actionUsed;
}

bool State::useAttack(Pokeman* userPokemon, Pokeman* targetPokemon, TinyAttack* attack){
  int damage;
  string effect;
	bool stillAlive;

  if(targetPokemon->get_protect()){
    return true;
  }else {
    damage = global->calculate_damage(attack, userPokemon, targetPokemon);
  }
//cout << "user = " << userPokemon->get_name() << endl;
//cout << "target = " << targetPokemon->get_name() << endl;
//cout << "move = " << attack->get_name() << endl;
//cout << "damage = " << damage << endl;

  if(targetPokemon->get_current_hp() - damage <= 0){
    targetPokemon->update_hp(0);
    targetPokemon->set_status("fainted");
  }else targetPokemon->update_hp(targetPokemon->get_current_hp() - damage);

//cout<<"targetPokemon->get_current_hp() = " << targetPokemon->get_current_hp()  << endl;

  effect.assign(attack->get_effect());

  if(effect.compare("recoil") == 0){
    userPokemon->update_hp( userPokemon-> get_current_hp() - (damage * attack->get_effect_chance()) );
  }
  if(effect.compare("drain") == 0){
    userPokemon->update_hp( userPokemon-> get_current_hp() + (damage * attack->get_effect_chance()) );
  }
  if(effect.compare("double") == 0){
    if(targetPokemon->get_current_hp() - damage <= 0){
      targetPokemon->update_hp(0);
      targetPokemon->set_status("fainted");
    }else targetPokemon->update_hp(targetPokemon->get_current_hp() - damage);
  }
//this is where we call calculate_damage
//if checks for recoil, flinch, double
  
  if(global->get_player()->get_lead()->get_name().compare(targetPokemon->get_name()) == 0 ){
  	if(global->get_player()->get_fainted() > 0){
      stillAlive = true;
    }
  }else if(global->get_opponent()->get_fainted() > 0){
      stillAlive = true;
  }
	return stillAlive;
}

Pokeman* State::getActivePokemon(){
	switch(this->whoseTurn) {
		case MY_TURN: return this->myPokemon;
		case THAT_BASTARDS_TURN: return this->thatBastardsPokemon;
		default: cout << "Attempting to get active pokemon on invalid state." << endl;
	}
}

Pokeman* State::getPassivePokemon(){
  switch(this->whoseTurn) {
   case MY_TURN: return this->thatBastardsPokemon;
   case THAT_BASTARDS_TURN: return this->myPokemon;
   default: cout << "Attempting to get passive pokemon on invalid state." << endl;
  }
}

State* State::nextState(int selectedAction){
	if(selectedAction > SWITCH3 || selectedAction < 0) {
		cout << "nextState() function called with improper value for Selected Action: " << selectedAction << endl;
		cout << "This value must be (attack) 1, (attack) 2, (attack) 3, (attack) 4, or 5(switch)" << endl;
	}
//  Pokeman* myNewPokeman = new Pokeman(*myPokemon);
//  Pokeman* hisNewPokeman = new Pokeman(*thatBastardsPokemon);
  Pokeman* switchPokemon;
  battle* newBattle = new battle(*global);
  int hisHealth;
  int myHealth;
  State* newState;
  TinyAttack attack;
  bool continueMatch;
	bool usedAction;
	int used = selectedAction;
	string action;
	Pokeman* active = NULL;
	Pokeman* passive = NULL;
  bool switchedPokemon;

//cout << "whoseturn? " << this->whoseTurn << endl;

  cout << "Pokemans! use attack number " << selectedAction << "!!!" << endl;
  if(this->whoseTurn == MY_TURN && selectedAction != SWITCH1 && selectedAction != SWITCH2 && selectedAction != SWITCH3){
//cout << "check" <<endl;
		active = newBattle->get_player()->get_lead();
		passive = newBattle->get_opponent()->get_lead();
	}
  else if(selectedAction != SWITCH1 && selectedAction != SWITCH2 && selectedAction != SWITCH3){
//cout << "other check" <<endl;
		active = newBattle->get_opponent()->get_lead();
		passive = newBattle->get_player()->get_lead();
	}

	if (selectedAction == SWITCH1) {
    if(this->whoseTurn == MY_TURN){
//cout<<"my turn"<<endl;
  		switchedPokemon = newBattle->get_player()->change_lead(newBattle->get_player()->get_bench(1));
      switchPokemon = new Pokeman(*newBattle->get_player()->get_lead());
      if(switchedPokemon){
        newState = new State(newBattle, (this->whoseTurn + 1) % 2);
        newState->setActionUsed(selectedAction);
        return newState;
      }
      else{
        newState = new State(newBattle, INVALID);
        newState->setActionUsed(selectedAction);
        return newState;
      }
    }else{
  		switchedPokemon = newBattle->get_opponent()->change_lead(newBattle->get_opponent()->get_bench(1));
      switchPokemon = new Pokeman(*(newBattle->get_opponent()->get_lead()));

      if(switchedPokemon){
        newState = new State(newBattle, (this->whoseTurn + 1) % 2);
        newState->setActionUsed(selectedAction);
        return newState;
      }
      else{
        newState = new State(newBattle, INVALID);
        newState->setActionUsed(selectedAction);
        return newState;
      }
    }
	}else if (selectedAction == SWITCH2) {
    if(this->whoseTurn == MY_TURN){
  		switchedPokemon = newBattle->get_player()->change_lead(newBattle->get_player()->get_bench(2));
      switchPokemon = new Pokeman(*newBattle->get_player()->get_lead());
      if(switchedPokemon){
        newState = new State(newBattle, (this->whoseTurn + 1) % 2);
        newState->setActionUsed(selectedAction);
        return newState;
      }
      else{
        newState = new State(newBattle, INVALID);
        newState->setActionUsed(selectedAction);
        return newState;
      }
    }else{
  		switchedPokemon = newBattle->get_opponent()->change_lead(newBattle->get_opponent()->get_bench(2));
      switchPokemon = new Pokeman(*newBattle->get_opponent()->get_lead());
      if(switchedPokemon){
        newState = new State(newBattle, (this->whoseTurn + 1) % 2);
        newState->setActionUsed(selectedAction);
        return newState;
      }
      else{
        newState = new State(newBattle, INVALID);
        newState->setActionUsed(selectedAction);
        return newState;
      }
    }
	}else if (selectedAction == SWITCH3) {
    if(this->whoseTurn == MY_TURN){
  		switchedPokemon = newBattle->get_player()->change_lead(newBattle->get_player()->get_bench(3));
      switchPokemon = new Pokeman(*newBattle->get_player()->get_lead());
      if(switchedPokemon){
        newState = new State(newBattle, (this->whoseTurn + 1) % 2);
        newState->setActionUsed(selectedAction);
        return newState;
      }
      else{
        newState = new State(newBattle, INVALID);
        newState->setActionUsed(selectedAction);
        return newState;
      }
    }else{
  		switchedPokemon = newBattle->get_opponent()->change_lead(newBattle->get_opponent()->get_bench(3));
      switchPokemon = new Pokeman(*newBattle->get_opponent()->get_lead());
      if(switchedPokemon){
        newState = new State(newBattle, (this->whoseTurn + 1) % 2);
        newState->setActionUsed(selectedAction);
        return newState;
      }
      else{
        newState = new State(newBattle, INVALID);
        newState->setActionUsed(selectedAction);
        return newState;
      }
    }
	}
  else if(selectedAction == NO_ATTACK){
    newState = new State(newBattle, (this->whoseTurn + 1) % 2);
    newState->setActionUsed(selectedAction);
    return newState;
  }
	else {
		if(active->getAttack(selectedAction) != NULL) {
			usedAction = active->usedAction(selectedAction);
			if(!usedAction){
				newState = new State(newBattle, INVALID);
        newState->setActionUsed(selectedAction);
				return newState;
			}
			else {
// new code
        action = active->getAttack(selectedAction)->get_effect();
        if(action.compare("heal") == 0){
          active->update_hp(active->get_current_hp() + (active->get_stat(0) * .5));
        }
        else if(action.compare("protect") == 0){
          active->set_protect(true);
        }
        else{
          continueMatch = useAttack(active, passive, active->getAttack(selectedAction));
        }

/*
				action = active->getAttack(selectedAction)->getType();
				if(action.compare("damage") == 0) {
					continueMatch = useAttack(passive, active->getAttack(selectedAction));
				}
				else if (action.compare("heal") == 0) {
					continueMatch = useAttack(active, active->getAttack(selectedAction));
				}
*/
			}
		
		}
		else {
			newState = new State(newBattle, INVALID);
      newState->setActionUsed(selectedAction);
			return newState;
		}
	}
  if(continueMatch){
    newState = new State(newBattle, (this->whoseTurn + 1) % 2);
  }
  else newState = new State(newBattle, MATCH_OVER);

  newState->setActionUsed(selectedAction);
  return newState;
}

int State::stateEval(){
  if(this == NULL){
    cout << "Null state provided to State Evaluation function" << endl;
    return -1000000000;
  }
  int myHealth = this->myPokemon->get_current_hp();
  int hisHealth = this->thatBastardsPokemon->get_current_hp();
	int myMax = this->myPokemon->get_stat(0);
	int hisMax = this->thatBastardsPokemon->get_stat(0);
	int myHealthPercent = myHealth/(myMax * 1.0) * 100;
	int hisHealthPercent = hisHealth/(hisMax * 1.0) * 100;
//cout << "myHealthPercent = " << myHealthPercent << endl;
//cout << "hisHealthPercent = " << hisHealthPercent << endl;
  return myHealthPercent - hisHealthPercent;
}

void State::print(){
	int turn = this->whoseTurn;
	string prevTurn;
	int lastAction;
	if (turn == MY_TURN || this->myPokemon->getHealth() <= 0) { 
		prevTurn = "THAT_BASTARDS_TURN"; lastAction = this->thatBastardsPokemon->getLastAction(); 
	}
	else if( turn == THAT_BASTARDS_TURN || this->thatBastardsPokemon->getHealth() <= 0) {
		prevTurn = "MY_TURN"; lastAction = this->myPokemon->getLastAction(); 
	}
	else if(turn == INVALID) {
		cout << "tried to use ability too many times" << endl;
		return;
	}
	cout << "====================================" << endl;
	cout << "Whose turn was it: " << prevTurn <<":::: " << turn << endl;
	cout << "Action used: " << lastAction <<endl;
	cout << "---------------------------------" << endl;
	cout << "My" << endl;
	this->myPokemon->print();
	cout << "---------------------------------" << endl;
	cout << "His" << endl;
	this->thatBastardsPokemon->print();
	cout << "---------------------------------" << endl;
        cout << "Value of this state: " << this->value << endl;
        cout << "====================================" << endl;
}
