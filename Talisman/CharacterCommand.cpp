#include "stdafx.h"
#include "CharacterCommand.h"


CharacterCommand::CharacterCommand(Character &subject) :
  subject(&subject)
{
}


CharacterCommand::~CharacterCommand(void)
{
}

GiveItem::GiveItem(Character &subject, Item &item) :
  CharacterCommand(subject),
  item(&item)
{
}

void GiveItem::execute()
{
  this->subject->pickup(this->item);
}

void GiveItem::revert()
{
  this->subject->drop(this->item);
}

GiveTalisman::GiveTalisman(Character &subject, Talisman &t) :
  CharacterCommand(subject),
  talisman(&t)
{
}

void GiveTalisman::execute()
{
  this->subject->pickup(this->talisman);
}

void GiveTalisman::revert()
{
  this->subject->drop(this->talisman);
}

DropItem::DropItem(Character &subject, Item &item) :
  CharacterCommand(subject),
  item(&item)
{
}

void DropItem::execute()
{
  this->subject->drop(this->item);
}

void DropItem::revert()
{
  this->subject->pickup(this->item);
}

DropTalisman::DropTalisman(Character &subject, Talisman &t) :
  CharacterCommand(subject),
  talisman(&t)
{
}

void DropTalisman::execute()
{
  this->subject->drop(this->talisman);
}

void DropTalisman::revert()
{
  this->subject->pickup(this->talisman);
}

TransformIntoToad::TransformIntoToad(Character &subject) : 
  CharacterCommand(subject)
{
}

void TransformIntoToad::execute()
{
  this->subject->transformIntoToad();
}

void TransformIntoToad::revert()
{
  this->subject->transformBack();
}

Move::Move(Character &subject, MapTile &tile) :
  CharacterCommand(subject),
  tile(&tile),
  prevTile(NULL)
{
}

void Move::execute()
{
  this->prevTile = this->subject->position();
  this->subject->move(this->tile);
}

void Move::revert()
{
  this->subject->move(this->prevTile);
}
