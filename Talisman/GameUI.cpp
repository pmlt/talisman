#include "stdafx.h"
#include "GameUI.h"


GameUI::GameUI(Game &game) :
  game(&game)
{
  game.attach(this);
}


GameUI::~GameUI(void)
{
  this->game->detach(this);
}
