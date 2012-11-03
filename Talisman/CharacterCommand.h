#pragma once
#include "TalismanGame.h"

class Character; //Temporary declaration just to compile

/*
  Class: CharacterCommand
  Represents a single reversible operation on a character.
*/
class CharacterCommand
{
public:
  CharacterCommand(Character &subject);
  virtual ~CharacterCommand(void);

  /*
    Method: execute
    Apply the operation to the character.
  */
  virtual void execute() = 0;

  /*
    Method: revert
    Undo the operation to the character.
  */
  virtual void revert() = 0;

protected:
  Character *subject;
};

/*
  Class: GiveItem
  Give an item to a character. Undoing this operation
  remove the item from the character.
*/
class GiveItem : public CharacterCommand
{
public:
  GiveItem(Character &subject, Item &item);

  virtual void execute();
  virtual void revert();
private:
  Item *item;
};

/*
  Class: GiveTalisman
  Give a talisman to a character. Undoing this operation
  removes the talisman from the character.
*/
class GiveTalisman : public CharacterCommand
{
public:
  GiveTalisman(Character &subject, Talisman &talisman);

  virtual void execute();
  virtual void revert();
private:
  Talisman *talisman;
};

/*
  Class: DropItem
  Remove an item from a character's inventory. Undoing this
  operation will give the item back to the character.
*/
class DropItem : public CharacterCommand
{
public:
  DropItem(Character &subject, Item &item);

  virtual void execute();
  virtual void revert();
private:
  Item *item;
};

/*
  Class: DropTalisman
  Remove a talisman from a character's inventory. Undoing this
  operation will give the talisman back to the character.
*/
class DropTalisman : public CharacterCommand
{
public:
  DropTalisman(Character &subject, Talisman &talisman);

  virtual void execute();
  virtual void revert();
private:
  Talisman *talisman;
};

/*
  Class: TransformIntoToad
  Transform a character into a toad. Undoing this operation
  will turn him back into a human.
*/
class TransformIntoToad : public CharacterCommand
{
public:
  TransformIntoToad(Character &subject);

  virtual void execute();
  virtual void revert();
};

/*
  Class: Move
  Move a character to a new tile. Undoing this operation
  will move the character back to the previous tile.
*/
class Move : public CharacterCommand
{
public:
  Move(Character &subject, MapTile &tile);

  virtual void execute();
  virtual void revert();
private:
  MapTile* tile;
  MapTile* prevTile;
};
