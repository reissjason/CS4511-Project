#ifndef BATTLE_H
#define BATTLE_H

using namespace std;

#include <iostream>
#include <string>
#include <math.h>
#include "Pokeman.h"
#include "team.h"
#include "TinyAttack.h"
#include "type.h"

class battle {
public:
battle(team * b_player, team * b_opponent);
battle(const battle& ba);

int calculate_damage(TinyAttack * move, Pokeman * user, Pokeman * defender);
float user_item_base_dmg(string item, string p_or_s, string type);
float user_ability_base_dmg(string ability, TinyAttack * move, int current_hp, int max_hp);
float foe_ability_base_dmg(string ability, string type);
float stat_modifier_func(int statChange, string userAbility, string foeAbility);

team* get_player();
team* get_opponent();
string get_weather();


private:
team * player;
team * opponent;

string weather;

};
#endif /*battle.h*/
