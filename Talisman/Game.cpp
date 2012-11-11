#include "stdafx.h"
#include "Game.h"
#include <time.h>

Game::Game(void)
{
}

Game::~Game(void)
{
}

Game* Game::init(string map_file, string character_file, string deck_file)
{
  //Create Game object
  Game* _inst = new Game();
  
  //Create Board object from map_file
  _inst->board = Board::createFromFile(map_file);
  
  //Create Character object from character_file
  Character::createFromFile(character_file, _inst->players);
  //Place characters on the board
  for (auto it = _inst->players.begin(); it != _inst->players.end(); it++) {
    string start_pos = (*it)->startPosition();
    MapTile* start_tile = _inst->board->find(start_pos);
    if (start_tile == NULL) throw new TException("Invalid starting position for " + (*it)->name());
    (*it)->move(start_tile);
    _inst->player_turns.push(*it);
  }

  //Create card deck from card_file
  AdventureCard::createDeckFromFile(deck_file, _inst->adventure_deck);

  //Return Game object
  return _inst;
}

void Game::destroy(Game* game)
{
  Character *c;
  while (game->players.size() > 0) {
    c = game->players.back();
    game->players.pop_back();
    delete c;
  }
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
  auto card = this->adventure_deck.top();
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
  while (!this->isFinished()) {
    //Do next player's turn
    Character *c = this->player_turns.front();

    this->getUI()->announce("It is now the " + c->name() + "'s turn...");

    MapTile* t = c->position();
    t->start(c, this);

    this->player_turns.pop();
    this->player_turns.push(c);
  }
}

bool Game::isFinished()
{
  //Inspect victory conditions
  //Return true if a player has won
  return 0;
}

