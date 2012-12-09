#pragma once
#include <string>
#include <vector>
#include <queue>
#include "Character.h"
#include "Board.h"
#include "AdventureCard.h"
#include "GameUI.h"
#include "Observable.h"
#include "Battle.h"

using namespace std;

class GameUI;

/*
  Class: Game
  Represents the entire game logic. Singleton.
*/
class Game : public Observable
{
public:
  /*
    Method: init
    Initialize the singleton using files for content.
  */
  static Game* init(string map_file, string character_file, string adventure_deck_file, string purchase_deck_file);

  /*
    Method: destroy
    Destroy the game instance.
  */
  static void destroy(Game* game);
  
  /*
    Method: getUI
    Returns a handle to the game's user interface.
  */
  GameUI* getUI() const;

  /*
    Method: setUI
    Sets the game's user interface.  This should not be called manually
    by client code.
  */
  void setUI(GameUI &ui);

  /*
    Method: getPlayers
    Returns the list of players.
  */
  vector<Character*> const & getPlayers() const;

  /*
    Method: removePlayer
    Removes a player from the session.
  */
  void removePlayer(Character* c);

  /*
    Method: getBoard
    Returns a handle to the game's board.
  */
  Board* getBoard() const;

  /*
    Method: setBoard
    Sets the game's board. This should not be called manually by client code.
  */
  void setBoard(Board &board);

  /*
    Method: addAdventureCard
    Add an adventure card to the adventure card deck. This should only
    be called before start().
  */
  void addAdventureCard(AdventureCard &card);

  /*
    Method: drawAdventureCard
    Draw from the Adventure deck. Returns NULL if no cards left.
  */
  AdventureCard* drawAdventureCard();

  /*
    Method: discardAdventureCard
    Put back a card into the adventure deck.
  */
  void discardAdventureCard(AdventureCard* card);

  /*
    Method: roll
    Roll the dice!
  */
  unsigned char roll() const;

  /*
    Method: loseLife
    Cause a player to lose some life tokens; the player may die as a result.

    Returns TRUE if player survived or FALSE otherwise.
  */
  bool loseLife(Character* character, int life_lost);

  /*
    Method: start
    Start the game session, setting everything in motion.
  */
  void start();

  /*
    Method: isFinished
    Inspect victory conditions to determine if a player has won.
  */
  bool isFinished();

  int getNumberOfPlayers() const;

private:
  Game(void);
  ~Game(void);

  GameUI* ui;
  vector<Character*> players;
  queue<Character*> player_turns;
  Board* board;
  queue<AdventureCard*> adventure_deck;
  queue<AdventureCard*> purchase_deck;
};
