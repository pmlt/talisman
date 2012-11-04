#pragma once

#include "Game.h"

class Game;

class GameUI : public Observer
{
public:
  GameUI(Game &game);
  virtual ~GameUI(void);

  virtual void notify() = 0; //Redraw UI

protected:
  Game* game;
};

