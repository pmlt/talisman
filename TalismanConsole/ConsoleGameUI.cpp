#include "stdafx.h"
#include "ConsoleGameUI.h"


ConsoleGameUI::ConsoleGameUI(Game &game) :
  GameUI(game)
{
}


ConsoleGameUI::~ConsoleGameUI(void)
{
}

void ConsoleGameUI::notify()
{
  //Redraw screen here! You have access to the whole game information from this->game
}
