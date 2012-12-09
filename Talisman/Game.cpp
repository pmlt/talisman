#include "stdafx.h"
#include "Game.h"
#include <time.h>

Game::Game(void)
{
}

Game::~Game(void)
{
}

Game* Game::init(string map_file, string character_file, string adventure_deck_file, string purchase_deck_file)
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
  srand((unsigned int)time(NULL));

  //Create card decks from files
  vector<AdventureCard*> v1, v2;
  AdventureCard::createDeckFromFile(adventure_deck_file, v1, false);
  for (auto it = v1.begin(); it != v1.end(); it++) {
    _inst->adventure_deck.push(*it);
  }
  AdventureCard::createDeckFromFile(purchase_deck_file, v2, true);
  for (auto it = v2.begin(); it != v2.end(); it++) {
    _inst->purchase_deck.push(*it);
  }

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

vector<Character*> const & Game::getPlayers() const { return players; }

void Game::removePlayer(Character* c)
{
  for(vector<int>::size_type i = 0; i != players.size(); i++) {
    if (this->players[i] == c )
    {
      this->players.erase(this->players.begin() + i);
      //Remove from board
      return;
    }
  }
  Character* first_player = player_turns.front();
  bool removed_character = false;
  while (!removed_character && player_turns.front() != first_player) {
    Character* p = player_turns.front();
    player_turns.pop();
    if (!removed_character && p == c) {
      removed_character = true;
      delete c;
      break; //Don't add it back to the queue
    }
    player_turns.push(p);
  }
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

void Game::discardAdventureCard(AdventureCard* card)
{
  this->adventure_deck.push(card);
}

unsigned char Game::roll() const
{
  return (rand() % 6) + 1;;
}

bool Game::loseLife(Character* character, int life_lost)
{
  character->setLife(character->life() - life_lost);
  if (character->life() <= 0) {
    ui->announce("The " + character->name() + " has perished!");
    removePlayer(character);
    return false;
  }
  return true;
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
  ui->announce("The " + players[0]->name() + " emerges victorious! Congratulations!");
}

bool Game::isFinished()
{
  //Inspect victory conditions
  //Return true if a player has won
  //Victory conditions are:
  //  1 - There is only one player surviving
  //  2 - That player is on the Crown of Command (in the Valley of Fire).
  return  getNumberOfPlayers() == 1 && 
          players[0]->position()->getTitle() == "Valley of Fire" && 
          dynamic_cast<ValleyOfFireTile*>(players[0]->position())->hasCrown(players[0]);
}

int Game::getNumberOfPlayers() const
{
  return this->players.size();
}
