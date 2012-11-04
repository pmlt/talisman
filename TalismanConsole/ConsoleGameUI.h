#pragma once

#include "GameUI.h"
#include "Game.h"

class ConsoleGameUI :
  public GameUI
{
public:
  ConsoleGameUI(Game &game);
  virtual ~ConsoleGameUI(void);

  virtual void notify();
};

