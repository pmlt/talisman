#pragma once

#include "Observer.h"
#include "TalismanGame.h"

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

