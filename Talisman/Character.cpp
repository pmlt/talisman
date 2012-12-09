#include "StdAfx.h"
#include "Character.h"

#include <iostream>
#include <fstream>

Character::Character(int life, int strength, int craft, int fate) : 
    life_counters(life), 
    starting_life(life),
    
    base_strength(strength), 
    strength_counters(0),

    base_craft(craft), 
    craft_counters(0),

    fate_counters(fate), 
    gold_counters(1), 
    _alignment(0),
    is_toad(false), 
    base_capacity(DEFAULT_CAPACITY),
    _position(NULL)
{
  recompute();
}

Character::~Character(void)
{
  if (_position != NULL) _position->removePlayer(this);
}

void Character::createFromFile(string character_file, std::vector<Character*> &v)
{
  // Read file and create character from this
  
  ifstream file;
  file.open(character_file);
  if (file.is_open()) {
    string line;
    Character* c;
    while (file.good()) {
      getline(file, line);
      if (line.size() <= 0) continue; //Empty line
      if (line[0] == ';') continue; //Comment line
      if (line == "Warrior") c = new Warrior();
      else if (line == "Wizard") c = new Wizard();
      else throw new InvalidCharacterFileException(line);
      v.push_back(c);
    }
  }
  else {
    throw new FileOpenException(character_file);
  }
  file.close();
}

int Character::life() const { return this->life_counters; }
int Character::lifeLost() const { return this->starting_life - this->life_counters; }
int Character::strength() const { return this->effective_strength; }
int Character::craft() const { return this->effective_craft; }
int Character::fate() const { return this->fate_counters; }
int Character::gold() const { return this->gold_counters; }
float Character::alignment() const { return this->_alignment; }
unsigned int Character::capacity() const { return this->effective_capacity; }
unsigned int Character::remainingCapacity() const { return effective_capacity - _inventory.size(); }
vector<ObjectCard*> const & Character::inventory() const { return _inventory; }
vector<SpellCard*> const & Character::spells() const { return _spells; }
MapTile* Character::position() const { return this->_position; }

bool Character::isToad() const { return this->is_toad; }
void Character::transformIntoToad()
{
  this->is_toad = 1;
  this->recompute();
}
void Character::transformBack()
{
  this->is_toad = 0;
  this->recompute();
}

void Character::move(MapTile* new_position)
{
  if (this->_position != NULL) {
    this->_position->removePlayer(this);
  }
  this->_position = new_position;
  this->_position->addPlayer(this);
  this->recompute();
}

void Character::pickup(ObjectCard* item)
{
  if (this->_inventory.size() >= this->capacity()) {
    throw InventoryFullException();
  }
  this->_inventory.push_back(item);
  this->recompute();
}

void Character::pickup(SpellCard* spell)
{
  this->_spells.push_back(spell);
  this->recompute();
}

void Character::drop(ObjectCard* item)
{
  for (unsigned int i=0; i < this->_inventory.size(); i++) {
    if (item == this->_inventory[i]) {
      this->_inventory.erase(this->_inventory.begin()+i);
      this->recompute();
      return;
    }
  }
  throw NotInInventoryException();
}

void Character::drop(SpellCard* spell)
{
  for (unsigned int i=0; i < this->_spells.size(); i++) {
    if (spell == this->_spells[i]) {
      this->_spells.erase(this->_spells.begin()+i);
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
  
  // Take into account items in _inventory
  // (TODO)

  // Take into account current position 
  // (TODO when the map part is implemented)

  //Notify all observers
  this->notify();
}

void Character::incrementStrength() {
  base_strength++;
  recompute();
}
void Character::incrementCraft() {
  base_craft++;
  recompute();
}

void Character::setFate(int newFate)
{
  fate_counters = newFate;
}

void Character::setGold(int newGold)
{
  gold_counters = newGold;
}

void Character::setAlignment(float alignment) {
  _alignment = alignment;
}

void Character::setLife(int newLife)
{
  life_counters = newLife;
}

/******* CHARACTER OVERRIDES *********/

Warrior::Warrior() : Character(5, 4, 2, 1) {}
Wizard::Wizard() : Character(4, 2, 5, 3) {}
