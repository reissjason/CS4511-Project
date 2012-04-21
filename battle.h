#ifndef BATTLE_H
#define BATTLE_H

#include <iostream>
#include <string>
#include <math.h>
#include "pkmn.h"
#include "team.h"
#include "attack.h"

class battle {
public:
battle(team * player, team * opponent);
int calculate_damage(attack * move; pkmn * user; pkmn * defender);
float user_item_base_dmg(string item, string p_or_s, string type);
float user_ability_base_dmg(string ability, attack * move, int current_hp, int max_hp);

float stat_modifier_func(int statChange, string userAbility, string foeAbility);


private:
  string weather;

};
#endif /*battle.h*/
