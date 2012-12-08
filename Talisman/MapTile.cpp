#include "StdAfx.h"
#include "MapTile.h"
#include "Character.h"
#include "Game.h"
#include "CharacterCommand.h"
#include "Battle.h"
#include <sstream>

using namespace std;

MapTile::MapTile() :
  cw(NULL),ccw(NULL),players()
{
}


MapTile::~MapTile(void)
{
}

Character* MapTile::getPlayer(unsigned int index) const { return this->players[index]; }
unsigned int MapTile::getPlayerCount() const { return players.size(); }
void MapTile::addPlayer(Character* player) { this->players.push_back(player); }
void MapTile::removePlayer(Character* player) {
  for (auto it = players.begin(); it != players.end(); it++) {
    if ((*it) == player) {
      players.erase(it);
      break;
    }
  }
}

void MapTile::setNeighbors(MapTile* cw, MapTile* ccw)
{
  this->cw = cw;
  this->ccw = ccw;
}

unsigned char MapTile::rollMovement(Character *character, Game *game)
{
  //Random number between 1 and 6
  return game->roll();
}

void MapTile::start(Character *character, Game* game)
{
  //Redraw
  game->notify();

  //Roll how much for movement
  unsigned char movement = this->rollMovement(character, game);
  stringstream smov;
  smov << (int)movement;

  //Prompt for which direction.
  string opts[2] = {
    "Clockwise",
    "Counter-clockwise"
  };
  unsigned int direction = game->getUI()->prompt("You rolled a " + smov.str() + "! Which direction do you want to go", opts, 2);

  //Go!
  this->leave(character, game, movement, direction);
}

void MapTile::leave(Character* character, Game* game, unsigned int movement, unsigned int direction)
{
  //Simply move out by default
  this->step(character, game, movement, direction);
}

void MapTile::step(Character *character, Game* game, unsigned int movement, unsigned int direction)
{
  if (movement == 0) {
    this->land(character, game);
    return;
  }
  if (direction == 0) {
    //Clockwise
    this->cw->step(character, game, movement - 1, direction);
  }
  else {
    //Counter-clockwise
    this->ccw->step(character, game, movement - 1, direction);
  }
}

void MapTile::land(Character* character, Game* game)
{
  game->getUI()->announce("You have arrived at the " + this->getTitle() + "...");
  //Set the new position
  character->move(this);
  //Default behavior for demonstration: draw a card.
  AdventureCard *card = game->drawAdventureCard();
  if (card != NULL) {
    //Encounter the card!
    card->encounter(character, game);

    //if enemy, send character and card to fight
    //temporary condition
    if (card->title() == "Bear" || card->title() == "Wolf" || card->title() == "Wild Boar")
    {
      Battle * battle = new Battle();
      battle->cardFight(character, card, game);
    }
    
  }
  //Redraw
  game->notify();
}

string VillageTile::getTitle() const { return "Village"; }

string FieldsTile::getTitle() const { return "Fields"; }

string GraveyardTile::getTitle() const { return "Graveyard"; }

string WoodsTile::getTitle() const { return "Woods"; }

string SentinelTile::getTitle() const { return "Sentinel"; }

void SentinelTile::step(Character *character, Game* game, unsigned int movement, unsigned int direction)
{
  if (movement > 0) {
    //Ask user to move to inner region
    string options[2] = {
      "Yes, cross into the middle region.",
      "No, continue my way in the outer region."
    };
    unsigned char choice = game->getUI()->prompt("You are passing the Sentinel space and you still have movement left. Do you want to cross the Sentinel into the middle region?", options, 2);
    if (choice == 0) {
      //Cross!
      MapTile* dest = game->getBoard()->find("Portal of Power");
      if (dest != NULL) {
        dest->land(character, game);
        return; //Do NOT continue
      }
    }
  }
  //Continue normally
  MapTile::step(character, game, movement, direction);
}

string HillsTile::getTitle() const { return "Hills"; }

string ChapelTile::getTitle() const { return "Chapel"; }

string CragsTile::getTitle() const { return "Crags"; }

string PlainsTile::getTitle() const { return "Plains"; }

string CityTile::getTitle() const { return "City"; }

string TavernTile::getTitle() const { return "Tavern"; }

string RuinsTile::getTitle() const { return "Ruins"; }

string ForestTile::getTitle() const { return "Forest"; }

string PortalOfPowerTile::getTitle() const { return "Portal of Power"; }

string BlackKnightTile::getTitle() const { return "Black Knight"; }

string HiddenValleyTile::getTitle() const { return "Hidden Valley"; }

string CursedGladeTile::getTitle() const { return "Cursed Glade"; }

string RunesTile::getTitle() const { return "Runes"; }

string ChasmTile::getTitle() const { return "Chasm"; }

string WarlocksCaveTile::getTitle() const { return "Warlock's Cave"; }

string DesertTile::getTitle() const { return "Desert"; }

string OasisTile::getTitle() const { return "Oasis"; }

string TempleTile::getTitle() const { return "Temple"; }

string CastleTile::getTitle() const { return "Castle"; }

string PlainsOfPerilTile::getTitle() const { return "Plains of Peril"; }

string MinesTile::getTitle() const { return "Mines"; }

string VampiresTowerTile::getTitle() const { return "Vampire's Tower"; }

string PitsTile::getTitle() const { return "Pits"; }

string ValleyOfFireTile::getTitle() const { return "Valley of Fire"; }

string WerewolfDenTile::getTitle() const { return "Werewolf Den"; }

string DeathTile::getTitle() const { return "Death"; }

string CryptTile::getTitle() const { return "Crypt"; }
