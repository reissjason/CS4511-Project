#include <iostream>
#include <string>
#include <math.h>
#include "pkmn.h"
#include "team.h"
#include "attack.h"
#include "battle.h"
#include "type.h"

using namespace std;

int ATTACK_LIST_LENGTH = 30;
attack * attack_list[30];

int * stat_cast(int hp, int atk, int def, int spatk, int spdef, int spd){
  int * ret_val = new int[6];
  ret_val[0] = hp;
  ret_val[1] = atk;
  ret_val[2] = def;
  ret_val[3] = spatk;
  ret_val[4] = spdef;
  ret_val[5] = spd;
  return ret_val;
}

attack * string_to_attack(string move_name){
  int i;  
  for(i = 0; i < ATTACK_LIST_LENGTH; i++){
    if(attack_list[i]->get_name().compare(move_name) == 0){
      return attack_list[i];
    }
//cout<< "i = " << i << endl << "attack = " << attack_list[i]->get_name() << endl << "move = " << move_name <<endl;
  }
  return NULL;
}

int main()
{
  for(int i = 0; i<ATTACK_LIST_LENGTH; i++){
    attack_list[i] = NULL;
  }
  int * stat_ptr;
//team1
  stat_ptr = stat_cast(297, 293, 193, 228, 206, 299);
  pkmn * charizard = new pkmn("charizard", stat_ptr, "fire", "flying", "blaze");
  charizard->add_item("life orb");

  stat_ptr = stat_cast(261, 158, 146, 383, 247, 279);
  pkmn * roserade = new pkmn("roserade", stat_ptr, "grass", "poison", "natural cure");
  roserade->add_item("big root");

  stat_ptr = stat_cast(393, 167, 348, 240, 196, 96);
  pkmn * slowbro = new pkmn("slowbro", stat_ptr, "water", "psychic", "regenerator");
  slowbro->add_item("leftover");

//team2
  stat_ptr = stat_cast(292, 328, 168, 140, 168, 329);
  pkmn * ambipom = new pkmn("ambipom", stat_ptr, "normal", "none", "technician");
  ambipom->add_item("gem flying");

  stat_ptr = stat_cast(308, 149, 208, 325, 148, 317);
  pkmn * yanmega = new pkmn("yanmega", stat_ptr, "bug", "flying", "speed boost");
  yanmega->add_item("wise glasses");
 
  stat_ptr = stat_cast(374, 176, 288, 246, 244, 156);
  pkmn * porygon2 = new pkmn("porygon2", stat_ptr, "normal", "none", "analytic");
  porygon2->add_item("eviolite");

//charizard's attack
  attack * flare_blitz = new attack("flare blitz", "fire", "recoil", "physical", 120, 1, .3);
  attack * thunderpunch = new attack("thunderpunch", "electric", "paralyze", "physical", 75, 1, .1);
  attack * dragon_dance = new attack("dragon dance", "dragon", "stat attack speed", "none", -1, 1, 1);
  attack * earthquake = new attack("earthquake", "ground", "none", "physical", 100, 1, 0);
  attack_list[0] = flare_blitz;
  attack_list[1] = thunderpunch;
  attack_list[2] = dragon_dance;
  attack_list[3] = earthquake;

//roserade's attacks
  attack * giga_drain = new attack("giga drain", "grass", "drain", "special", 75, 1, .5);
  attack * sludge_bomb = new attack("sludge bomb", "poison", "poison", "special", 90, 1, .3);
  attack * sleep_powder = new attack("sleep powder", "grass", "sleep", "none", -1, 1, .75);
  attack * synthesis = new attack("synthesis", "grass", "heal", "none", -1, 1, .5);
  attack_list[4] = giga_drain;
  attack_list[5] = sludge_bomb;
  attack_list[6] = sleep_powder;
  attack_list[7] = synthesis;

//slowbro's attacks
  attack * scald = new attack("scald", "water", "burn", "special", 80, 1, .3);
  attack * slack_off = new attack("slack off", "normal", "heal", "none", -1, 1, .5);
  attack * psychic = new attack("psychic", "psychic", "none", "special", 90, 1, 0);
  attack * toxic = new attack("toxic", "poison", "poison", "none", -1, 1, .9);
  attack_list[8] = scald;
  attack_list[9] = slack_off;
  attack_list[10] = psychic;
  attack_list[11] = toxic;

//ambipom's attacks
  attack * aerial_ace = new attack("aerial ace", "flying", "none", "physical", 60, 1, 0);
  attack * double_hit = new attack("double hit", "normal", "double", "physical", 35, 1, 0);
  attack * fake_out = new attack("fake_out", "normal", "flinch", "physical", 40, 1, 1);
  attack * low_sweep = new attack("low sweep", "fighting", "foe stat speed", "physical", 60, 1, -1);
  attack_list[12] = aerial_ace;
  attack_list[13] = double_hit;
  attack_list[14] = fake_out;
  attack_list[15] = low_sweep;

//porygon2's attacks
  attack * ice_beam = new attack("ice beam", "ice", "freeze", "special", 95, 1, .1);
  attack * thunderbolt = new attack("thunderbolt", "electric", "paralzye", "special", 95, 1, .1);
  //toxic
  attack * recover = new attack("recover", "normal", "heal", "none", -1, 1, .5);
  attack_list[16] = ice_beam;
  attack_list[17] = thunderbolt;
  attack_list[18] = recover;

//yanmega's attacks
  //giga drain
  attack * air_slash = new attack("air slash", "flying", "flinch", "special", 75, .95, .3);
  attack * bug_buzz = new attack("bug buzz", "bug", "none", "special", 90, 1, 0);
  attack * protect = new attack("protect", "normal", "protect", "none", -1, 1, 0);
  attack_list[19] = air_slash;
  attack_list[20] = bug_buzz;
  attack_list[21] = protect;

  charizard->set_attacks("flare blitz", "thunderpunch", "dragon dance", "earthquake");
  roserade->set_attacks("giga drain", "sludge bomb", "sleep powder", "synthesis");
  slowbro->set_attacks("scald", "slack off", "psychic", "toxic");
  ambipom->set_attacks("aerial ace", "double hit", "fake out", "low sweep");
  porygon2->set_attacks("ice beam", "thunderbolt", "recover", "toxic");
  yanmega->set_attacks("giga drain", "bug buzz", "air slash", "protect");

  team * laptop = new team(charizard, roserade, slowbro, NULL, NULL, NULL);
  team * tower = new team(ambipom, yanmega, porygon2, NULL, NULL, NULL);

  battle * sim = new battle(laptop, tower);

  int damage = 0;
  

  damage = sim->calculate_damage(flare_blitz, charizard, ambipom);
  cout << "damage = " << damage << endl;

  attack * next_move;
  pkmn * attacker;
  pkmn * defender;

  next_move = string_to_attack(sim->get_player()->get_lead()->get_attack(1));
  attacker = sim->get_player()->get_lead();
  defender = sim->get_opponent()->get_lead();
  
cout << "next_move power = " << next_move->get_power() << endl;

  damage = sim->calculate_damage(next_move, attacker, defender);
cout<< "damage = " << damage << endl;

  sim->get_player()->change_lead(sim->get_player()->get_bench(2));

//cout << sim->get_player()->get_lead()->get_name() << endl;
//cout << sim->get_player()->get_lead()->get_attack(1) << endl;
//cout << string_to_attack(sim->get_player()->get_lead()->get_attack(1))->get_name() << endl;

  next_move = string_to_attack(sim->get_player()->get_lead()->get_attack(1));
  attacker = sim->get_player()->get_lead();
  defender = sim->get_opponent()->get_lead();
  
cout << "next_move power = " << next_move->get_power() << endl;

  damage = sim->calculate_damage(next_move, attacker, defender);
cout<< "damage = " << damage << endl;

  return 0;
}
