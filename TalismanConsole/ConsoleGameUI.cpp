#include "stdafx.h"
#include "ConsoleGameUI.h"


ConsoleGameUI::ConsoleGameUI(Game &game) :
  GameUI(game)
{
}


ConsoleGameUI::~ConsoleGameUI(void)
{
}

unsigned int prompt(string msg, string options[], unsigned int options_size)
{
  //Use cout and cin to display choices and retrieve user input.
  //Should re-ask if user did not choose one of the options.
}

void ConsoleGameUI::notify()
{
  //Redraw screen here! You have access to the whole game information from this->game
}
