#pragma once

#include "TalismanGame.h"
#include <vector>

class Character
{
public:
	Character(int life, int strength, int craft, int fate);
	virtual ~Character(void);

  int life();
  int strength();
  int craft();
  int fate();
  int gold();

  bool isToad();
  void transformIntoToad();

  void move(MapTile* new_position);

  void pickup(Item* item);
  void pickup(Talisman* t);
  void drop(Item* item);
  void drop(Talisman* t);

  void recompute();

private:
  int life_counters;
  int starting_life;

  int base_strength;
  int strength_counters;
  int effective_strength;

  int base_craft;
  int craft_counters;
  int effective_craft;

  int fate_counters;
  int gold_counters;

  unsigned int capacity;
  unsigned int effective_capacity;
  bool is_toad;

  MapTile* position;

  std::vector<Item*> inventory;
  std::vector<Spell*> spells;
  std::vector<Talisman*> talismans;
  std::vector<Follower*> followers;
};

class Warrior : public Character
{
public:
  Warrior();
};

class Wizard : public Character
{
public:
  Wizard();
};
