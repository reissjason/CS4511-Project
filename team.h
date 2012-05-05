#ifndef TEAM_H
#define TEAM_H

using namespace std;

#include <iostream>
#include <string>
#include <math.h>
#include "Pokeman.h"

class team {
public:
  team(Pokeman * t_one, Pokeman * t_two, Pokeman * t_three, Pokeman * t_four, Pokeman * t_five, Pokeman * t_six);
  team(const team& ta);
  
  bool change_lead(Pokeman * new_lead);

  int get_fainted();
  int get_total();

  bool get_lightscreen();
  bool get_reflect();
  bool get_stealth_rocks();
  bool get_spikes();
  bool get_poison_spikes();
  bool isAlive() ;

  Pokeman * get_lead();

  Pokeman * get_bench(int bench_num);
  
private:
  Pokeman * lead;
  Pokeman * one;
  Pokeman * two;
  Pokeman * three;
  Pokeman * four;
  Pokeman * five;
  Pokeman * six;

//all specific instances that can be ignored for proof of concept
  bool lightscreen;
  bool reflect;
  bool stealth_rocks;
  bool spikes;
  bool poison_spikes;
  
};
#endif /*team.h*/
