#include <iostream>
#include <string>
#include <math.h>
#include "Pokeman.h"

using namespace std;

#include "team.h"

team::team(Pokeman * t_one, Pokeman * t_two, Pokeman * t_three, Pokeman * t_four, Pokeman * t_five, Pokeman * t_six){
  this->one = t_one;
  this->two = t_two;
  this->three = t_three;
  this->four = t_four;
  this->five = t_five;
  this->six = t_six;
  this->lead = one;

  this->lightscreen = false;
  this->reflect = false;
  this->stealth_rocks = false;
  this->spikes = false;
  this->poison_spikes = false;
}

team::team(const team& ta){
  string temp;
  temp.assign(ta.lead->get_name());
  this->one = new Pokeman(*ta.one);
  this->two = new Pokeman(*ta.two);
  this->three = new Pokeman(*ta.three);
  this->four = new Pokeman(*ta.four);
  this->five = new Pokeman(*ta.five);
  this->six = new Pokeman(*ta.six);
  if(one->get_name().compare(temp) == 0){
    this->lead = this->one;
  }else if(two->get_name().compare(temp) == 0){
    this->lead = this->two;
  }else if(three->get_name().compare(temp) == 0){
    this->lead = this->three;
  }else if(four->get_name().compare(temp) == 0){
    this->lead = this->four;
  }else if(five->get_name().compare(temp) == 0){
    this->lead = this->five;
  }else if(six->get_name().compare(temp) == 0){
    this->lead = this->six;
  }

//all specific instances that can be ignored for proof of concept
  this->lightscreen = ta.lightscreen;
  this->reflect = ta.reflect;
  this->stealth_rocks = ta.stealth_rocks;
  this->spikes = ta.spikes;
  this->poison_spikes = ta.poison_spikes;
}

bool team::change_lead(Pokeman * new_lead){
//::TODO check if new lead is fainted
  if(lead->get_name().compare(new_lead->get_name()) == 0){
    cout << "Error in change_lead, given pokemon is already active" << endl;
    return false;
  }
  if(new_lead == NULL){
    cout << "Error in change_lead, attempting to make a null Pokeman active" << endl;
    return false;
  }else {
    lead = new_lead;
    return true;
  }
}

int team::get_fainted(){
  int ret = 0;

  if(one != NULL){
    if(one->get_status().compare("fainted") == 0){
      ret++;
    }
  }
  if(two != NULL){
    if(two->get_status().compare("fainted") == 0){
      ret++;
    }
  }
  if(three != NULL){
    if(three->get_status().compare("fainted") == 0){
      ret++;
    }
  }
  if(four != NULL){
    if(four->get_status().compare("fainted") == 0){
      ret++;
    }
  }
  if(five != NULL){
    if(five->get_status().compare("fainted") == 0){
      ret++;
    }
  }
  if(six != NULL){
    if(six->get_status().compare("fainted") == 0){
      ret++;
    }
  }
  return ret;
}

int team::get_total(){
  int ret = 0;

  if(one != NULL){
    ret++;
  }
  if(two != NULL){
    ret++;
  }
  if(three != NULL){
    ret++;
  }
  if(four != NULL){
    ret++;
  }
  if(five != NULL){
    ret++;
  }
  if(six != NULL){
    ret++;
  }
  return ret;
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

Pokeman * team::get_lead(){
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

Pokeman * team::get_bench(int bench_num){
  Pokeman * ret = NULL;  
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

