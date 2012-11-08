#include "stdafx.h"
#include "Game.h"
#include <time.h>

Game::Game(void)
{
}

Game::~Game(void)
{
}

Game* Game::create(string map_file, string character_file, string card_file)
{
  //Create Game object
  //Create Board object from map_file
  //Create Character object from character_file
  //Create card deck from card_file
  //Attach all three objects to the Game object
  //Return Game object
  return NULL;
}

void Game::destroy(Game* game)
{
  delete game;
}

GameUI* Game::getUI() const { return this->ui; }
void Game::setUI(GameUI &ui) { this->ui = &ui; }

void Game::addPlayer(Character &c)
{
  // Check player is not already in vector
  // Assign position on board to player
  // Add player to vector
}

void Game::removePlayer(Character &c)
{
  //Throw exception if player not found in vector
  //Remove player from board
  //Remove player from vector
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
  srand(time(NULL));
  return (rand() % 6) + 1;;
}

void Game::start()
{
  //Start the whole game!
}
