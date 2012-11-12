#include "StdAfx.h"
#include "MapTile.h"
#include "Character.h"
#include "Game.h"
#include "CharacterCommand.h"
#include <sstream>

using namespace std;

MapTile::MapTile() :
  cw(NULL),ccw(NULL),player(NULL)
{
}


MapTile::~MapTile(void)
{
}

Character* MapTile::getPlayer() { return this->player; }
void MapTile::setPlayer(Character* player) { this->player = player; }

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
  game->getUI()->announce("You have arrived at the " + this->getTitle() + "... Your turn is over.");
  //Set the new position
  character->move(this);
  //Redraw
  game->notify();
}

string VillageTile::getTitle() const { return "Village"; }

string FieldsTile::getTitle() const { return "Fields"; }

string GraveyardTile::getTitle() const { return "Graveyard"; }

string WoodsTile::getTitle() const { return "Woods"; }

string SentinelTile::getTitle() const { return "Sentinel"; }

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
