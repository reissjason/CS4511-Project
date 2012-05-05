#include "list.h"
#include <string>
#include <iostream>

list::list(){
}

int * list::stat_cast(int hp, int atk, int def, int spatk, int spdef, int spd){
  int * ret_val = new int[6];
  ret_val[0] = hp;
  ret_val[1] = atk;
  ret_val[2] = def;
  ret_val[3] = spatk;
  ret_val[4] = spdef;
  ret_val[5] = spd;
  return ret_val;
}

TinyAttack * list::string_to_attack(string move_name){
  int i;  
  //cout << "looking for " << move_name << endl;
  for(i = 0; i < ATTACK_LIST_LENGTH; i++){
	//cout << "is it " << attack_list[i]->get_name() << endl;
    if(attack_list[i]->get_name().compare(move_name) == 0){
    //	cout << "yep";
      return attack_list[i];
    }
  }
  return NULL;
}

void list::construct_list(){
  TinyAttack * empty = new TinyAttack();
  for(int i = 0; i<ATTACK_LIST_LENGTH; i++){
    attack_list[i] = empty;
  }
//charizard's attack
  TinyAttack * flare_blitz = new TinyAttack("flare blitz", "fire", "recoil", "physical", 120, 1, .3, 10, 0);
  TinyAttack * thunderpunch = new TinyAttack("thunderpunch", "electric", "paralyze", "physical", 75, 1, .1, 10, 0);
  TinyAttack * dragon_dance = new TinyAttack("dragon dance", "dragon", "stat attack speed", "none", -1, 1, 1, 10, 0);
  TinyAttack * earthquake = new TinyAttack("earthquake", "ground", "none", "physical", 100, 1, 0, 10, 0);

//roserade's attacks
  TinyAttack * giga_drain = new TinyAttack("giga drain", "grass", "drain", "special", 75, 1, .5, 10, 0);
  TinyAttack * sludge_bomb = new TinyAttack("sludge bomb", "poison", "poison", "special", 90, 1, .3, 10, 0);
  TinyAttack * sleep_powder = new TinyAttack("sleep powder", "grass", "sleep", "none", -1, 1, .75, 10, 0);
  TinyAttack * synthesis = new TinyAttack("synthesis", "grass", "heal", "none", -1, 1, .5, 10, 0);

//slowbro's attacks
  TinyAttack * scald = new TinyAttack("scald", "water", "burn", "special", 80, 1, .3, 10, 0);
  TinyAttack * slack_off = new TinyAttack("slack off", "normal", "heal", "none", -1, 1, .5, 10, 0);
  TinyAttack * psychic = new TinyAttack("psychic", "psychic", "none", "special", 90, 1, 0, 10, 0);
  TinyAttack * toxic = new TinyAttack("toxic", "poison", "poison", "none", -1, 1, .9, 10, 0);

//ambipom's attacks
  TinyAttack * aerial_ace = new TinyAttack("aerial ace", "flying", "none", "physical", 60, 1, 0, 10, 0);
  TinyAttack * double_hit = new TinyAttack("double hit", "normal", "double", "physical", 35, 1, 0, 10, 0);
  TinyAttack * fake_out = new TinyAttack("fake out", "normal", "flinch", "physical", 40, 1, 1, 10, 3);
  TinyAttack * low_sweep = new TinyAttack("low sweep", "fighting", "foe stat speed", "physical", 60, 1, -1, 10, 0);

//porygon2's attacks
  TinyAttack * ice_beam = new TinyAttack("ice beam", "ice", "freeze", "special", 95, 1, .1, 10, 0);
  TinyAttack * thunderbolt = new TinyAttack("thunderbolt", "electric", "paralzye", "special", 95, 1, .1, 10, 0);
  //toxic
  TinyAttack * recover = new TinyAttack("recover", "normal", "heal", "none", -1, 1, .5, 10, 0);

//yanmega's attacks
  //giga drain
  TinyAttack * air_slash = new TinyAttack("air slash", "flying", "flinch", "special", 75, .95, .3, 10, 0);
  TinyAttack * bug_buzz = new TinyAttack("bug buzz", "bug", "none", "special", 90, 1, 0, 10, 0);
  TinyAttack * protect = new TinyAttack("protect", "normal", "protect", "none", -1, 1, 0, 10, 4);

  attack_list[0] = flare_blitz;
  attack_list[1] = thunderpunch;
  attack_list[2] = dragon_dance;
  attack_list[3] = earthquake;

  attack_list[4] = giga_drain;
  attack_list[5] = sludge_bomb;
  attack_list[6] = sleep_powder;
  attack_list[7] = synthesis;

  attack_list[8] = scald;
  attack_list[9] = slack_off;
  attack_list[10] = psychic;
  attack_list[11] = toxic;

  attack_list[12] = aerial_ace;
  attack_list[13] = double_hit;
  attack_list[14] = fake_out;
  attack_list[15] = low_sweep;

  attack_list[16] = ice_beam;
  attack_list[17] = thunderbolt;
  attack_list[18] = recover;

  attack_list[19] = air_slash;
  attack_list[20] = bug_buzz;
  attack_list[21] = protect;
}







