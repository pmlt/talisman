#pragma once
class Item
{
public:
  Item();
  virtual ~Item(void);
  
  // There are PASSIVE bonuses (always applied, no need to use the item)
  virtual int strength() = 0;
  virtual int craft() = 0;
  virtual int capacity() = 0;
};

class Weapon : public Item
{
public:
  virtual int getAttackBonus() = 0; //Bonus if USED in battle
  virtual int capacity() { return 0; } //Reasonable default
};

class Armor : public Item
{
public:
  virtual int getLifeBonus() = 0; //Bonus if USED after battle
  virtual int capacity() { return 0; } //Reasonable default
};

/**
 * Sword: Example of weapon that gives a +1 strength bonus
 * if used in battle, but no passive bonuses.
 */
class Sword : public Weapon
{
public:
  virtual int strength() { return 0; }
  virtual int craft() { return 0; }
  virtual int capacity() { return 0; }
  virtual int getAttackBonus() { return 1; }
};

/**
 * Axe: Example of weapon that gives a constant passive
 * +2 strength bonus, but cannot be used in battle.
 */
class Axe : public Weapon
{
public:
  virtual int strength() { return 2; }
  virtual int craft() { return 0; }
  virtual int capacity() { return 0; }
  virtual int getAttackBonus() { return 0; }
};

/**
 * Shield: Example of armor which can be used after a lost battle
 * to nullify the life penalty.
 */
class Shield : public Armor
{
public:
  virtual int strength() { return 0; }
  virtual int craft() { return 0; }
  virtual int capacity() { return 0; }
  virtual int getLifeBonus() { return 1; }
};

/**
 * Mule: Example of item which increases carrying capacity.
 */
class Mule : public Item
{
public:
  virtual int strength() { return 0; }
  virtual int craft() { return 0; }
  virtual int capacity() { return 4; }
};
