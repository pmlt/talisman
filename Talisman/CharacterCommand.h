#pragma once
#include "TalismanGame.h"

class Character; //Temporary declaration just to compile

class CharacterCommand
{
public:
  CharacterCommand(Character &subject);
  virtual ~CharacterCommand(void);

  virtual void execute() = 0;
  virtual void revert() = 0;

protected:
  Character *subject;
};

class GiveItem : public CharacterCommand
{
public:
  GiveItem(Character &subject, Item &item);

  virtual void execute();
  virtual void revert();
private:
  Item *item;
};

class GiveTalisman : public CharacterCommand
{
public:
  GiveTalisman(Character &subject, Talisman &talisman);

  virtual void execute();
  virtual void revert();
private:
  Talisman *talisman;
};

class DropItem : public CharacterCommand
{
public:
  DropItem(Character &subject, Item &item);

  virtual void execute();
  virtual void revert();
private:
  Item *item;
};

class DropTalisman : public CharacterCommand
{
public:
  DropTalisman(Character &subject, Talisman &talisman);

  virtual void execute();
  virtual void revert();
private:
  Talisman *talisman;
};

class TransformIntoToad : public CharacterCommand
{
public:
  TransformIntoToad(Character &subject);

  virtual void execute();
  virtual void revert();
};

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
