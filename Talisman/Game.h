#pragma once
#include <string>
#include <vector>
#include <queue>
#include "Character.h"
#include "Board.h"
#include "AdventureCard.h"
#include "GameUI.h"
#include "Observable.h"

using namespace std;

class GameUI;

class Game : public Observable
{
public:
  static Game* create(string map_file, string character_file, string card_file);
  static void destroy(Game* game);
  
  GameUI* getUI() const;
  void setUI(GameUI &ui);

  void addPlayer(Character &c);
  void removePlayer(Character &c);

  Board* getBoard() const;
  void setBoard(Board &board);

  void addAdventureCard(AdventureCard &card);
  AdventureCard* drawAdventureCard();

  unsigned char roll() const;

  void start();

private:
  Game(void);
  ~Game(void);

  GameUI* ui;
  vector<Character*> players;
  Board* board;
  queue<AdventureCard*> adventure_deck;
};

