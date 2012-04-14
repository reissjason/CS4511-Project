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
int calculate_damage(int attack; int defense; int power);


private:

};
#endif /*battle.h*/
