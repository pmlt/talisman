#include "StdAfx.h"
#include "Character.h"

Character::Character(int life, int strength, int craft, int fate) : 
    life_counters(life), 
    starting_life(life),
    
    base_strength(strength), 
    strength_counters(0),

    base_craft(craft), 
    craft_counters(0),

    fate_counters(fate), 
    gold_counters(1), 
    is_toad(false), 
    base_capacity(DEFAULT_CAPACITY),
    position(0)
{
  recompute();
}

Character::~Character(void)
{
}

int Character::life() { return this->life_counters; }
int Character::strength() { return this->effective_strength; }
int Character::craft() { return this->effective_craft; }
int Character::fate() { return this->fate_counters; }
int Character::gold() { return this->gold_counters; }
unsigned int Character::capacity() { return this->effective_capacity; }

bool Character::isToad() { return this->is_toad; }
void Character::transformIntoToad()
{
  this->is_toad = 1;
  this->recompute();
}

void Character::move(MapTile* new_position)
{
  this->position = new_position;
  this->recompute();
}

void Character::pickup(Item* item)
{
  if (this->inventory.size() >= this->capacity()) {
    throw InventoryFullException();
  }
  this->inventory.push_back(item);
  this->recompute();
}

void Character::pickup(Talisman* t)
{
  this->talismans.push_back(t);
  this->recompute();
}

void Character::drop(Item* item)
{
  for (unsigned int i=0; i < this->inventory.size(); i++) {
    if (item == this->inventory[i]) {
      this->inventory.erase(this->inventory.begin()+i);
      this->recompute();
      return;
    }
  }
  throw NotInInventoryException();
}

void Character::drop(Talisman* t)
{
  for (unsigned int i=0; i < this->talismans.size(); i++) {
    if (t == this->talismans[i]) {
      this->talismans.erase(this->talismans.begin()+i);
      this->recompute();
      return;
    }
  }
  throw NotInInventoryException();
}

void Character::recompute()
{
  if (this->isToad()) {
    this->effective_strength = 1;
    this->effective_craft = 1;
  }
  else {
    this->effective_strength = this->base_strength + this->strength_counters;
    this->effective_craft = this->base_craft + this->craft_counters;
  }
  this->effective_capacity = this->base_capacity;
  
  // Take into account items in inventory
  for (unsigned int i=0; i < this->inventory.size(); i++) {
    Item *item = this->inventory[i];
    if (item->strength() > 0) {
      this->effective_strength += item->strength();
    }
    if (item->craft() > 0) {
      this->effective_craft += item->craft();
    }
    if (item->capacity() > 0) {
      this->effective_capacity += item->capacity();
    }
  }

  // Take into account current position 
  // (TODO when the map part is implemented)
}

/******* CHARACTER OVERRIDES *********/

Warrior::Warrior() : Character(4, 4, 2, 1) {}
Wizard::Wizard() : Character(2, 1, 4, 2) {}
