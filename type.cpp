#include <iostream>
#include <string>
#include <math.h>

using namespace std;

#include "type.h"

type::type(){
}

int type::string_to_enum(string type){
  if(type.compare("bug") == 0){
    return 0;
  }else if(type.compare("dark") == 0){
    return 1;
  }else if(type.compare("dragon") == 0){
    return 2;
  }else if(type.compare("electric") == 0){
    return 3;
  }else if(type.compare("fighting") == 0){
    return 4;
  }else if(type.compare("fire") == 0){
    return 5;
  }else if(type.compare("flying") == 0){
    return 6;
  }else if(type.compare("ghost") == 0){
    return 7;
  }else if(type.compare("grass") == 0){
    return 8;
  }else if(type.compare("ground") == 0){
    return 9;
  }else if(type.compare("ice") == 0){
    return 10;
  }else if(type.compare("normal") == 0){
    return 11;
  }else if(type.compare("poison") == 0){
    return 12;
  }else if(type.compare("psychic") == 0){
    return 13;
  }else if(type.compare("rock") == 0){
    return 14;
  }else if(type.compare("steel") == 0){
    return 15;
  }else if(type.compare("water") == 0){
    return 16;
  }else return -1;
}

void type::set_type_match(){
int i;
int j;
for(i=0; i<17; i++){
  for(j=0; j<17; j++){
    TYPE_MATCH[i][j] = 1.0;
  }
}

type::TYPE_MATCH[BUG][DARK] = 2.0;
type::TYPE_MATCH[BUG][FIGHTING] = 0.5;
type::TYPE_MATCH[BUG][FIRE] = 0.5;
type::TYPE_MATCH[BUG][FLYING] = 0.5;
type::TYPE_MATCH[BUG][GHOST] = 0.5;
type::TYPE_MATCH[BUG][GRASS] = 2.0;
type::TYPE_MATCH[BUG][STEEL] = 0.5;
type::TYPE_MATCH[BUG][PSYCHIC] = 2.0;
type::TYPE_MATCH[BUG][POISON] = 0.5;

type::TYPE_MATCH[DARK][DARK] = 0.5;
type::TYPE_MATCH[DARK][FIGHTING] = 0.5;
type::TYPE_MATCH[DARK][STEEL] = 0.5;
type::TYPE_MATCH[DARK][GHOST] = 2.0;
type::TYPE_MATCH[DARK][PSYCHIC] = 2.0;

type::TYPE_MATCH[DRAGON][DRAGON] = 2.0;
type::TYPE_MATCH[DRAGON][STEEL] = 0.5;

type::TYPE_MATCH[ELECTRIC][DRAGON] = 0.5;
type::TYPE_MATCH[ELECTRIC][ELECTRIC] = 0.5;
type::TYPE_MATCH[ELECTRIC][FLYING] = 2.0;
type::TYPE_MATCH[ELECTRIC][GRASS] = 0.5;
type::TYPE_MATCH[ELECTRIC][GROUND] = 0.0;
type::TYPE_MATCH[ELECTRIC][WATER] = 2.0;

type::TYPE_MATCH[FIGHTING][BUG] = 0.5;
type::TYPE_MATCH[FIGHTING][DARK] = 2.0;
type::TYPE_MATCH[FIGHTING][FLYING] = 0.5;
type::TYPE_MATCH[FIGHTING][GHOST] = 0.0;
type::TYPE_MATCH[FIGHTING][STEEL] = 2.0;
type::TYPE_MATCH[FIGHTING][ROCK] = 2.0;
type::TYPE_MATCH[FIGHTING][PSYCHIC] = 0.5;
type::TYPE_MATCH[FIGHTING][POISON] = 0.5;
type::TYPE_MATCH[FIGHTING][NORMAL] = 2.0;
type::TYPE_MATCH[FIGHTING][ICE] = 2.0;

type::TYPE_MATCH[FIRE][BUG] = 2.0;
type::TYPE_MATCH[FIRE][DRAGON] = 0.5;
type::TYPE_MATCH[FIRE][FIRE] = 0.5;
type::TYPE_MATCH[FIRE][GRASS] = 2.0;
type::TYPE_MATCH[FIRE][WATER] = 0.5;
type::TYPE_MATCH[FIRE][STEEL] = 2.0;
type::TYPE_MATCH[FIRE][ROCK] = 0.5;
type::TYPE_MATCH[FIRE][ICE] = 2.0;

type::TYPE_MATCH[FLYING][BUG] = 2.0;
type::TYPE_MATCH[FLYING][ELECTRIC] = 0.5;
type::TYPE_MATCH[FLYING][FIGHTING] = 2.0;
type::TYPE_MATCH[FLYING][GRASS] = 2.0;
type::TYPE_MATCH[FLYING][STEEL] = 0.5;
type::TYPE_MATCH[FLYING][ROCK] = 0.5;

type::TYPE_MATCH[GHOST][DARK] = 0.5;
type::TYPE_MATCH[GHOST][GHOST] = 2.0;
type::TYPE_MATCH[GHOST][STEEL] = 0.5;
type::TYPE_MATCH[GHOST][PSYCHIC] = 2.0;
type::TYPE_MATCH[GHOST][NORMAL] = 0.0;

type::TYPE_MATCH[GRASS][BUG] = 0.5;
type::TYPE_MATCH[GRASS][DRAGON] = 0.5;
type::TYPE_MATCH[GRASS][FIRE] = 0.5;
type::TYPE_MATCH[GRASS][FLYING] = 0.5;
type::TYPE_MATCH[GRASS][GRASS] = 0.5;
type::TYPE_MATCH[GRASS][WATER] = 2.0;
type::TYPE_MATCH[GRASS][STEEL] = 0.5;
type::TYPE_MATCH[GRASS][ROCK] = 2.0;
type::TYPE_MATCH[GRASS][POISON] = 0.5;
type::TYPE_MATCH[GRASS][GROUND] = 2.0;

type::TYPE_MATCH[GROUND][BUG] = 0.5;
type::TYPE_MATCH[GROUND][ELECTRIC] = 2.0;
type::TYPE_MATCH[GROUND][FIRE] = 2.0;
type::TYPE_MATCH[GROUND][FLYING] = 0.0;
type::TYPE_MATCH[GROUND][GRASS] = 0.5;
type::TYPE_MATCH[GROUND][STEEL] = 2.0;
type::TYPE_MATCH[GROUND][ROCK] = 2.0;
type::TYPE_MATCH[GROUND][POISON] = 2.0;

type::TYPE_MATCH[ICE][DRAGON] = 2.0;
type::TYPE_MATCH[ICE][FIRE] = 0.5;
type::TYPE_MATCH[ICE][FLYING] = 2.0;
type::TYPE_MATCH[ICE][GRASS] = 2.0;
type::TYPE_MATCH[ICE][WATER] = 0.5;
type::TYPE_MATCH[ICE][STEEL] = 0.5;
type::TYPE_MATCH[ICE][GROUND] = 2.0;
type::TYPE_MATCH[ICE][ICE] = 0.5;

type::TYPE_MATCH[NORMAL][GHOST] = 0.0;
type::TYPE_MATCH[NORMAL][STEEL] = 0.5;
type::TYPE_MATCH[NORMAL][ROCK] = 0.5;

type::TYPE_MATCH[POISON][GRASS] = 2.0;
type::TYPE_MATCH[POISON][STEEL] = 0.0;
type::TYPE_MATCH[POISON][ROCK] = 0.5;
type::TYPE_MATCH[POISON][POISON] = 0.5;
type::TYPE_MATCH[POISON][GROUND] = 0.5;

type::TYPE_MATCH[PSYCHIC][DARK] = 0.0;
type::TYPE_MATCH[PSYCHIC][FIGHTING] = 2.0;
type::TYPE_MATCH[PSYCHIC][POISON] = 2.0;
type::TYPE_MATCH[PSYCHIC][STEEL] = 0.5;
type::TYPE_MATCH[PSYCHIC][PSYCHIC] = 0.5;

type::TYPE_MATCH[ROCK][BUG] = 2.0;
type::TYPE_MATCH[ROCK][FIGHTING] = 0.5;
type::TYPE_MATCH[ROCK][FIRE] = 2.0;
type::TYPE_MATCH[ROCK][FLYING] = 2.0;
type::TYPE_MATCH[ROCK][STEEL] = 0.5;
type::TYPE_MATCH[ROCK][GROUND] = 0.5;
type::TYPE_MATCH[ROCK][ICE] = 2.0;

type::TYPE_MATCH[STEEL][ELECTRIC] = 0.5;
type::TYPE_MATCH[STEEL][FIRE] = 0.5;
type::TYPE_MATCH[STEEL][WATER] = 0.5;
type::TYPE_MATCH[STEEL][STEEL] = 0.5;
type::TYPE_MATCH[STEEL][ROCK] = 2.0;
type::TYPE_MATCH[STEEL][ICE] = 2.0;

type::TYPE_MATCH[WATER][DRAGON] = 0.5;
type::TYPE_MATCH[WATER][FIRE] = 2.0;
type::TYPE_MATCH[WATER][GRASS] = 0.5;
type::TYPE_MATCH[WATER][WATER] = 0.5;
type::TYPE_MATCH[WATER][ROCK] = 2.0;
type::TYPE_MATCH[WATER][GROUND] = 2.0;
}

float type::get_type_match(int atk_type, int target_type){
  return TYPE_MATCH[atk_type][target_type];
}
