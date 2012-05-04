#include <iostream>
#include <string>
#include <math.h>
#include "pkmn.h"

using namespace std;

#include "team.h"

team::team(pkmn * t_one, pkmn * t_two, pkmn * t_three, pkmn * t_four, pkmn * t_five, pkmn * t_six){
  one = t_one;
  two = t_two;
  three = t_three;
  four = t_four;
  five = t_five;
  six = t_six;
  lead = one;

  lightscreen = false;
  reflect = false;
}
void team::change_lead(pkmn * new_lead){
//::TODO check if new lead is fainted
  if(lead->get_name().compare(new_lead->get_name()) == 0){
    cout << "Error in change_lead, given pokemon is already active" << endl;
  }
  if(new_lead == NULL){
    cout << "Error in change_lead, attempting to make a null pkmn active" << endl;
  }else {
    lead = new_lead;
  }
}

bool team::get_lightscreen(){
  return lightscreen;
}

bool team::get_reflect(){
  return reflect;
}

bool team::get_stealth_rocks(){
  return stealth_rocks;
}

bool team::get_spikes(){
  return spikes;
}

bool team::get_poison_spikes(){
  return poison_spikes;
}

pkmn * team::get_lead(){
	if (lead->isAlive())
		return lead;

	if (one != NULL && one->isAlive())
		lead = one;
	else if (two != NULL && two->isAlive())
		lead = two;
	else if (three != NULL && three->isAlive())
		lead = three;
	else if (four != NULL && four->isAlive())
		lead = four;
	else if (five != NULL && five->isAlive())
		lead = five;
	else if (six != NULL && six->isAlive())
		lead = six;

  return lead;
}

pkmn * team::get_bench(int bench_num){
  pkmn * ret = NULL;  
  if(bench_num == 1){
    ret = one;
  }else if(bench_num == 2){
    ret = two;
  }else if(bench_num == 3){
    ret = three;
  }else if(bench_num == 4){
    ret = four;
  }else if(bench_num == 5){
    ret = five;
  }else if(bench_num == 6){
    ret = six;
  }

  if(ret == NULL){
    cout << "getting invalid team position, or position did not contain a pokemon" << endl;
  }
  return ret;
}

bool team::isAlive() {
	bool alive = false;

	if (one != NULL && one->isAlive())
		alive = true;
	if (two != NULL && two->isAlive())
		alive = true;
	if (three != NULL && three->isAlive())
		alive = true;
	if (four != NULL && four->isAlive())
		alive = true;
	if (five != NULL && five->isAlive())
		alive = true;
	if (six != NULL && six->isAlive())
		alive = true;

	return alive;
}

