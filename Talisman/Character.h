#pragma once

#include "AdventureCard.h"
#include "MapTile.h"
#include "Observable.h"
#include "TException.h"
#include <vector>
#include <string>

#define DEFAULT_CAPACITY 4

class MapTile;

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
    Method: createFromFile
    Add a series of constructed characters to a vector from a file
  */
  static void createFromFile(std::string character_file, std::vector<Character*> &v);

  /*
    Method: name
    The name of the card
  */
  virtual std::string name() const = 0;

  /*
    Method: life
    Returns the current life amount of the character
  */
  int life() const;

  /*
    Method: lifeLost
    Returns the difference between starting life and current life.
  */
  int lifeLost() const;

  /*
    Method: setLife
    Sets the current life amount of the character
  */
  void setLife(int);

  /*
    Method: strength
    Returns the effective strength of the character. The effective strength
    means taking into account the base strength, strength tokens, equipment, 
    and current position on the map.
  */
  int strength() const;

  /*
    Method: craft
    Returns the effective craft of the character. The effective craft
    means taking into account the base craft, craft tokens, equipment, 
    and current position on the map.
  */
  int craft() const;

  /*
    Method: fate
    Returns the current number of fate tokens of the character.
  */
  int fate() const;

  /*
    Method: setFate
    Sets the current number of fate tokens of the character.
  */
  void setFate(int);
  /*
    Method: gold
    Returns the current number of gold tokens of the character.
  */
  int gold() const;
  /*
    Method: alignment
    Returns the alignment of the character (-1 = most evil to 1 = most good)
  */
  float alignment() const;

  /*
    Method: incrementStrength
    Gain 1 strength.
  */
  void incrementStrength();

  /*
    Method: incrementCraft
    Gain 1 craft.
  */
  void incrementCraft();

  /*
    Method: setGold
    Sets the current number of gold tokens of the character.
  */
  void setGold(int);

  /*
    Method: setAlignment
    Sets the alignment of the character.
  */
  void setAlignment(float alignment);

  /*
    Method: capacity
    Returns the carrying capacity of the character.
  */
  unsigned int capacity() const;

  /*
    Method: remainingCapacity
    Returns the number of free slots in the character's inventory.
  */
  unsigned int remainingCapacity() const;

  /*
    Method: startPosition
    Returns the starting position of the character.
  */
  virtual std::string startPosition() const = 0;

  /*
    Method: position
    Returns the current tile that the character is on.
  */
  MapTile* position() const;

  /*
    Method: isToad
    Check whether character has been transformed into a toad or not.
  */
  bool isToad() const;
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
  void pickup(ObjectCard* item);

  /*
    Method: pickup
    Pick up a spell and add it to character's spellbook.
  */
  void pickup(SpellCard* item);

  /*
    Method: drop
    Drop an item from inventory and places it on the current map tile.

    Throws:
      NotInInventoryException - The item could not be found in inventory.
  */
  void drop(ObjectCard* item);

  /*
    Method: drop
    Drop a spell from spellbook and places it on the current map tile.

    Throws:
      NotInInventoryException - The item could not be found in spellbook.
  */
  void drop(SpellCard* item);

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
  float _alignment;

  unsigned int base_capacity;
  unsigned int effective_capacity;
  bool is_toad;

  MapTile* _position;

  std::vector<ObjectCard*> inventory;
  std::vector<SpellCard*> spells;
  std::vector<FollowerCard*> followers;
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

  virtual std::string name() const { return "Warrior"; }
  virtual std::string startPosition() const { return "Tavern"; }
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
  
  virtual std::string name() const { return "Wizard"; }
  virtual std::string startPosition() const { return "Graveyard"; }
};
