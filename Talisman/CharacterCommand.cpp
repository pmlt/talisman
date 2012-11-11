#include "stdafx.h"
#include "CharacterCommand.h"
#include "Character.h"


CharacterCommand::CharacterCommand(Character &subject) :
  subject(&subject)
{
}


CharacterCommand::~CharacterCommand(void)
{
}

GiveItem::GiveItem(Character &subject, ObjectCard &item) :
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

DropItem::DropItem(Character &subject, ObjectCard &item) :
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
