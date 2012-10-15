#pragma once

/*
  Class: Item
  Represents an Object card in the game.
*/
class Item
{
public:
  Item();
  virtual ~Item(void);
  
  /*
    Method: strength
    Returns the strength modifier that this Object card confers to the
    character which is carrying it. This bonus is passive (always applied).

    This method MUST be overriden by child classes (it is part of the
    definition of the item).
  */
  virtual int strength() = 0;
  /*
    Method: craft
    Returns the craft modifier that this Object card confers to the
    character which is carrying it. This bonus is passive (always applied).

    This method MUST be overriden by child classes (it is part of the
    definition of the item).
  */
  virtual int craft() = 0;
  /*
    Method: capacity
    Returns the capacity modifier that this Object card confers to the
    character which is carrying it. This bonus is passive (always applied).

    This method MUST be overriden by child classes (it is part of the
    definition of the item).
  */
  virtual int capacity() = 0;
};

/*
  Class: Weapon
  Represents a Weapon card. Cards of this type can be actively used once in
  battle to confer additional bonuses to its wielder (this is different than 
  passive bonuses).
*/
class Weapon : public Item
{
public:
  /*
    Method: getAttackBonus
    Returns the bonus to attack roll that this weapon confers to its wielder
    when activated in battle.

    This method MUST be overriden by child classes (it is part of the
    definition of the weapon).
  */
  virtual int getAttackBonus() = 0; //Bonus if USED in battle
};

/*
  Class: Armor
  Represents an Armor card. Cards of this type can be used once after a battle
  to regain some life if the battle was lost.
*/
class Armor : public Item
{
public:
  /*
    Method: getLifeBonus
    Returns the bonus to life that this armor confers to its user
    at the end of a battle.

    This method MUST be overriden by child classes (it is part of the
    definition of the weapon).
  */
  virtual int getLifeBonus() = 0;
};

/*
  Class: Sword
  Example of a concrete weapon that gives a +1 strength bonus
  if used in battle, but no passive bonuses.
*/
class Sword : public Weapon
{
public:
  virtual int strength() { return 0; }
  virtual int craft() { return 0; }
  virtual int capacity() { return 0; }
  virtual int getAttackBonus() { return 1; }
};

/*
  Class: Axe
  Example of a concrete weapon that gives a constant passive
  +2 strength bonus, but cannot be used in battle.
*/
class Axe : public Weapon
{
public:
  virtual int strength() { return 2; }
  virtual int craft() { return 0; }
  virtual int capacity() { return 0; }
  virtual int getAttackBonus() { return 0; }
};

/*
  Class: Shield
  Example of a concrete armor which can be used after a lost battle
  to nullify the life penalty.
*/
class Shield : public Armor
{
public:
  virtual int strength() { return 0; }
  virtual int craft() { return 0; }
  virtual int capacity() { return 0; }
  virtual int getLifeBonus() { return 1; }
};

/*
  Class: Mule
  Example of concrete item which simply increases carrying capacity.
*/
class Mule : public Item
{
public:
  virtual int strength() { return 0; }
  virtual int craft() { return 0; }
  virtual int capacity() { return 4; }
};
