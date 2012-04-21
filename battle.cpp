#include <iostream>
#include <string>
#include <math.h>
#include "pkmn.h"
#include "team.h"
#include "attack.h"

using namespace std;

#include "battle.h"

battle(team * player, team * defender){

}
/*
*Takes in the item name, whether the attack is physical or special, and the type of the move.
*Outputs the item modifier to base damage
*/
float user_item_base_dmg(string item, string p_or_s, string type){
//The following items equipped to the user provide a boost to the item multiplier   
  float value = 1; 
  if(item.compare("muscle band") == 0){
    if(p_or_s.compare("physical") == 0){
      value = 1.1;
    }
  }else if(item.compare("wise glasses") == 0){
    if(p_or_s.compare("special") == 0){
      value = 1.1;
    }
  }
  //type boosting gems, one time uses, larger boosts ::TODO:: check length to avoid segfault
  //format should be "gem fire" "gem fighting" etc.
  else if(item.compare(0, 3, "gem") == 0){
    if(item.compare(5, (item.length() - 4), type) == 0){
      value = 1.5;
    }
  }
  //type boosting items
  //currently, plates, incense etc are represented by the type effected only
  else if(item.compare(type) == 0) value = 1.2;
  //used with palkia, dialga, giratina
  else if(item.compare("adamant orb") == 0){
    if(type.compare("dragon") == 0 || type.compare("steel") == 0){
      value = 1.2;
    }
  }else if(item.compare("lustrous orb") == 0){
    if(type.compare("dragon") == 0 || type.compare("water") == 0){
      value = 1.2;
    }
  }else if(user->item.compare("griseous orb") == 0){
    if(type.compare("dragon") == 0 || type.compare("ghost") == 0){
      value = 1.2;
    }
  }
  return value;
}//end user_item_base_dmg

/*
* takes in the user's ability, the move type and power, and the users current and total hp
* outputs the userAbility modifier to base damage
*/
float user_ability_base_dmg(string ability, attack * move, int current_hp, int max_hp){
  string type;
  type.copy(move->type, move->type.length(), 0);
  int power = move->power;
  
  //calculating the third of the maximum hp
  float third_hp = max_hp / 3.0;
  third_hp = floor(third_hp);
  int total_hp = (int) third_hp;
  float value = 1;

  string effect;
  if(move->effect != NULL){ //::TODO
    effect.copy(move->effect, move->effect.length(), 0);
  }

  //checking if user ability has an effect on the base damage
  if(ability.compare("reckless"){
    if(effect.compare("recoil") == 0){
      value = 1.2;
    }
  }else if(ability.compare("blaze"){
    if(type.compare("fire") == 0 && current_hp <= total_hp){
      value = 1.5;
    }
  }else if(user->ability.compare("overgrow"){
    if(type.compare("grass") == 0 && current_hp <= total_hp){
      value = 1.5;
    }
  }else if(user->ability.compare("torrent"){
    if(type.compare("water") == 0 && current_hp <= total_hp){
      value = 1.5;
    }
  }else if(user->ability.compare("swarm"){
    if(type.compare("bug") == 0 && current_hp <= total_hp){
      value = 1.5;
    }
  }else if(user->ability.compare("technician"){
    if(power <= 60){
      value = 1.5;
    }
  }
  return value;
}// end user_ability_base_dmg

//::TODO fix this code, add call in calc_damage, add comments
float foe_ability_base_dmg(){
  if(defender->ability.compare("thick fat"){
    if(move->type.compare("fire") == 0 || move->type.compare("ice") == 0){
      foeAbility = .5;
    }else foeAbility = 1;
  }else if(defender->ability.compare("heatproof"){
    if(move->type.compare("fire") == 0){
      foeAbility = .5;
    }else foeAbility = 1;
  }else if(defender->ability.compare("dry skin"){
    if(move->type.compare("fire") == 0){
      foeAbility = 1.25;
    }else foeAbility = 1;
  }else foeAbility = 1;
}

/*
* Takes in the the user's stat change, the user ability and the foe's ability
* outputs the stat modifier multiplier
* remember the userAbility refers to the pokemon who's stat change is being calculated
*/
float stat_modifier_func(int statChange, string userAbility, string foeAbility){
  float value = 1;
  //if there is no change, we do not need to do any calculations
  if(statChange == 0){
    return value;
  }
  //if the defender has the unaware ability the multiplier is always 1
  if(foeAbility.compare("unaware") == 0){
    return value;
  }
  //this is an algorithmic computation based on whether or not the userAbility is "simple"
  if(userAbility.compare("simple") != 0){
    if(statChange < 0){
      value = 2 / (2 + abs(statChange));
    }else value = (2 + statChange) / 2;
  }
  else{ //if the ability is "simple, there is no algorithm, the values match to a table
    if(statChange == -1){
      value = 1/2;
    }else if(statChange == -2){
      value = 1/3;
    }else if(statChange <= -3){
      value = 1/4;
    }else if(statChange == 1){
      value = 2;
    }else if(statChange == 2){
      value = 3;
    }else if(statChange] >= 3){
      value = 4;
    }
  }
  return value;
}//end stat_modifier_func

int calculate_damage(attack * move; pkmn * user; pkmn * defender){
// assumes move is valid, user and defender are valid and initiated correctly ::TODO:: checks to confirm this
  int base;
  float item = 1;
  float charge = 1;
  float mudSport = 1;
  float waterSport = 1;
  float userAbility = 1;
  float foeAbility = 1;

  //determine item mod for base dmg
  if(user->item != NULL){
  item = user_item_base_dmg(user->item, move->p_or_s, move->type); //::TODO
  }

  //case if the user has previously used charge ::TODO::
  if(user->charge == true) charge = 2;

  //Mud sport and water sport are unimplemented for lack of competetive use, to implement need bool's in team

  //determine user ability mod for base dmg
  userAbility = user_ability_base_dmg(user->ability, move, user->current_hp, user->stats[0]);

  //::TODO add call to foe ability

  //determine modifiers to the relevant attack stat
  base = floor(move->power * item);
  base = floor(base * charge);
  base = floor(base * userAbility);
  base = floor(base * foeAbility);

  int relAtkStat;
  float statMod;

  //if the move is physical, determine modifier using the attack stat
  if(move->p_or_s.compare("physical") == 0){
    statMod = stat_modifier_func(user->stat_increases[1], user->ability, defender->ability);
  }
  //if the move is special, determine modifier using the special attack stat
  else statMod = stat_modifier_func(user->stat_increases[3], user->ability, defender->ability);

  

  if(move->p_or_s.compare("physical") == 0){
    if(user->ability.compare("pure power") == 0 || user->ability.compare("huge power") == 0){
      userAbility = 2;
    }else if(user->ability.compare("flower gift") == 0 && weather.compare("sunny") == 0){
      userAbility = 1.5;
    }else if(user->ability.compare("guts") == 0 && user->status != NULL){
      userAbility = 1.5;
    }else if(user->ability.compare("hustle") == 0){
      userAbility = 1.5;
    }else userAbility = 1;
  }else{
    if(user->ability.compare("solar power") == 0 && weather.compare("sunny") == 0){
      userAbility = 1.5;
    }
  }
  if(user->item.compare("choice band") == 0 || (user->item.compare("choice specs") == 0){
    item = 1.5;
  }else if(user->item.compare("choice band") == 0 || (user->name.compare("marowak") == 0){
    item = 2
  }else item = 1;
  if(move->p_or_s.compare("physical") == 0){
    relAtkstat = user->stats[1];
  }else relAtkstat = user->stats[3];

  //determine the modifiers to the relevant defense stat
  relAtkStat = floor(relAtkstat * statMod);
  relAtkStat = floor(relAtkStat * userAbility);
  relAtkStat = floor(relAtkStat * item);

  int relDefStat;
  float sStorm;

  if(move->p_or_s.compare("physical"){
    if(defender->item.compare("metal powder") == 0 && defender->name.compare("ditto") == 0){
      item = 1.5;
    }
    if(defender->ability.compare("marvel scale") == 0 && defender->status != NULL){
      foeAbility = 1.5;
    }
    if(defender->item.compare("eviolite"){
      item = 1.5;
    }else{
      item = 1;
      foeAbility = 1;
    }
  }else{
    if(weather.compare("sandstorm") == 0){
      if(defender->type1.compare("rock") == 0 || defender->type2.compare("rock") == 0){
        sStorm = 1.5;
      }
    }
    if(defender->item.compare("metal powder") == 0 && defender->name.compare("ditto") == 0){
      item = 1.5;
    }
    if(defender->ability.compare("flower gift") == 0 && weather.compare("sunny"){
      foeAbility = 1.5;
    }
    if(defender->item.compare("eviolite"){
      item = 1.5;
    }else mod = 1;
  }

  //if the move is physical, determine modifier using the defense stat
  if(move->p_or_s.compare("physical") == 0){
    statMod = stat_modifier_func(user->stat_increases[2], defender->ability, user->ability);
  }
  //if the move is special, determine modifier using the special defense stat
  else statMod = stat_modifier_func(user->stat_increases[4], defender->ability, user->ability);
  
  if(move->p_or_s.compare("physical") == 0){
    relDefstat = defender->stats[2];
  }else relDefstat = defender->stats[3];

  //calculate the first modifier
  relDefStat = floor(relDefstat * statMod);
  relDefStat = floor(relDefStat * foeAbility);
  relDefStat = floor(relDefStat * item);
  relDefStat = floor(relDefStat * sStorm);

  float mod1;
  float burn = 1;
  float screens = 1;
  float weather = 1;
  float flashfire = 1;

  if(move->p_or_s.compare("physical") == 0){
    if(user->status.compare("burn") == 0 && user->ability.compare("guts") != 0){
      burn = .5;
    }
    if(opponent->reflect){
      screens = .5;
    }
  }else{
    if(opponent->lightscreen){
      screens = .5;
    }
  }
  if(weather.compare("sunny") == 0){
    if(move->type.compare("fire") == 0){
      weather = 1.5;
    }else if(move->tpye.compare("water"){
      weather = .5;
    }
  }else if(weather.compare("rainy"){
    if(move->type.compare("fire") == 0){
      weather = .5;
    }else if(move->tpye.compare("water"){
      weather = 1.5;
    }
  }
  mod1 = burn * screens;
  mod1 = mod1 * weather;
  //mod1 = mod1 * flashfire;

  //calculate the second modifier ::TODO:: add metronome and me first
  float mod2;
  if(user->item.compare("life orb") == 0){
    mod2 = 1.3;
  }

  //determine STAB
  float stab = 1;
  if(move->type.compare(user->type) == 0){
    stab = 1.5;
  }
  if(user->ability.compare("adaptability") == 0 && stab != 1){
    stab = 2;
  }

  //determine super effective hits
  float type1 = 1;
  float type2 = 1;

  //calculate the third modifier
  float mod3;
  float solidRockFilter = 1;
  float expertBelt = 1;
  float tintedLens = 1;
  float berry = 1;

  if(type1 != 1 || type2 != 1){
    if(user->item.compare("expert belt") == 0){
      expertBelt = 1.2;
    }
  }

  

  //::TODO:: fill in final calculation
}
