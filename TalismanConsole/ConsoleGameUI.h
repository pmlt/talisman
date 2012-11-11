#pragma once

#include "GameUI.h"
#include "Game.h"

class ConsoleGameUI :
  public GameUI
{
public:
  ConsoleGameUI(Game &game);
  virtual ~ConsoleGameUI(void);

  virtual void announce(string msg);
  virtual unsigned int prompt(string msg, string options[], unsigned int options_size);
  virtual void notify();
};

