#ifndef TEAM_H
#define TEAM_H

using namespace std;

#include <iostream>
#include <string>
#include <math.h>
#include "pkmn.h"

class team {
public:
  team(pkmn * t_one, pkmn * t_two, pkmn * t_three, pkmn * t_four, pkmn * t_five, pkmn * t_six);
  
  void change_lead(pkmn * new_lead);

  bool get_lightscreen();
  bool get_reflect();
  bool get_stealth_rocks();
  bool get_spikes();
  bool get_poison_spikes();

  bool isAlive();

  pkmn * get_lead();

  pkmn * get_bench(int bench_num);
  
private:
  pkmn * lead;
  pkmn * one;
  pkmn * two;
  pkmn * three;
  pkmn * four;
  pkmn * five;
  pkmn * six;

//all specific instances that can be ignored for proof of concept
  bool lightscreen;
  bool reflect;
  bool stealth_rocks;
  bool spikes;
  bool poison_spikes;
  
};
#endif /*team.h*/
