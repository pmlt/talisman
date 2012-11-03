#pragma once

#include "TalismanGame.h"
#include "Observable.h"
#include <vector>
#include <string>

/*
  Class: Character

  The base class representing a Talisman character. All character types must
  inherit this class. 
*/
class Character : public Observable
{
public:
  /*
    Constructor: Character

    Parameters:
      life     - Starting amount of life (as shown on the character card)
      strength - Base strength value (as shown on the character card)
      craft    - Base craft value (as shown on the character card)
      fate     - Starting amount of fate (as shown on the character card)
  */
	Character(int life, int strength, int craft, int fate);
	virtual ~Character(void);

  /*
    Method: name
    The name of the card
  */
  virtual std::string name() = 0;

  /*
    Method: life
    Returns the current life amount of the character
  */
  int life();

  /*
    Method: strength
    Returns the effective strength of the character. The effective strength
    means taking into account the base strength, strength tokens, equipment, 
    and current position on the map.
  */
  int strength();

  /*
    Method: craft
    Returns the effective craft of the character. The effective craft
    means taking into account the base craft, craft tokens, equipment, 
    and current position on the map.
  */
  int craft();

  /*
    Method: fate
    Returns the current number of fate tokens of the character.
  */
  int fate();

  /*
    Method: gold
    Returns the current number of gold tokens of the character.
  */
  int gold();

  /*
    Method: capacity
    Returns the carrying capacity of the character.
  */
  unsigned int capacity();

  /*
    Method: position
    Returns the current tile that the character is on.
  */
  MapTile* position();

  /*
    Method: isToad
    Check whether character has been transformed into a toad or not.
  */
  bool isToad();
  /*
    Method: transformIntoToad
    Transform character into toad.
  */
  void transformIntoToad();

  /*
    Method: transformBack
    Reverts Toad state.
  */
  void transformBack();

  /*
    Method: move
    Move the character to the new designated position. This may affect the
    character's effective strength and craft values.
  */
  void move(MapTile* new_position);

  /*
    Method: pickup
    Pick up an item and add it to the character's inventory.

    Throws:
      InventoryFullException - The character's inventory is already full
  */
  void pickup(Item* item);

  /*
    Method: pickup
    Pick up a talisman. There is no limit on the number of talismans.
  */
  void pickup(Talisman* t);

  /*
    Method: drop
    Drop an item from inventory and places it on the current map tile.

    Throws:
      NotInInventoryException - The item could not be found in inventory.
  */
  void drop(Item* item);

  /*
    Method: drop
    Drop a talisman from inventory and places it on the current map tile.

    Throws:
      NotInInventoryException - The item could not be found in inventory.
  */
  void drop(Talisman* t);

protected:
  /*
    Method: recompute
    Recalculate the effective strength, craft, and capacity of the character.
    Call this whenever a condition which may affect the character's attributes
    has changed.
  */
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

  unsigned int base_capacity;
  unsigned int effective_capacity;
  bool is_toad;

  MapTile* _position;

  std::vector<Item*> inventory;
  std::vector<Spell*> spells;
  std::vector<Talisman*> talismans;
  std::vector<Follower*> followers;
};

/*
  Class: Warrior
  Concrete character class represented by a card. The concrete class
  has no constructor parameters; it assigns hardcoded values to the 
  parent constructor's parameters. That is what represents the values
  on the card.
*/
class Warrior : public Character
{
public:
  Warrior();

  virtual std::string name() { return "Warrior"; }
};

/*
  Class: Wizard
  Concrete character class represented by a card. The concrete class
  has no constructor parameters; it assigns hardcoded values to the 
  parent constructor's parameters. That is what represents the values
  on the card.
*/
class Wizard : public Character
{
public:
  Wizard();
  
  virtual std::string name() { return "Wizard"; }
};
