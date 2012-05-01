#include <iostream>
#include <string>
#include <math.h>
#include "pkmn.h"
#include "team.h"
#include "attack.h"

using namespace std;

#include "battle.h"

battle::battle(team * b_player, team * b_opponent){
  player = b_player;
  opponent = b_opponent;
}

team* battle::get_player(){
  return player;
}

team* battle::get_opponent(){
  return opponent;
}

/*
*Takes in the item name, whether the attack is physical or special, and the type of the move.
*Outputs the item modifier to base damage
*/
float battle::user_item_base_dmg(string item, string p_or_s, string type){
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
  }else if(item.compare("griseous orb") == 0){
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
float battle::user_ability_base_dmg(string ability, attack * move, int current_hp, int max_hp){

  string type = move->get_type();
  int power = move->get_power();
  
  //calculating the third of the maximum hp
  float third_hp = max_hp / 3.0;
  third_hp = floor(third_hp);
  int total_hp = (int) third_hp;
  float value = 1;

  string effect = move->get_effect();

  //checking if user ability has an effect on the base damage
  if(ability.compare("reckless") == 0){
    if(effect.compare("recoil") == 0){
      value = 1.2;
    }
  }else if(ability.compare("blaze") == 0){
    if(type.compare("fire") == 0 && current_hp <= total_hp){
      value = 1.5;
    }
  }else if(ability.compare("overgrow") == 0){
    if(type.compare("grass") == 0 && current_hp <= total_hp){
      value = 1.5;
    }
  }else if(ability.compare("torrent") == 0){
    if(type.compare("water") == 0 && current_hp <= total_hp){
      value = 1.5;
    }
  }else if(ability.compare("swarm") == 0){
    if(type.compare("bug") == 0 && current_hp <= total_hp){
      value = 1.5;
    }
  }else if(ability.compare("technician") == 0){
    if(power <= 60){
      value = 1.5;
    }
  }
  return value;
}// end user_ability_base_dmg

//::TODO fix this code, add call in calc_damage, add comments
/*
*Takes in defender ability and move type
*outputs the foe ability modifier to base damage
*/
float battle::foe_ability_base_dmg(string ability, string type){
  float value = 1;
  if(ability.compare("thick fat") == 0){
    if(type.compare("fire") == 0 || type.compare("ice") == 0){
      value = .5;
    }
  }else if(ability.compare("heatproof") == 0){
    if(type.compare("fire") == 0){
      value = .5;
    }
  }else if(ability.compare("dry skin") == 0){
    if(type.compare("fire") == 0){
     value = 1.25;
    }
  }
  return value;
}//end foe_ability_base_dmg

/*
* Takes in the the user's stat change, the user ability and the foe's ability
* outputs the stat modifier multiplier
* remember the userAbility refers to the pokemon who's stat change is being calculated
*/
float battle::stat_modifier_func(int statChange, string userAbility, string foeAbility){
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
      value = 2.0 / (2.0 - statChange);
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
    }else if(statChange >= 3){
      value = 4;
    }
  }
  return value;
}//end stat_modifier_func

/*
*
*
*/
int battle::calculate_damage(attack * move, pkmn * user, pkmn * defender){
// assumes move is valid, user and defender are valid and initiated correctly ::TODO:: checks to confirm this
//cout << "in calculate_damage" << endl;
  type * types = new type();
  types->set_type_match();

  string user_name = user->get_name();
  string user_item = user->get_item();
  string user_ability = user->get_ability();
  string user_status = user->get_status();
  string user_type1 = user->get_type(0);
  string user_type2 = user->get_type(1); 
  int user_stats[6];
  int i;
  for(i = 0; i<6; i++){
    user_stats[i] = user->get_stat(i);
  }
  int user_stat_increases[6];
  for(i = 0; i<6; i++){
    user_stat_increases[i] = user->get_stat_increase(i);
  }
  int user_current_hp = user->get_current_hp();
  bool user_charge = user->get_charge();

  string defender_name = defender->get_name();
  string defender_item = defender->get_item();
  string defender_ability = defender->get_ability();
  string defender_status = defender->get_status();
  string defender_type1 = defender->get_type(0);
  string defender_type2 = defender->get_type(1); 
  int defender_stats[6];
  for(i = 0; i<6; i++){
    defender_stats[i] = defender->get_stat(i);
  }
  int defender_stat_increases[6];
  for(i = 0; i<6; i++){
    defender_stat_increases[i] = defender->get_stat_increase(i);
  }

  int move_power = move->get_power();
  string move_type = move->get_type();
  string p_or_s = move->get_p_or_s();

  int base;
  float item = 1;
  float charge = 1;
  //float mudSport = 1;
  //float waterSport = 1;
  float userAbility = 1;
  float foeAbility = 1;

  //determine item mod for base dmg
  if(!(user_item.empty())){
  item = user_item_base_dmg(user_item, p_or_s, move_type);
  }

  //case if the user has previously used charge
  if(user_charge) charge = 2;

  //Mud sport and water sport are unimplemented for lack of competetive use, to implement need bool's in team

  //determine user ability mod for base dmg
  userAbility = user_ability_base_dmg(user_ability, move, user_current_hp, user_stats[0]);

  //::TODO add call to foe ability
  foeAbility = foe_ability_base_dmg(defender_ability, move_type);

  base = floor(move_power * item);
  base = floor(base * charge);
  base = floor(base * userAbility);
  base = floor(base * foeAbility);

  //determine modifiers to the relevant attack stat
  int relAtkStat;
  float statMod;
  userAbility = 1;
  item = 1;

  //if the move is physical, determine modifier using the attack stat
  if(p_or_s.compare("physical") == 0){
    statMod = stat_modifier_func(user_stat_increases[1], user_ability, defender_ability);
  }
  //if the move is special, determine modifier using the special attack stat
  else statMod = stat_modifier_func(user_stat_increases[3], user_ability, defender_ability);

  if(p_or_s.compare("physical") == 0){
    if(user_ability.compare("pure power") == 0 || user_ability.compare("huge power") == 0){
      userAbility = 2;
    }else if(user_ability.compare("flower gift") == 0 && weather.compare("sunny") == 0){
      userAbility = 1.5;
    }else if(user_ability.compare("guts") == 0 && !(user_status.empty())){
      userAbility = 1.5;
    }else if(user_ability.compare("hustle") == 0){
      userAbility = 1.5;
    }else userAbility = 1;
  }else{
    if(user_ability.compare("solar power") == 0 && weather.compare("sunny") == 0){
      userAbility = 1.5;
    }
  }

  if(user_item.compare("choice band") == 0 || user_item.compare("choice specs") == 0){
//::TODO assumption made here that the attack is the correct physcal or special
    item = 1.5;
  }else if(user_item.compare("thick club") == 0 || user_name.compare("marowak") == 0){
    item = 2;
  }else item = 1;

  if(p_or_s.compare("physical") == 0){
    relAtkStat = user_stats[1];
  }else relAtkStat = user_stats[3];

  relAtkStat = floor(relAtkStat * statMod);
  relAtkStat = floor(relAtkStat * userAbility);
  relAtkStat = floor(relAtkStat * item);

  //determine the modifiers to the relevant defense stat
  int relDefStat;
  float sStorm = 1;
  foeAbility = 1;
  item = 1;

  if(p_or_s.compare("physical") == 0){
    if(defender_item.compare("metal powder") == 0 && defender_name.compare("ditto") == 0){
      item = 1.5;
    }
    if(defender_ability.compare("marvel scale") == 0 && !(defender_status.empty())){
      foeAbility = 1.5;
    }
    if(defender_item.compare("eviolite") == 0){
      item = 1.5;
    }else{
      item = 1;
      foeAbility = 1;
    }
  }else{
    if(weather.compare("sandstorm") == 0){
      if(defender_type1.compare("rock") == 0 || defender_type2.compare("rock") == 0){
        sStorm = 1.5;
      }
    }
    if(defender_item.compare("metal powder") == 0 && defender_name.compare("ditto") == 0){
      item = 1.5;
    }
    if(defender_ability.compare("flower gift") == 0 && weather.compare("sunny") == 0){
      foeAbility = 1.5;
    }
    if(defender_item.compare("eviolite") == 0){
      item = 1.5;
    }
  }

  //if the move is physical, determine modifier using the defense stat
  if(p_or_s.compare("physical") == 0){
    statMod = stat_modifier_func(defender_stat_increases[2], defender_ability, user_ability);
  }
  //if the move is special, determine modifier using the special defense stat
  else statMod = stat_modifier_func(defender_stat_increases[4], defender_ability, user_ability);
  
  if(p_or_s.compare("physical") == 0){
    relDefStat = defender_stats[2];
  }else relDefStat = defender_stats[4];

//cout << "relDefStat = " << relDefStat << endl;
//cout << "statMod = " << statMod << endl;
//cout << "foeAbility = " << foeAbility << endl;
//cout << "sStorm = " << sStorm << endl;

  relDefStat = floor(relDefStat * statMod);
  relDefStat = floor(relDefStat * foeAbility);
  relDefStat = floor(relDefStat * item);
  relDefStat = floor(relDefStat * sStorm);

//cout << "relDefStat = " << relDefStat << endl << endl;

  //calculate the first modifier
  float mod1;
  float burn = 1;
  float screens = 1;
  float weather_mod = 1;
  float flashfire = 1;

  if(p_or_s.compare("physical") == 0){
    if(user_status.compare("burn") == 0 && user_ability.compare("guts") != 0){
      burn = .5;
    }
    if(opponent->get_reflect()){
      screens = .5;
    }
  }else{
    if(opponent->get_lightscreen()){
      screens = .5;
    }
  }
  if(weather.compare("sunny") == 0){
    if(move_type.compare("fire") == 0){
      weather_mod = 1.5;
    }else if(move_type.compare("water") == 0){
      weather_mod = .5;
    }
  }else if(weather.compare("rainy") == 0){
    if(move_type.compare("fire") == 0){
      weather_mod = .5;
    }else if(move_type.compare("water") == 0){
      weather_mod = 1.5;
    }
  }
  mod1 = burn * screens;
  mod1 = mod1 * weather_mod;
  mod1 = mod1 * flashfire;

  //calculate the second modifier ::TODO:: add metronome and me first
  float mod2 = 1;
  if(user_item.compare("life orb") == 0){
    mod2 = 1.3;
  }

  //determine STAB
  float stab = 1;
  if(move_type.compare(user_type1) == 0 || move_type.compare(user_type2) == 0){
    stab = 1.5;
  }
  if(user_ability.compare("adaptability") == 0 && stab != 1){
    stab = 2;
  }

  //determine super effective hits
  int move_enum = types->string_to_enum(move_type);
  int type1_enum = types->string_to_enum(defender_type1);
  int type2_enum = types->string_to_enum(defender_type2);
//cout << "move type = " << move_type << endl;
//cout << "move enum = " << move_enum << endl;
//cout << "type1 enum = " << type1_enum << endl;
//cout << "type2 enum = " << type2_enum << endl;

  float type1 = types->get_type_match(move_enum, type1_enum);
  float type2 = types->get_type_match(move_enum, type2_enum);
  

  //calculate the third modifier
  float mod3;
  float solidRockFilter = 1;
  float expertBelt = 1;
  float tintedLens = 1;
  float berry = 1;

  if(type1 != 1 || type2 != 1){
    if(user_item.compare("expert belt") == 0){
      expertBelt = 1.2;
    }
  }
//cout << "user item = " << user_item << endl;
//cout << "expertBelt = " << expertBelt << endl;
  mod3 = solidRockFilter * expertBelt;
  mod3 = mod3 * tintedLens;
  mod3 = mod3 * berry;

//cout<< "base = " << base << endl;
//cout<< "relAtkStat = " << relAtkStat << endl;
//cout<< "relDefStat = " << relDefStat << endl;
//cout<< "mod1 = " << mod1 << endl;
//cout<< "mod2 = " << mod2 << endl;
//cout<< "stab = " << stab << endl;
//cout<< "type1 = " << type1 << endl;
//cout<< "type2 = " << type2 << endl;
//cout<< "mod3 = " << mod3 << endl;

  long ret_val = 42;
  ret_val = floor(ret_val * base);
//cout << "base ret_val = " << ret_val << endl;
  ret_val = floor(ret_val * relAtkStat);
//cout << "atk ret_val = " << ret_val << endl;
  ret_val = floor(ret_val / 50);
//cout << "ret_val = " << ret_val << endl;
  ret_val = floor(ret_val / relDefStat);
//cout << "def et_val = " << ret_val << endl;
  ret_val = floor(ret_val * mod1);
//cout << "mod1 ret_val = " << ret_val << endl;
  ret_val = floor(ret_val + 2);
//cout << "ret_val = " << ret_val << endl;
  ret_val = floor(ret_val * 1);
//cout << "ret_val = " << ret_val << endl;
  ret_val = floor(ret_val * mod2);
//cout << "mod2 ret_val = " << ret_val << endl;
  ret_val = floor(ret_val * 1);
//cout << "ret_val = " << ret_val << endl;
  ret_val = floor(ret_val * 100);
  ret_val = floor(ret_val / 100);
//cout << "ret_val = " << ret_val << endl;
  ret_val = floor(ret_val * stab);
//cout << "stab ret_val = " << ret_val << endl;
  ret_val = floor(ret_val * type1);
//cout << "type1 ret_val = " << ret_val << endl;
  ret_val = floor(ret_val * type2);
//cout << "type2 ret_val = " << ret_val << endl;
  ret_val = floor(ret_val * mod3);
//cout << "mod3 ret_val = " << ret_val << endl;
  return ret_val;

  //::TODO:: fill in final calculation
}
