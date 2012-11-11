#pragma once

#include "Observer.h"
#include "Character.h"

class CharacterPrinter :
  public Observer
{
public:
  CharacterPrinter(Character &subject);
  ~CharacterPrinter(void);

  virtual void notify();

private:
  Character* subject;
};

