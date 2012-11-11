#include "stdafx.h"
#include "Game.h"
#include <time.h>

Game::Game(void)
{
}

Game::~Game(void)
{
}

Game* Game::init(string map_file, string character_file, string card_file)
{
  //Create Game object
  //Create Board object from map_file
  //Create Character object from character_file
  //Create card deck from card_file
  //Attach all three objects to the Game object
  //Return Game object
  return NULL;
}

Game* Game::instance()
{
  return Game::inst;
}

void Game::destroy(Game* game)
{
  delete game;
}

GameUI* Game::getUI() const { return this->ui; }
void Game::setUI(GameUI &ui) { this->ui = &ui; }

void Game::addPlayer(Character &c)
{
  // Assign position on board to player

  for(vector<int>::size_type i = 0; i != players.size(); i++) {
    if (this->players[i]->name() == c.name() )
    {
      //Throw PlayerExistsException
      return;
    }
  }
  // Assign position on board to player
  this->players.push_back(&c);
}

void Game::removePlayer(Character &c)
{
  for(vector<int>::size_type i = 0; i != players.size(); i++) {
    if (this->players[i]->name() == c.name() )
    {
      this->players.erase(this->players.begin() + i);
      //Remove from board
      return;
    }
  }
  //Throw PlayerNotFoundException

}

Board* Game::getBoard() const { return this->board; }
void Game::setBoard(Board &board) { this->board = &board; }

void Game::addAdventureCard(AdventureCard &card)
{
  this->adventure_deck.push(&card);
}

AdventureCard* Game::drawAdventureCard()
{
  auto card = this->adventure_deck.front();
  this->adventure_deck.pop();
  return card;
}

unsigned char Game::roll() const
{
  srand((unsigned int)time(NULL));
  return (rand() % 6) + 1;;
}

void Game::start()
{
  //Start the whole game!
}
