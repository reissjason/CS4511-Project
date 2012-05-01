#ifndef TYPE_H
#define TYPE_H

#include <iostream>
#include <string>
#include <math.h>

class type {

public:
  type();

  enum { BUG, DARK, DRAGON, ELECTRIC, FIGHTING, FIRE, FLYING, GHOST, GRASS, GROUND, ICE, NORMAL, POISON, PSYCHIC, ROCK, STEEL, WATER };

  void set_type_match();
  float get_type_match(int atk_type, int target_type);
  int string_to_enum(string type);

private:
  float TYPE_MATCH[17][17];

};
#endif /*type.h*/
