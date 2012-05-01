#ifndef BATTLE_H
#define BATTLE_H

using namespace std;

#include <iostream>
#include <string>
#include <math.h>
#include "pkmn.h"
#include "team.h"
#include "attack.h"
#include "type.h"

class battle {
public:
battle(team * b_player, team * b_opponent);

int calculate_damage(attack * move, pkmn * user, pkmn * defender);
float user_item_base_dmg(string item, string p_or_s, string type);
float user_ability_base_dmg(string ability, attack * move, int current_hp, int max_hp);
float foe_ability_base_dmg(string ability, string type);
float stat_modifier_func(int statChange, string userAbility, string foeAbility);

team* get_player();
team* get_opponent();


private:
team * player;
team * opponent;

string weather;

};
#endif /*battle.h*/
