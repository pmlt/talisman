#pragma once

#include "Game.h"

class Game;

/*
  Class: GameUI
  Abstract representation of the game's user interface.
  Offers facilies for both input and output.
*/
class GameUI : public Observer
{
public:

  GameUI(Game &game);
  virtual ~GameUI(void);

  /*
    Method: announce
    Announce something to the player, not requiring any feedback.
  */
  virtual void announce(string msg) = 0;

  /*
    Method: prompt
    Prompt the user to make a choice from a collection of options.

    Parameters:
      msg          - The prompt text
      options      - Array of option strings the user must pick from
      options_size - How many options are in the array

    Return:
      The index of the chosen option.
  */
  virtual unsigned int prompt(string msg, string options[], unsigned int options_size) = 0;

  /*
    Method: notify
    Notify the UI that a change occured in the game, so that it redraws
    itself.
  */
  virtual void notify() = 0;

protected:
  Game* game;
};

